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
#include <iostream>
#include "mindspore/core/utils/log_adapter.h"
#include "common/common_test.h"
#include "mindspore/lite/src/runtime/kernel/arm/nnacl/fp32/batchnorm.h"
#include "mindspore/lite/src/kernel_registry.h"
#include "mindspore/lite/src/lite_kernel.h"

namespace mindspore {
class TestBatchnormFp32 : public mindspore::CommonTest {
 public:
  TestBatchnormFp32() {}
};

TEST_F(TestBatchnormFp32, BNTest) {
  std::vector<float> in_data = {-11.18675,  11.433986,  11.386012, 11.245945,   -2.7614849, 14.692399,
                                -1.1983503, -6.6790967, 6.383416,  -13.3213005, -8.693595,  9.476344};
  std::vector<float> in_data1 = {12.352293, 5.122387, 14.249514};
  std::vector<float> in_data2 = {14.632595, 0.70900035, 11.179003};
  std::vector<lite::tensor::Tensor *> inputs_tensor;
  std::vector<lite::tensor::Tensor *> outputs_tensor;

  BatchNormParameter op_param;
  op_param.op_parameter_.type_ = schema::PrimitiveType_BatchNorm;
  op_param.epsilon_ = 0.001f;

  std::vector<int> shape = {1, 2, 2, 3};
  lite::tensor::Tensor input0_tensor;
  lite::tensor::Tensor input1_tensor;
  lite::tensor::Tensor input2_tensor;
  inputs_tensor.push_back(&input0_tensor);
  inputs_tensor.push_back(&input1_tensor);
  inputs_tensor.push_back(&input2_tensor);
  input0_tensor.SetData(in_data.data());
  input1_tensor.SetData(in_data1.data());
  input2_tensor.SetData(in_data2.data());
  input0_tensor.set_shape(shape);
  input1_tensor.set_shape({3});
  input2_tensor.set_shape({3});

  std::vector<float> output(12);
  std::vector<float> corr_out = {-6.1533737, 7.4904885,  -0.8563998, -0.289212,  -9.356432,  0.13245535,
                                 -3.5422924, -14.005781, -2.3525476, -6.7113695, -16.396551, -1.4275324};

  lite::tensor::Tensor output0_tensor;
  outputs_tensor.push_back(&output0_tensor);
  output0_tensor.SetData(output.data());
  output0_tensor.set_shape(shape);
  kernel::KernelKey desc = {kernel::KERNEL_ARCH::kCPU, kNumberTypeFloat32, schema::PrimitiveType_BatchNorm};
  auto creator = lite::KernelRegistry::GetInstance()->GetCreator(desc);
  ASSERT_NE(creator, nullptr);
  lite::Context ctx;
  ctx.thread_num_ = 1;
  kernel::LiteKernel *kernel =
    creator(inputs_tensor, outputs_tensor, reinterpret_cast<OpParameter *>(&op_param), &ctx, desc, nullptr);
  ASSERT_NE(kernel, nullptr);
  auto output_tensor_shape = output0_tensor.shape();
  kernel->Run();

  printf("==================output data=================\n");
  for (int i = 0; i < output0_tensor.ElementsNum(); i++) {
    std::cout << output[i] << " ,";
  }
  std::cout << std::endl;
  CompareOutputData(output.data(), corr_out.data(), output0_tensor.ElementsNum(), 0.001);

  input0_tensor.SetData(nullptr);
  input1_tensor.SetData(nullptr);
  input2_tensor.SetData(nullptr);
  output0_tensor.SetData(nullptr);
  MS_LOG(INFO) << "TestBathNormFp32 accuracy passed";
}
}  // namespace mindspore
