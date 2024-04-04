find_package(Qt5 
  COMPONENTS
  Core
  Widgets REQUIRED 
)

set(SOURCES main.cc
            abstract_monitor_model.cc
            cpu_load_model.cc
            cpu_softirq_model.cc
            cpu_stat_model.cc
            monitor_widget.cc)

add_executable(display ${SOURCES})  
set_target_properties(display PROPERTIES AUTOMOC TRUE)

target_include_directories(display
            PUBLIC
            ${PROJECT_SOURCE_DIR}/rpc_manager
)


target_link_libraries(display
            PUBLIC
            stub
            monitor_proto
            Qt5::Widgets
            Qt5::Core
)

            

