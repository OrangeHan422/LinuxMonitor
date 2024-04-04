#include "cpu_load_monitor.h"
#include "read_file.h"


namespace monitor{
void CpuLoadMonitor::UpdateOnce(monitor::proto::MonitorInfo& monitor_info){
    ReadFile file("/proc/loadavg");
    std::vector<std::string> container;
    file.ReadLine(container);

    m_load_avg_1 = std::stof(container[0]);
    m_load_avg_5 = std::stof(container[1]);
    m_load_avg_15 = std::stof(container[2]);
    auto cpu_load = monitor_info.mutable_cpu_load();
    cpu_load->set_load_avg_1(m_load_avg_1);
    cpu_load->set_load_avg_5(m_load_avg_5);
    cpu_load->set_load_avg_15(m_load_avg_15);
}

}// namespace monitor