#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include "rpc_manager.h"

const char* k_ServerListening = "0.0.0.0:50051";
void InitServer(){
    grpc::ServerBuilder builder;
    builder.AddListeningPort(k_ServerListening,grpc::InsecureServerCredentials());

    monitor::GrpcManagerImpl grpc_server;
    builder.RegisterService(&grpc_server);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();

    return; 
}

int main(){
    InitServer();
    return 0;
}