
set(SOURCES
   main.cc
   cpu_softirq_monitor.cc
   cpu_load_monitor.cc
   cpu_stat_monitor.cc
#    mem_monitor.cc
#    net_monitor.cc
   read_file.cc
)

add_executable(monitor ${SOURCES})

target_include_directories(monitor
        PUBLIC
        ${PROJECT_SOURCE_DIR}/monitor/include
        ${PROJECT_SOURCE_DIR}/rpc_manager
)

target_link_libraries(monitor
    PUBLIC
    monitor_proto
    stub
)