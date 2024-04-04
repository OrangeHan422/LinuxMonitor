#include <cstdlib>
#include <memory>
#include <thread>

#include "read_file.h"
#include "cpu_load_monitor.h"
#include "cpu_softirq_monitor.h"
#include "cpu_stat_monitor.h"
#include "stub/rpc_stub.h"

int main(int argc,char* argv[])
{
    if(argc != 2){
        std::cerr << "plese exec:monitor IP:port" << std::endl;
        return -1;
    }
    std::vector<std::shared_ptr<monitor::AbstractMonitor>> monitors;
    monitors.emplace_back(std::make_shared<monitor::CpuLoadMonitor>());
    monitors.emplace_back(std::make_shared<monitor::CpuSoftirqMonitor>());
    monitors.emplace_back(std::make_shared<monitor::CpuStatMonitor>());


    monitor::RpcStub skeleton(argv[1]);
    const char *name = std::getenv("USER");
    std::unique_ptr<std::thread> worker{std::make_unique<std::thread>([&name,&monitors,&skeleton](){
        while (true)
        {
            monitor::proto::MonitorInfo monitor_info;
            monitor_info.set_name(std::string(name));
            for(auto &mon:monitors){
                mon->UpdateOnce(monitor_info);
            }

            skeleton.SetMonitorInfo(monitor_info);
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
        
    })};
    
    worker->join();
    return 0;
}