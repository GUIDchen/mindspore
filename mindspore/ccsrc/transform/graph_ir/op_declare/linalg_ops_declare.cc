/**
 * Copyright 2022 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "transform/graph_ir/op_declare/linalg_ops_declare.h"

namespace mindspore::transform {
// Ger
INPUT_MAP(Ger) = {{1, INPUT_DESC(x1)}, {2, INPUT_DESC(x2)}};
ATTR_MAP(Ger) = EMPTY_ATTR_MAP;
OUTPUT_MAP(Ger) = {{0, OUTPUT_DESC(y)}};
REG_ADPT_DESC(Ger, prim::kGer, ADPT_DESC(Ger))
}  // namespace mindspore::transform
