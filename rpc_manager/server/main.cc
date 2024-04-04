#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include "rpc_manager.h"

void InitServer(std::string_view address){
    grpc::ServerBuilder builder;
    builder.AddListeningPort(address.data(),grpc::InsecureServerCredentials());

    monitor::GrpcManagerImpl grpc_server;
    builder.RegisterService(&grpc_server);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();

    return; 
}

int main(int argc,char* argv[]){

    if(argc != 2){
        std::cerr << "plese exec:server IP:port" << std::endl;
        return -1;
    }
    InitServer(argv[1]);
    return 0;
}