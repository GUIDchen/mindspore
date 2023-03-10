/**
 * Copyright 2020 Huawei Technologies Co., Ltd
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

#ifndef MINDSPORE_CCSRC_PLUGIN_DEVICE_GPU_KERNEL_CUDA_IMPL_CUDA_OPS_MULTINOMIAL_IMPL_CUH_
#define MINDSPORE_CCSRC_PLUGIN_DEVICE_GPU_KERNEL_CUDA_IMPL_CUDA_OPS_MULTINOMIAL_IMPL_CUH_
#include <curand_kernel.h>
#include "plugin/device/gpu/kernel/cuda_impl/cuda_ops/cuda_common.h"

CUDA_LIB_EXPORT void InitRandState(int seed, int num, curandState *state, cudaStream_t stream);
template <typename T, typename S>
CUDA_LIB_EXPORT void Multinomial(int row, int col, T *probs, curandState *rand_state, int64_t *num_sample, S *output,
                                 cudaStream_t stream);
template <typename T>
CUDA_LIB_EXPORT void CheckNonNeg(const size_t size, const T *input, T *output, cudaStream_t stream);
template <typename T>
CUDA_LIB_EXPORT void CheckZero(const size_t distributions, const size_t categories, const T *input, T *output,
                               cudaStream_t stream);

#endif  // MINDSPORE_CCSRC_PLUGIN_DEVICE_GPU_KERNEL_CUDA_IMPL_CUDA_OPS_MULTINOMIAL_IMPL_CUH_
