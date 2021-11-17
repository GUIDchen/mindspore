/**
 * Copyright 2021 Huawei Technologies Co., Ltd
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

#ifndef MINDSPORE_CCSRC_RUNTIME_FRAMEWORK_ACTOR_CONTROLFLOW_STACK_ACTOR_H_
#define MINDSPORE_CCSRC_RUNTIME_FRAMEWORK_ACTOR_CONTROLFLOW_STACK_ACTOR_H_

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <stack>
#include "runtime/framework/actor/actor_common.h"
#include "runtime/framework/actor/control_flow/control_actor.h"

namespace mindspore {
namespace runtime {
// Stack actor is used to record those device actors that need additional storage in recursive scenes.
// The execution steps of the stack actor:
// 1. Accept a copy of all direct parameters and push them to the stack
// 2. Notify gather actor can be executed
// 3. Receive the output of exit actor
// 4. Send output.
class StackActor : public ControlActor {
 public:
  StackActor(const std::string &name, const std::vector<KernelWithIndex> &parameters);
  ~StackActor() override = default;

  void Init() override;
  // The input data of the stack actor needs to be pushed into the stack according to the input index, so it is
  // implemented separately.
  void RunOpData(OpData<DeviceTensor> *const input_data, OpContext<DeviceTensor> *const context) override;

 protected:
  void FetchInput(OpContext<DeviceTensor> *const context) override;
  bool CheckRunningCondition(const OpContext<DeviceTensor> *context) const override;
  void EraseInput(const OpContext<DeviceTensor> *const context) override;

 private:
  friend class ControlNodeScheduler;

  void FillStack(OpData<DeviceTensor> *const input_data, OpContext<DeviceTensor> *const context);

  // The device tensors created and stored by the stack.
  std::vector<DeviceTensorPtr> created_device_tensors_;

  // The input data records that the stack actor is copied from the input nodes and needs to be stored in the
  // device tensor in the stack.
  std::unordered_map<int, std::unordered_map<size_t, std::stack<DeviceTensor *>>> input_parameter_data_;
  // Input parameter data num represents the number of actor's input come from funcgraph itself, these inputs
  // will be ranked at the front of input.
  size_t input_parameter_data_num_{0};
  // The backend parameter is used to save the backend node corresponding to the device tensor in the stack.
  // When these device tensors are used as output, they need to be placed in the node of the result arrow,
  // so these nodes need to be saved.
  std::vector<KernelWithIndex> backend_parameters_;
};

using StackActorPtr = std::shared_ptr<StackActor>;
}  // namespace runtime
}  // namespace mindspore

#endif  // MINDSPORE_CCSRC_RUNTIME_FRAMEWORK_ACTOR_CONTROLFLOW_STACK_ACTOR_H_
