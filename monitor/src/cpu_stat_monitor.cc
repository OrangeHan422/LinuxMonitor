#include "cpu_stat_monitor.h"

namespace monitor{
void CpuStatMonitor::UpdateOnce(monitor::proto::MonitorInfo& monitor_info){
    ReadFile file("/proc/stat");
    std::vector<std::string> dood_stat;
    while(file.ReadLine(dood_stat)){
        if(dood_stat[0].find("cpu") != std::string::npos){
            struct CpuStat fresh_dood;
            fresh_dood.cpu_id = dood_stat[0];
            fresh_dood.user = std::stof(dood_stat[1]);
            fresh_dood.nice = std::stof(dood_stat[2]);
            fresh_dood.system = std::stof(dood_stat[3]);
            fresh_dood.idle = std::stof(dood_stat[4]);
            fresh_dood.io_wait = std::stof(dood_stat[5]);
            fresh_dood.irq = std::stof(dood_stat[6]);
            fresh_dood.soft_irq = std::stof(dood_stat[7]);
            fresh_dood.steal = std::stof(dood_stat[8]);
            fresh_dood.guest = std::stof(dood_stat[9]);
            fresh_dood.guest_nice = std::stof(dood_stat[10]);

            auto it = m_cpu_stats.find(fresh_dood.cpu_id);
            if(it != std::end(m_cpu_stats)){
                struct CpuStat unfresh_dood = it->second;
                auto cpu_stat_message = monitor_info.add_cpu_stat();
                float new_cpu_total_time = fresh_dood.user + fresh_dood.system + fresh_dood.idle
                                            + fresh_dood.nice + fresh_dood.io_wait + fresh_dood.irq
                                            + fresh_dood.soft_irq + fresh_dood.steal;
                float old_cpu_total_time = unfresh_dood.user + unfresh_dood.system + unfresh_dood.idle
                            + unfresh_dood.nice + unfresh_dood.io_wait + unfresh_dood.irq
                            + unfresh_dood.soft_irq + unfresh_dood.steal;
                float new_cpu_busy_time = fresh_dood.user + fresh_dood.system +
                                  fresh_dood.nice + fresh_dood.irq +
                                  fresh_dood.soft_irq + fresh_dood.steal;
                float old_cpu_busy_time = unfresh_dood.user + unfresh_dood.system + unfresh_dood.nice + unfresh_dood.irq +
                                        unfresh_dood.soft_irq + unfresh_dood.steal;

                float cpu_percent = (new_cpu_busy_time - old_cpu_busy_time) /
                                    (new_cpu_total_time - old_cpu_total_time) * 100.00;
                float cpu_user_percent = (fresh_dood.user - unfresh_dood.user) /
                                        (new_cpu_total_time - old_cpu_total_time) *
                                        100.00;
                float cpu_system_percent = (fresh_dood.system - unfresh_dood.system) /
                                        (new_cpu_total_time - old_cpu_total_time) *
                                        100.00;
                float cpu_nice_percent = (fresh_dood.nice - unfresh_dood.nice) /
                                        (new_cpu_total_time - old_cpu_total_time) *
                                        100.00;
                float cpu_idle_percent = (fresh_dood.idle - unfresh_dood.idle) /
                                        (new_cpu_total_time - old_cpu_total_time) *
                                        100.00;
                float cpu_io_wait_percent = (fresh_dood.io_wait - unfresh_dood.io_wait) /
                                            (new_cpu_total_time - old_cpu_total_time) *
                                            100.00;
                float cpu_irq_percent = (fresh_dood.irq - unfresh_dood.irq) /
                                        (new_cpu_total_time - old_cpu_total_time) *
                                        100.00;
                float cpu_soft_irq_percent = (fresh_dood.soft_irq - unfresh_dood.soft_irq) /
                                            (new_cpu_total_time - old_cpu_total_time) *
                                            100.00;
                
                cpu_stat_message->set_cpu_id(fresh_dood.cpu_id);
                cpu_stat_message->set_cpu_percent(cpu_percent);
                cpu_stat_message->set_user_percent(cpu_user_percent);
                cpu_stat_message->set_system_percent(cpu_system_percent);
                cpu_stat_message->set_nice_percent(cpu_nice_percent);
                cpu_stat_message->set_idle_percent(cpu_idle_percent);
                cpu_stat_message->set_io_wait_percent(cpu_io_wait_percent);
                cpu_stat_message->set_irq_percent(cpu_irq_percent);
                cpu_stat_message->set_soft_irq_percent(cpu_soft_irq_percent);
            }
            m_cpu_stats[fresh_dood.cpu_id] = fresh_dood;
        }//if(dood_stat[0].find("cpu") != std::string::npos)
        dood_stat.clear();
    }//while(file.ReadLine(dood_stat))
}

}//namespace monitor