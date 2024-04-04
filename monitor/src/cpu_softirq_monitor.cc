#include "cpu_softirq_monitor.h"

namespace monitor{
void CpuSoftirqMonitor::UpdateOnce(monitor::proto::MonitorInfo& monitor_info){
    ReadFile file("/proc/softirqs");
    std::vector<std::string> dood_softirq;
    std::vector<std::vector<std::string>> pile_dood_softirq;
    while(file.ReadLine(dood_softirq)){
        pile_dood_softirq.push_back(dood_softirq);
        dood_softirq.clear();
    }

    for(int i = 0; i < pile_dood_softirq[0].size()-1 ; ++i){
        std::string cpu_id = pile_dood_softirq[0][i];
        struct SoftIrq fresh_dood;
        fresh_dood.cpu_id = cpu_id;
        fresh_dood.hi = std::stoll(pile_dood_softirq[1][i+1]);
        fresh_dood.timer = std::stoll(pile_dood_softirq[2][i+1]);
        fresh_dood.net_tx = std::stoll(pile_dood_softirq[3][i+1]);
        fresh_dood.net_rx = std::stoll(pile_dood_softirq[4][i+1]);
        fresh_dood.block = std::stoll(pile_dood_softirq[5][i+1]);
        fresh_dood.irq_poll = std::stoll(pile_dood_softirq[6][i+1]);
        fresh_dood.tasklet = std::stoll(pile_dood_softirq[7][i+1]);
        fresh_dood.sched = std::stoll(pile_dood_softirq[8][i+1]);
        fresh_dood.hrtimer = std::stoll(pile_dood_softirq[9][i+1]);
        fresh_dood.rcu = std::stoll(pile_dood_softirq[10][i+1]);
        fresh_dood.timepoint = std::chrono::steady_clock::now();


        const auto iter = m_cpu_softirqs.find(cpu_id);
        if(iter != m_cpu_softirqs.end()){
            const auto unfresh_dood = (*iter).second;
            const auto period = fresh_dood.timepoint - unfresh_dood.timepoint;
            auto one_cpu_softirq_message = monitor_info.add_soft_irq();
            one_cpu_softirq_message->set_cpu_id(fresh_dood.cpu_id);
            one_cpu_softirq_message->set_hi((fresh_dood.hi - unfresh_dood.hi) / (period.count()/1000000000));
            one_cpu_softirq_message->set_timer((fresh_dood.timer - unfresh_dood.timer) / (period.count()/1000000000));
            one_cpu_softirq_message->set_net_tx((fresh_dood.net_tx - unfresh_dood.net_tx) / (period.count()/1000000000));
            one_cpu_softirq_message->set_net_rx((fresh_dood.net_rx - unfresh_dood.net_rx) / (period.count()/1000000000));
            one_cpu_softirq_message->set_block((fresh_dood.block - unfresh_dood.block) / (period.count()/1000000000));
            one_cpu_softirq_message->set_irq_poll((fresh_dood.irq_poll - unfresh_dood.irq_poll) / (period.count()/1000000000));
            one_cpu_softirq_message->set_tasklet((fresh_dood.tasklet - unfresh_dood.tasklet) / (period.count()/1000000000));
            one_cpu_softirq_message->set_sched((fresh_dood.sched - unfresh_dood.sched) / (period.count()/1000000000));
            one_cpu_softirq_message->set_hrtimer((fresh_dood.hrtimer - unfresh_dood.hrtimer) / (period.count()/1000000000));
            one_cpu_softirq_message->set_rcu((fresh_dood.rcu - unfresh_dood.rcu) / (period.count()*1000000000));
        }
        m_cpu_softirqs[cpu_id] = fresh_dood;
    }
}

}// namespace monitor