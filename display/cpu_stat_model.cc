#include "cpu_stat_model.h"

namespace monitor{
CpuStatModel::CpuStatModel(QObject* parent):AbstractMonitorModel(parent){
    m_header.append("cpu_id");
    m_header.append("cpu_percent");
    m_header.append("user_percent");
    m_header.append("system_percent");
    m_header.append("nice_percent");
    m_header.append("idle_percent");
    m_header.append("io_wait_percent");
    m_header.append("irq_percent");
    m_header.append("soft_irq_percent");
}

int CpuStatModel::rowCount(const QModelIndex& parent)const {
    return m_monitor_data.size();
}

int CpuStatModel::columnCount(const QModelIndex& parent )const {
    return static_cast<int>(CpuStat::COLUMN_MAX);
}

QVariant CpuStatModel::headerData(int section,Qt::Orientation orientation,int role)const {
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        return m_header[section];
    }

    return AbstractMonitorModel::headerData(section,orientation,role);
}

QVariant CpuStatModel::data(const QModelIndex& index,int role )const {
    if(index.column() < 0 || index.column() >= static_cast<int>(CpuStat::COLUMN_MAX)){
        return QVariant();
    }

    if(role == Qt::DisplayRole){
        if(index.row() < m_monitor_data.size() && index.column() < static_cast<int>(CpuStat::COLUMN_MAX)){
            return m_monitor_data[index.row()][index.column()];
        }
    }
    return QVariant();
}

void CpuStatModel::UpdateMonitorInfo(const monitor::proto::MonitorInfo& monitor_info){
    beginResetModel();

    m_monitor_data.clear();
    std::vector<QVariant> container;
    for(int i = 0; i < monitor_info.cpu_stat_size(); ++i){
        container.clear();
        fillData(container,monitor_info.cpu_stat(i));
        m_monitor_data.push_back(container);
    }


    endResetModel();
    return;
}

void CpuStatModel::fillData(std::vector<QVariant>& container,const monitor::proto::CpuStat& cpu_stat){
    for (int i = static_cast<int>(CpuStat::CPU_ID); i < static_cast<int>(CpuStat::COLUMN_MAX); i++) {
        switch (i) {
        case static_cast<int>(CpuStat::CPU_ID):
            container.push_back(
                QVariant(QString::fromStdString(cpu_stat.cpu_id())));
            break;
        case static_cast<int>(CpuStat::CPU_PERCENT):
            container.push_back(QVariant(cpu_stat.cpu_percent()));
            break;
        case static_cast<int>(CpuStat::CPU_USER_PERCENT):
            container.push_back(QVariant(cpu_stat.user_percent()));
            break;
        case static_cast<int>(CpuStat::CPU_SYSTEM_PERCENT):
            container.push_back(QVariant(cpu_stat.system_percent()));
            break;
        case static_cast<int>(CpuStat::CPU_NICE_PERCENT):
            container.push_back(QVariant(cpu_stat.nice_percent()));
            break;
        case static_cast<int>(CpuStat::CPU_IDLE_PERCENT):
            container.push_back(QVariant(cpu_stat.idle_percent()));
            break;
        case static_cast<int>(CpuStat::CPU_IO_WAIT_PERCENT):
            container.push_back(QVariant(cpu_stat.io_wait_percent()));
            break;
        case static_cast<int>(CpuStat::CPU_IRQ_PERCENT):
            container.push_back(QVariant(cpu_stat.irq_percent()));
            break;
        case static_cast<int>(CpuStat::CPU_SOFT_IRQ_PERCENT):
            container.push_back(QVariant(cpu_stat.soft_irq_percent()));
            break;
        default:
            break;
        }
  }
    return;
}
}// namespace monitor