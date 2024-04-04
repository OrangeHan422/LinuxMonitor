#pragma once

#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/grpcpp.h>
#include <string_view>
#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor{
class RpcStub{
    public:
        explicit RpcStub(std::string_view addr);
        ~RpcStub() = default;
        void SetMonitorInfo(const monitor::proto::MonitorInfo& monitor_info);
        void GetMonitorInfo(monitor::proto::MonitorInfo* monitor_info);
    private:
        std::unique_ptr<monitor::proto::GrpcManager::Stub> m_stub_ptr;
};

} //namespace monitor