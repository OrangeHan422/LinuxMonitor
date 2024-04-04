#pragma once


#include "abstract_monitor.h"

namespace monitor
{
    class CpuLoadMonitor:public AbstractMonitor{
        public:
            CpuLoadMonitor() = default;
            void UpdateOnce(monitor::proto::MonitorInfo& monitor_info) override;
            void Stop() override {};
        private:
            float m_load_avg_1;
            float m_load_avg_5;
            float m_load_avg_15;
    };
} // namespace monitor

