/**
 * Copyright 2020-2022 Huawei Technologies Co., Ltd
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

#ifndef MINDSPORE_CCSRC_BACKEND_KERNEL_COMPILER_CPU_STRIDED_SLICE_GRAD_V2_CPU_KERNEL_H_
#define MINDSPORE_CCSRC_BACKEND_KERNEL_COMPILER_CPU_STRIDED_SLICE_GRAD_V2_CPU_KERNEL_H_

#include <memory>
#include <string>
#include <vector>

#include "plugin/device/cpu/kernel/nnacl/fp32_grad/strided_slice_grad.h"
#include "plugin/device/cpu/kernel/cpu_kernel.h"
#include "plugin/factory/ms_factory.h"

namespace mindspore {
namespace kernel {
constexpr auto kStridedSliceV2Grad = "StridedSliceV2Grad";
constexpr auto kUnknown = "Unknown";

class StridedSliceV2GradCpuKernelMod : public DeprecatedNativeCpuKernelMod {
 public:
  StridedSliceV2GradCpuKernelMod() = default;

  explicit StridedSliceV2GradCpuKernelMod(const std::string &kernel_type) : kernel_type_(kernel_type) {}

  ~StridedSliceV2GradCpuKernelMod() override = default;

  void InitKernel(const CNodePtr &kernel_node) override;

  bool Launch(const std::vector<AddressPtr> &inputs, const std::vector<AddressPtr> &workspace,
              const std::vector<AddressPtr> &outputs) override;

 protected:
  std::vector<KernelAttr> GetOpSupport() override;

 private:
  template <typename T>
  bool LaunchKernel(const std::vector<kernel::AddressPtr> &inputs, const std::vector<kernel::AddressPtr> &outputs);

  template <typename T>
  void InitParams(const std::vector<kernel::AddressPtr> &inputs);

  void ClearVectors();

  void ExpandAllMemberDims(size_t expand_dims = 4);

  int SignOfStride(size_t axis) const;

  void FormatArgs(bool stride);

  template <typename T>
  bool StridedSliceV2GradCal(const std::vector<kernel::AddressPtr> &inputs,
                             const std::vector<kernel::AddressPtr> &outputs, T *input_addr, T *output_addr);

  template <typename T>
  bool CalStridedSliceV2Grad(const std::vector<kernel::AddressPtr> &inputs,
                             const std::vector<kernel::AddressPtr> &outputs, T *input, T *output);

  std::vector<int> begin_;
  std::vector<int> end_;
  std::vector<int> strides_;
  std::vector<int> size_;
  ShapeVector input_shape_;
  int shape_dim_output;
  int slice_len;
  std::vector<size_t> input_element_num_;
  ShapeVector output_shape_;
  std::vector<size_t> output_element_num_;
  TypeId dtype_{kTypeUnknown};
  TypeId dtype_grad_attr{kTypeUnknown};
  std::string kernel_type_{kUnknown};
};
}  // namespace kernel
}  // namespace mindspore
#endif  // MINDSPORE_CCSRC_BACKEND_KERNEL_COMPILER_CPU_STRIDED_SLICE_GRAD_V2_CPU_KERNEL_H_