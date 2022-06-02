# Copyright 2020 Huawei Technologies Co., Ltd
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

import numpy as np
import pytest

import mindspore
import mindspore.nn as nn
from mindspore import Tensor, context
from mindspore.ops import operations as P

context.set_context(mode=context.GRAPH_MODE, device_target='CPU')


class TruncateDiv(nn.Cell):
    def __init__(self):
        super(TruncateDiv, self).__init__()
        self.truncdiv = P.TruncateDiv()

    def construct(self, x, y):
        res = self.truncdiv(x, y)
        return res


@pytest.mark.level0
@pytest.mark.platform_x86_cpu
@pytest.mark.env_onecard
def test_truncatediv_output_diff_types():
    """
    Feature: TruncateDiv cpu op
    Description: Test output values for different dtypes
    Expectation: Output matching expected values
    """
    input_x = Tensor(np.array([1, 4, -7]), mindspore.int32)
    input_y = Tensor(np.array([3, 3, 5]), mindspore.float32)

    input_x_1 = Tensor(np.array([1, 4, -3]), mindspore.float32)
    input_y_1 = Tensor(np.array([3, 3, 5]), mindspore.float32)

    input_x_2 = Tensor(np.array([1, 4, -3]), mindspore.int32)
    input_y_2 = Tensor(np.array([3, 3, 5]), mindspore.int32)

    input_x_3 = Tensor(np.array([1, 4, -3]), mindspore.int32)
    input_y_3 = Tensor(np.array([True]), mindspore.bool_)

    truncatediv_op = TruncateDiv()
    out = truncatediv_op(input_x, input_y).asnumpy()
    exp = np.array([0.33333334, 1.33333334, -1.4])
    diff = np.abs(out - exp)
    err = np.ones(shape=exp.shape) * 1.0e-5
    assert np.all(diff < err)
    assert out.shape == exp.shape

    out_1 = truncatediv_op(input_x_1, input_y_1).asnumpy()
    exp = np.array([0.33333334, 1.33333334, -0.6])
    diff = np.abs(out_1 - exp)
    err = np.ones(shape=exp.shape) * 1.0e-5
    assert np.all(diff < err)
    assert out.shape == exp.shape

    out_2 = truncatediv_op(input_x_2, input_y_2).asnumpy()
    exp = np.array([0, 1, 0])
    diff = np.abs(out_2 - exp)
    err = np.ones(shape=exp.shape) * 1.0e-5
    assert np.all(diff < err)
    assert out.shape == exp.shape

    out_3 = truncatediv_op(input_x_3, input_y_3).asnumpy()
    exp = np.array([1, 4, -3])
    diff = np.abs(out_3 - exp)
    err = np.ones(shape=exp.shape) * 1.0e-5
    assert np.all(diff < err)
    assert out.shape == exp.shape


@pytest.mark.level0
@pytest.mark.platform_x86_cpu
@pytest.mark.env_onecard
def test_truncatediv_output_broadcasting():
    """
    Feature: TruncateDiv cpu op
    Description: Test output values with broadcasting
    Expectation: Output matching expected values
    """
    input_x = Tensor(np.array([1, 4, -7]), mindspore.int32)
    input_y = Tensor(np.array([3]), mindspore.int32)

    out = TruncateDiv()(input_x, input_y).asnumpy()
    exp = np.array([0, 1, -2])
    diff = np.abs(out - exp)
    err = np.ones(shape=exp.shape) * 1.0e-5
    assert np.all(diff < err)
    assert out.shape == exp.shape


@pytest.mark.level0
@pytest.mark.platform_x86_cpu
@pytest.mark.env_onecard
def test_truncatediv_output_broadcasting_scalar():
    """
    Feature: TruncateDiv cpu op
    Description: Test output values for scalar input
    Expectation: Output matching expected values
    """
    input_x = Tensor(np.array([1, 4, -7]), mindspore.int32)
    input_y = 3

    out = TruncateDiv()(input_x, input_y).asnumpy()
    exp = np.array([0, 1, -2])
    diff = np.abs(out - exp)
    err = np.ones(shape=exp.shape) * 1.0e-5
    assert np.all(diff < err)
    assert out.shape == exp.shape


@pytest.mark.level0
@pytest.mark.platform_x86_cpu
@pytest.mark.env_onecard
def test_truncatediv_dtype_not_supported():
    """
    Feature: TruncateDiv cpu op
    Description: Test output for unsupported dtype
    Expectation: Raise TypeError exception
    """
    with pytest.raises(TypeError):
        input_x = Tensor(np.array([True, False]), mindspore.bool_)
        input_y = Tensor(np.array([True]), mindspore.bool_)

        _ = TruncateDiv()(input_x, input_y).asnumpy()
