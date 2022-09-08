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
#ifndef MINDSPORE_CCSRC_BACKEND_KERNEL_COMPILER_ACL_ACL_UTILS_H_
#define MINDSPORE_CCSRC_BACKEND_KERNEL_COMPILER_ACL_ACL_UTILS_H_
#include <memory>
#include <string>
#include <vector>
#include "kernel/kernel.h"
#include "mindapi/base/type_id.h"
#include "acl/acl_op_compiler.h"
#include "acl/acl_base.h"

namespace mindspore {
namespace kernel {
class AclOpDesc {
 public:
  explicit AclOpDesc(const std::string &op_type);
  ~AclOpDesc();

  void AddInputTensor(const AnfNodePtr &anf_node, const size_t input_num, const std::vector<AddressPtr> &inputs,
                      const std::vector<size_t> &input_size_list);
  void AddOutputTensor(const AnfNodePtr &anf_node, const size_t output_num, const std::vector<AddressPtr> &outputs,
                       const std::vector<size_t> &output_size_list);
  void AddTensorAttr(const std::string &attr_name, const ValuePtr &value, const std::string &op_type);

  std::vector<aclTensorDesc *> input_tensor_desc() const { return input_tensor_desc_; }
  std::vector<aclTensorDesc *> output_tensor_desc() const { return output_tensor_desc_; }
  std::vector<aclDataBuffer *> input_tensor_data() const { return input_tensor_data_; }
  std::vector<aclDataBuffer *> output_tensor_data() const { return output_tensor_data_; }
  aclopAttr *acl_attr() const { return acl_attr_; }

 protected:
  void SetListAttr(const std::string &attr_name, const ValuePtr &value);

 private:
  std::string op_type_;
  aclopAttr *acl_attr_{nullptr};
  std::vector<aclTensorDesc *> input_tensor_desc_{};
  std::vector<aclTensorDesc *> output_tensor_desc_{};
  std::vector<aclDataBuffer *> input_tensor_data_{};
  std::vector<aclDataBuffer *> output_tensor_data_{};
};

class AclUtils {
 public:
  static aclDataType ConvertTypeIdToAclType(const TypeId &type_id);

  static aclFormat ConvertFormatToAclFormat(const std::string &format);
};
}  // namespace kernel
}  // namespace mindspore

#endif  // MINDSPORE_CCSRC_BACKEND_KERNEL_COMPILER_ACL_ACL_UTILS_H_