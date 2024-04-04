#include "cpu_softirq_model.h"

namespace monitor{
CpuSoftirqModel::CpuSoftirqModel(QObject* parent):AbstractMonitorModel(parent){
    m_header.append("cpu_id");
    m_header.append("hi");
    m_header.append("timer");
    m_header.append("net_tx");
    m_header.append("net_rx");
    m_header.append("block");
    m_header.append("irq_poll");
    m_header.append("tasklet");
    m_header.append("sched");
    m_header.append("hrtimer");
    m_header.append("rcu");
}

int CpuSoftirqModel::rowCount(const QModelIndex& parent)const {
    return m_monitor_data.size();
}

int CpuSoftirqModel::columnCount(const QModelIndex& parent )const {
    return static_cast<int>(Softirq::COLUMN_MAX);
}

QVariant CpuSoftirqModel::headerData(int section,Qt::Orientation orientation,int role)const {
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        return m_header[section];
    }

    return AbstractMonitorModel::headerData(section,orientation,role);
}

QVariant CpuSoftirqModel::data(const QModelIndex& index,int role )const {
    if(index.column() < 0 || index.column() >= static_cast<int>(Softirq::COLUMN_MAX)){
        return QVariant();
    }

    if(role == Qt::DisplayRole){
        if(index.row() < m_monitor_data.size() && index.column() < static_cast<int>(Softirq::COLUMN_MAX)){
            return m_monitor_data[index.row()][index.column()];
        }
    }
    return QVariant();
}

void CpuSoftirqModel::UpdateMonitorInfo(const monitor::proto::MonitorInfo& monitor_info){
    beginResetModel();

    m_monitor_data.clear();
    std::vector<QVariant> container;
    for(int i = 0; i < monitor_info.soft_irq_size(); ++i){
        container.clear();
        fillData(container,monitor_info.soft_irq(i));
        m_monitor_data.push_back(container);
    }


    endResetModel();
    return;
}

void CpuSoftirqModel::fillData(std::vector<QVariant>& container,const monitor::proto::SoftIrq& soft_irq){
    for (int i = static_cast<int>(Softirq::CPU_ID); i < static_cast<int>(Softirq::COLUMN_MAX); i++) {
        switch (i) {
        case static_cast<int>(Softirq::CPU_ID):
            container.push_back(
                QVariant(QString::fromStdString(soft_irq.cpu_id())));
            break;
        case static_cast<int>(Softirq::HI):
            container.push_back(QVariant(soft_irq.hi()));
            break;
        case static_cast<int>(Softirq::TIMER):
            container.push_back(QVariant(soft_irq.timer()));
            break;
        case static_cast<int>(Softirq::NET_TX):
            container.push_back(QVariant(soft_irq.net_tx()));
            break;
        case static_cast<int>(Softirq::NET_RX):
            container.push_back(QVariant(soft_irq.net_rx()));
            break;
        case static_cast<int>(Softirq::BLOCK):
            container.push_back(QVariant(soft_irq.block()));
            break;
        case static_cast<int>(Softirq::IRQ_POLL):
            container.push_back(QVariant(soft_irq.irq_poll()));
            break;
        case static_cast<int>(Softirq::TASKLET):
            container.push_back(QVariant(soft_irq.tasklet()));
            break;
        case static_cast<int>(Softirq::SCHED):
            container.push_back(QVariant(soft_irq.sched()));
            break;
        case static_cast<int>(Softirq::HRTIMER):
            container.push_back(QVariant(soft_irq.hrtimer()));
            break;
        case static_cast<int>(Softirq::RCU):
            container.push_back(QVariant(soft_irq.rcu()));
            break;
        default:
            break;
        }
  }
    return;
}
}// namespace monitor