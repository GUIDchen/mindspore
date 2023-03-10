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

#ifndef MINDSPORE_CCSRC_PLUGIN_DEVICE_GPU_KERNEL_NN_ADAPTIVE_MAX_POOL2D_GRAD_GPU_KERNEL_H_
#define MINDSPORE_CCSRC_PLUGIN_DEVICE_GPU_KERNEL_NN_ADAPTIVE_MAX_POOL2D_GRAD_GPU_KERNEL_H_

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <algorithm>
#include <functional>
#include "mindspore/core/ops/grad/adaptive_max_pool2d_grad.h"
#include "plugin/device/gpu/kernel/gpu_kernel.h"
#include "plugin/device/gpu/kernel/gpu_kernel_factory.h"
#include "plugin/device/gpu/kernel/cuda_impl/cuda_class/adaptive_max_pool_grad_helper.h"
namespace mindspore {
namespace kernel {
class AdaptiveMaxPool2DGradGpuKernelMod : public NativeGpuKernelMod {
 public:
  AdaptiveMaxPool2DGradGpuKernelMod() { attr_ptr_ = std::make_shared<cukernel::AdaptiveMaxPoolGradAttr>(); }
  ~AdaptiveMaxPool2DGradGpuKernelMod() override = default;

  bool Launch(const std::vector<AddressPtr> &inputs, const std::vector<AddressPtr> &workspace,
              const std::vector<AddressPtr> &outputs, void *stream_ptr) override;

  bool Init(const BaseOperatorPtr &base_operator, const std::vector<KernelTensorPtr> &inputs,
            const std::vector<KernelTensorPtr> &outputs) override;

  int Resize(
    const BaseOperatorPtr &base_operator, const std::vector<KernelTensorPtr> &inputs,
    const std::vector<KernelTensorPtr> &outputs,
    const std::map<uint32_t, tensor::TensorPtr> &inputsOnHost = std::map<uint32_t, tensor::TensorPtr>()) override;

  std::vector<KernelAttr> GetOpSupport() override;

 private:
  std::unique_ptr<cukernel::GpuKernelHelperBase> helper_ptr_{nullptr};
  std::shared_ptr<cukernel::AdaptiveMaxPoolGradAttr> attr_ptr_{nullptr};
};
}  // namespace kernel
}  // namespace mindspore

#endif  // MINDSPORE_CCSRC_PLUGIN_DEVICE_GPU_KERNEL_NN_ADAPTIVE_MAX_POOL2D_GRAD_GPU_KERNEL_H_
