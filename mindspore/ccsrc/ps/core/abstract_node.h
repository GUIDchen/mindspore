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

#ifndef MINDSPORE_CCSRC_PS_CORE_ABSTRACT_NODE_H_
#define MINDSPORE_CCSRC_PS_CORE_ABSTRACT_NODE_H_

#include <utility>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <unordered_map>

#include "ps/core/node.h"
#include "ps/core/communicator/message.h"
#include "utils/ms_exception.h"

namespace mindspore {
namespace ps {
namespace core {
class AbstractNode : public Node {
 public:
  AbstractNode()
      : heart_beat_thread_(nullptr),
        client_to_scheduler_thread_(nullptr),
        client_to_scheduler_(nullptr),
        server_(nullptr),
        server_thread_(nullptr),
        worker_num_(-1),
        server_num_(-1) {}
  ~AbstractNode() override = default;

  typedef void (AbstractNode::*ResponseHandler)(std::shared_ptr<MessageMeta> meta, const void *data, size_t size);
  typedef void (AbstractNode::*ServerHandler)(std::shared_ptr<TcpConnection> conn, std::shared_ptr<MessageMeta> meta,
                                              const Protos &protos, const void *data, size_t size);

  using DataPtr = std::shared_ptr<unsigned char[]>;
  using VectorPtr = std::shared_ptr<std::vector<unsigned char>>;

  bool Broadcast(const enum NodeRole &node_role, const DataPtr &message, size_t size, int command,
                 const uint32_t &timeout = kCommTimeoutInSeconds);

  void set_event_callback(const OnNodeEventMessage &event);
  // When the business layer finish scale out, it should call this function
  void set_ready_for_scale_out();
  // When the business layer finish scale in, it should call this function
  void set_ready_for_scale_in();

  bool Send(const enum NodeRole &node_role, const uint32_t &rank_id, const DataPtr &data, size_t len, int command,
            const uint32_t &timeout = kCommTimeoutInSeconds);
  bool Send(const NodeRole &node_role, const std::vector<uint32_t> &rank_ids, const std::vector<DataPtr> &data,
            const std::vector<size_t> &lens, int command, const uint32_t &timeout = kCommTimeoutInSeconds);
  bool Send(const enum NodeRole &node_role, const uint32_t &rank_id, const DataPtr &message, size_t len, int command,
            VectorPtr *output, const uint32_t &timeout = kCommTimeoutInSeconds);
  bool Send(const NodeRole &node_role, const std::vector<uint32_t> &rank_ids, const std::vector<DataPtr> &data,
            const std::vector<size_t> &data_lens, int command, std::vector<VectorPtr> *output,
            const uint32_t &timeout = kCommTimeoutInSeconds);

  uint64_t CollectiveSendAsync(const enum NodeRole &node_role, const uint32_t &rank_id, const void *data, size_t size);
  std::pair<uint32_t, uint64_t> CollectiveReceiveAsync(const enum NodeRole &node_role, const uint32_t &rank_id,
                                                       VectorPtr *output);
  bool CollectiveWait(std::pair<uint32_t, uint64_t> request_id, const uint32_t &timeout = kCommTimeoutInSeconds);

  int32_t worker_num() const;
  int32_t server_num() const;

  ClusterState cluster_state() const;

 protected:
  void Register(const std::shared_ptr<TcpClient> &client);
  bool Heartbeat(const std::shared_ptr<TcpClient> &client);
  void FetchServers(const std::shared_ptr<TcpClient> &client);

  void ProcessRegisterResp(std::shared_ptr<MessageMeta> meta, const void *data, size_t size);
  void ProcessHeartbeatResp(std::shared_ptr<MessageMeta> meta, const void *data, size_t size);
  void ProcessFetchServersResp(std::shared_ptr<MessageMeta> meta, const void *data, size_t size);

  void ProcessSendMetadata(std::shared_ptr<TcpConnection> conn, std::shared_ptr<MessageMeta> meta, const Protos &protos,
                           const void *data, size_t size);
  void ProcessFinish(std::shared_ptr<TcpConnection> conn, std::shared_ptr<MessageMeta> meta, const Protos &protos,
                     const void *data, size_t size);

