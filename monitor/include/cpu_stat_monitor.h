#pragma once


#include "abstract_monitor.h"

namespace monitor
{
    class CpuStatMonitor:public AbstractMonitor{
        public:
            CpuStatMonitor() = default;
            void UpdateOnce(monitor::proto::MonitorInfo& monitor_info) override;
            void Stop() override {};
        private:
            struct CpuStat {
                std::string cpu_id;
                float user;
                float system;
                float idle;
                float nice;
                float io_wait;
                float irq;
                float soft_irq;
                float steal;
                float guest;
                float guest_nice;
            };
            std::unordered_map<std::string, struct CpuStat> m_cpu_stats;
    };
} // namespace monitor