#include "cpu_load_model.h"

namespace monitor{
CpuLoadModel::CpuLoadModel(QObject* parent):AbstractMonitorModel(parent){
    m_header.append("load_1");
    m_header.append("load_5");
    m_header.append("load_15");
}

int CpuLoadModel::rowCount(const QModelIndex& parent)const {
    return m_monitor_data.size();
}

int CpuLoadModel::columnCount(const QModelIndex& parent )const {
    return static_cast<int>(CpuLoad::COLUMN_MAX);
}

QVariant CpuLoadModel::headerData(int section,Qt::Orientation orientation,int role)const {
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        return m_header[section];
    }

    return AbstractMonitorModel::headerData(section,orientation,role);
}

QVariant CpuLoadModel::data(const QModelIndex& index,int role )const {
    if(index.column() < 0 || index.column() >= static_cast<int>(CpuLoad::COLUMN_MAX)){
        return QVariant();
    }

    if(role == Qt::DisplayRole){
        if(index.row() < m_monitor_data.size() && index.column() < static_cast<int>(CpuLoad::COLUMN_MAX)){
            return m_monitor_data[index.row()][index.column()];
        }
    }
    return QVariant();
}

void CpuLoadModel::UpdateMonitorInfo(const monitor::proto::MonitorInfo& monitor_info){
    beginResetModel();

    m_monitor_data.clear();
    std::vector<QVariant> container;
    fillData(container,monitor_info.cpu_load());
    m_monitor_data.push_back(std::move(container));

    endResetModel();
    return;
}

void CpuLoadModel::fillData(std::vector<QVariant>& container,const monitor::proto::CpuLoad& cpu_load_info){
    container.push_back(cpu_load_info.load_avg_1());
    container.push_back(cpu_load_info.load_avg_5());
    container.push_back(cpu_load_info.load_avg_15());
    return;
}

}// namespace monitor