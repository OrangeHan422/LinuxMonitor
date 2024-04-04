#pragma once

#include <grpcpp/support/status.h>

#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor{
    class GrpcManagerImpl:public monitor::proto::GrpcManager::Service{
        public:
            GrpcManagerImpl() = default;
            virtual ~GrpcManagerImpl() = default;

            ::grpc::Status SetMonitorInfo(::grpc::ServerContext* context,
                                        const ::monitor::proto::MonitorInfo* request,
                                        ::google::protobuf::Empty* response);
            ::grpc::Status GetMonitorInfo(::grpc::ServerContext* context,
                                        const ::google::protobuf::Empty* request,
                                        ::monitor::proto::MonitorInfo* response);
        private:
            monitor::proto::MonitorInfo m_monitor_info;
    };
} // namespace monitor