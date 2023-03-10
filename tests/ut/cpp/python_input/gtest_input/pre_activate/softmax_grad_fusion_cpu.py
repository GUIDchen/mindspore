# Copyright 2022 Huawei Technologies Co., Ltd
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ============================================================================
from mindspore.ops import Primitive
from mindspore.ops import _constants as Constants
from mindspore.ops import operations as P

mul = P.Mul()
reduce_sum = P.ReduceSum(keep_dims=True)
sub = P.Sub()
prim_after_fusion = Primitive('SoftmaxGradFusion')
make_tuple = Primitive('MakeTuple')
tuple_getitem = Primitive(Constants.kTupleGetItem)


class FuncDict:
    def __init__(self):
        self.fn_dict = {}

    def __call__(self, fn):
        self.fn_dict[fn.__name__] = fn

    def __getitem__(self, name):
        return self.fn_dict.get(name)


def test_softmax_grad_fusion_cpu(tag):
    """
    Feature: Test SoftmaxGradFusionCpu pass
    Description: Test SoftmaxGradFusionCpu pass
    Expectation: The graph after fusion is as expected when it meets the pattern of the pass.
    """
    fns = FuncDict()

    @fns
    def before(input0, input1):
        res = mul(input0, input1)
        # input axis will be convert to attr in ConstructKernelGraph step
        res = reduce_sum(res, -1)
        res = sub(input1, res)
        res = mul(input0, res)
        return res

    @fns
    def after(input0, input1):
        res = prim_after_fusion(input0, input1)
        return make_tuple(res)

    return fns[tag]