  void ProcessScaleOut(std::shared_ptr<TcpConnection> conn, std::shared_ptr<MessageMeta> meta, const Protos &protos,
                       const void *data, size_t size);

  void ProcessScaleIn(std::shared_ptr<TcpConnection> conn, std::shared_ptr<MessageMeta> meta, const Protos &protos,
                      const void *data, size_t size);

  void StartHeartbeatTimer(const std::shared_ptr<TcpClient> &client);
  void UpdateSchedulerTime();
  bool CheckSchedulerTimeout() const;
  bool Disconnect(const std::shared_ptr<TcpClient> &client, const uint32_t &timeout);
  bool WaitForDisconnect(const uint32_t &timeout);
  bool InitClientToScheduler();
  const std::shared_ptr<TcpClient> &GetOrCreateTcpClient(const int &rank_id);

  void ProcessSendDataResp(std::shared_ptr<MessageMeta> meta, const Protos &protos, const void *data, size_t size);
  void RunMessageCallback(const uint64_t &request_id);
  void set_message_callback(const uint64_t &request_id, const MessageCallback &callback);
  void RunReceiveCallback(std::shared_ptr<MessageMeta> meta, const Protos &protos, const void *data, size_t size);
  uint64_t NextExpectedRankRequestId(const uint32_t &rank_id);
  uint64_t NextActualRankRequestId(const uint32_t &rank_id);
  void InitCommandHandler();
  void InitServerHandler();

  // when initializing the node, should initializing the node info.
  void InitNodeInfo(const NodeRole &role);
  // Initialize worker num and server num by cluster config.
  void InitNodeNum();

  std::unique_ptr<std::thread> heart_beat_thread_;
  std::unique_ptr<std::thread> client_to_scheduler_thread_;
  std::shared_ptr<TcpClient> client_to_scheduler_;

  OnNodeEventMessage on_node_event_message_;

  // the key is: <node_role,rank_id>, the value is: <ip, port>
  std::map<std::pair<NodeRole, uint32_t>, std::pair<std::string, uint16_t>> nodes_address_;
  std::mutex client_mutex_;
  // the map's key is: rank_id
  std::unordered_map<int, std::shared_ptr<TcpClient>> connected_nodes_;

  // the key is: request_id, the value is: <rank_id, RecvMessage>
  std::unordered_map<uint64_t, std::unordered_map<uint32_t, VectorPtr>> receive_messages_;
  std::map<std::pair<uint32_t, uint64_t>, bool> receive_messages_done_;
  std::mutex receive_messages_mutex_;
  // the key is: request_id
  std::unordered_map<uint64_t, MessageCallback> message_callbacks_;
  std::mutex message_callbacks_mutex_;

  // the key is <rank_id, rank_request_id>
  std::map<std::pair<uint32_t, uint64_t>, std::shared_ptr<std::vector<unsigned char>>> received_data_;
  std::mutex receive_callbacks_mutex_;
  // the key is <rank_id, rank_request_id>
  std::map<std::pair<uint32_t, uint64_t>, MessageCallback> receive_callbacks_;
  std::condition_variable receive_cond_;

  // the key is rank_id, the value is rank_id's expected request_id
  std::unordered_map<uint32_t, uint64_t> expected_rank_request_ids_;
  // the key is rank_id, the value is rank_id's actual request_id
  std::unordered_map<uint32_t, uint64_t> actual_rank_request_ids_;
  std::mutex rank_request_ids_mutex;
  timeval scheduler_time_{0, 0};
  std::unordered_map<NodeCommand, ResponseHandler> handlers_;
  std::unordered_map<NodeCommand, ServerHandler> server_handler_;

  // Workers and servers launch the server to process command: FINISH,SCALE_OUT,SCALE_IN,SEND_METADATA
  std::shared_ptr<TcpServer> server_;
  std::unique_ptr<std::thread> server_thread_;

  int32_t worker_num_;
  int32_t server_num_;
};
}  // namespace core
}  // namespace ps
}  // namespace mindspore
#endif  // MINDSPORE_CCSRC_PS_CORE_ABSTRACT_NODE_H_
