#include "rpc_manager.h"

namespace monitor{
::grpc::Status GrpcManagerImpl::SetMonitorInfo(::grpc::ServerContext* context,
                                            const ::monitor::proto::MonitorInfo* request,
                                            ::google::protobuf::Empty* response){
    m_monitor_info.Clear();
    m_monitor_info = *request;
    return grpc::Status::OK;
}
::grpc::Status GrpcManagerImpl::GetMonitorInfo(::grpc::ServerContext* context,
                                        const ::google::protobuf::Empty* request,
                                        ::monitor::proto::MonitorInfo* response){
    *response = m_monitor_info;
    return grpc::Status::OK;
}

} //namespace monitor