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
#ifndef MINDSPORE_LITE_SRC_EXTENDRT_PLUGIN_ASCEND_GE_EXECUTOR_PLUGIN_H_
#define MINDSPORE_LITE_SRC_EXTENDRT_PLUGIN_ASCEND_GE_EXECUTOR_PLUGIN_H_

#include <string>
#include "include/api/status.h"
#include "utils/log_adapter.h"
#include "mindapi/base/macros.h"
#include "base/base.h"

namespace mindspore::lite {
class AscendGeExecutorPluginImplBase {
 public:
  AscendGeExecutorPluginImplBase() = default;
  virtual ~AscendGeExecutorPluginImplBase() = default;

  virtual Status AscendGeDeviceContextInitialize() = 0;
  virtual void AscendGeDeviceContextDestroy() const = 0;
  virtual Status AdaptGraph(FuncGraphPtr graph) const = 0;
};

class MS_API AscendGeExecutorPlugin {
 public:
  static AscendGeExecutorPlugin &GetInstance();
  bool Register();

  Status InitializeGeContext();
  void DestroyGeContext();
  void AdaptGraph(FuncGraphPtr graph);

 private:
  AscendGeExecutorPlugin();
  ~AscendGeExecutorPlugin();

  std::string plugin_path_;
  void *handle_ = nullptr;
  bool is_registered_ = false;
  AscendGeExecutorPluginImplBase *ge_plugin_impl_ = nullptr;
};
}  // namespace mindspore::lite
#endif  // MINDSPORE_LITE_SRC_EXTENDRT_PLUGIN_ASCEND_GE_EXECUTOR_PLUGIN_H_
