#include "rpc_stub.h"

namespace monitor{
RpcStub::RpcStub(std::string_view addr){
    auto channel = grpc::CreateChannel(addr.data(),grpc::InsecureChannelCredentials());
    m_stub_ptr = monitor::proto::GrpcManager::NewStub(channel);
}

void RpcStub::SetMonitorInfo(const monitor::proto::MonitorInfo& monitor_info){
    ::grpc::ClientContext context;
    ::google::protobuf::Empty response;
    ::grpc::Status status = m_stub_ptr->SetMonitorInfo(&context,monitor_info,&response);
    if(!status.ok()){
        std::cerr << status.error_details() << std::endl;
    }
}

void RpcStub::GetMonitorInfo(monitor::proto::MonitorInfo* monitor_info){
    ::grpc::ClientContext context;
    ::google::protobuf::Empty request;
    ::grpc::Status status = m_stub_ptr->GetMonitorInfo(&context,request,monitor_info);
    if(!status.ok()){
        std::cerr << status.error_details() << std::endl;
    }
}
} // namespace monitor