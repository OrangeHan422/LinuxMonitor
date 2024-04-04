set(SOURCES
    rpc_stub.cc)

add_library(stub ${SOURCES})

target_link_libraries(stub
            PUBLIC
            monitor_proto)             