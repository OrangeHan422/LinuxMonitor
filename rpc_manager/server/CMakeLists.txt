set(SOURCES
    main.cc
    rpc_manager.cc)

add_executable(server ${SOURCES})
target_link_libraries(server
        PUBLIC
        monitor_proto)