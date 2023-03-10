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

"""RaggedTensorToTensor op"""
from mindspore.ops.op_info_register import op_info_register, AiCPURegOp, DataType

ragged_tensor_to_tensor_op_info = AiCPURegOp("RaggedTensorToTensor")                        \
    .fusion_type("OPAQUE")                                                                  \
    .attr("num_row_partition_tensors", "int")                                               \
    .attr("row_partition_types", "listStr")                                                 \
    .input(0, "shape", "required")                                                          \
    .input(1, "values", "required")                                                         \
    .input(2, "default_value", "required")                                                  \
    .input(3, "row_partition_tensors", "dynamic")                                           \
    .output(0, "result", "required")                                                        \
    .dtype_format(DataType.I32_Default, DataType.BOOL_Default, DataType.BOOL_Default,       \
                  DataType.I32_Default, DataType.BOOL_Default)                              \
    .dtype_format(DataType.I32_Default, DataType.I8_Default, DataType.I8_Default,           \
                  DataType.I32_Default, DataType.I8_Default)                                \
    .dtype_format(DataType.I32_Default, DataType.U8_Default, DataType.U8_Default,           \
                  DataType.I32_Default, DataType.U8_Default)                                \
    .dtype_format(DataType.I32_Default, DataType.I16_Default, DataType.I16_Default,         \
                  DataType.I32_Default, DataType.I16_Default)                               \
    .dtype_format(DataType.I32_Default, DataType.U16_Default, DataType.U16_Default,         \
                  DataType.I32_Default, DataType.U16_Default)                               \
    .dtype_format(DataType.I32_Default, DataType.I32_Default, DataType.I32_Default,         \
                  DataType.I32_Default, DataType.I32_Default)                               \
    .dtype_format(DataType.I32_Default, DataType.I64_Default, DataType.I64_Default,         \
                  DataType.I32_Default, DataType.I64_Default)                               \
    .dtype_format(DataType.I32_Default, DataType.F64_Default, DataType.F64_Default,         \
                  DataType.I32_Default, DataType.F64_Default)                               \
    .dtype_format(DataType.I32_Default, DataType.F32_Default, DataType.F32_Default,         \
                  DataType.I32_Default, DataType.F32_Default)                               \
    .dtype_format(DataType.I32_Default, DataType.F16_Default, DataType.F16_Default,         \
                  DataType.I32_Default, DataType.F16_Default)                               \
    .dtype_format(DataType.I64_Default, DataType.BOOL_Default, DataType.BOOL_Default,       \
                  DataType.I64_Default, DataType.BOOL_Default)                              \
    .dtype_format(DataType.I64_Default, DataType.I8_Default, DataType.I8_Default,           \
                  DataType.I64_Default, DataType.I8_Default)                                \
    .dtype_format(DataType.I64_Default, DataType.U8_Default, DataType.U8_Default,           \
                  DataType.I64_Default, DataType.U8_Default)                                \
    .dtype_format(DataType.I64_Default, DataType.I16_Default, DataType.I16_Default,         \
                  DataType.I64_Default, DataType.I16_Default)                               \
    .dtype_format(DataType.I64_Default, DataType.U16_Default, DataType.U16_Default,         \
                  DataType.I64_Default, DataType.U16_Default)                               \
    .dtype_format(DataType.I64_Default, DataType.I32_Default, DataType.I32_Default,         \
                  DataType.I64_Default, DataType.I32_Default)                               \
    .dtype_format(DataType.I64_Default, DataType.I64_Default, DataType.I64_Default,         \
                  DataType.I64_Default, DataType.I64_Default)                               \
    .dtype_format(DataType.I64_Default, DataType.F64_Default, DataType.F64_Default,         \
                  DataType.I64_Default, DataType.F64_Default)                               \
    .dtype_format(DataType.I64_Default, DataType.F32_Default, DataType.F32_Default,         \
                  DataType.I64_Default, DataType.F32_Default)                               \
    .dtype_format(DataType.I64_Default, DataType.F16_Default,                               \
                  DataType.F16_Default, DataType.I64_Default, DataType.F16_Default)         \
    .get_op_info()


@op_info_register(ragged_tensor_to_tensor_op_info)
def _ragged_tensor_to_tensor_aicpu():
    """RaggedTensorToTensor aicpu register"""
    return
