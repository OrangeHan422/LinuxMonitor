#include <chrono>
#include "abstract_monitor.h"

namespace monitor{
class CpuSoftirqMonitor:public AbstractMonitor{
    public:
        CpuSoftirqMonitor() = default;
        void UpdateOnce(monitor::proto::MonitorInfo& monitor_info) override;
        void Stop() override{};
    private:
        struct SoftIrq{
            std::string cpu_id;
            int64_t hi;
            int64_t timer;
            int64_t net_tx;
            int64_t net_rx;
            int64_t block;
            int64_t irq_poll;
            int64_t tasklet;
            int64_t sched;
            int64_t hrtimer;
            int64_t rcu;
            std::chrono::time_point<std::chrono::steady_clock>  timepoint;
        };
        std::unordered_map<std::string,struct SoftIrq> m_cpu_softirqs;

};
} // namespace monitor