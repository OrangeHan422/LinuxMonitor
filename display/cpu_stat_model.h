#pragma once
#include "abstract_monitor_model.h"

namespace monitor{
class CpuStatModel:public AbstractMonitorModel{
    Q_OBJECT
    public:
        explicit CpuStatModel(QObject* parent = nullptr);
        virtual ~CpuStatModel() = default;
        int rowCount(const QModelIndex& parent = QModelIndex())const override;
        int columnCount(const QModelIndex& parent = QModelIndex())const override;
        QVariant headerData(int section,Qt::Orientation orientation,int role)const override;
        QVariant data(const QModelIndex& index,int role = Qt::DisplayRole)const override;
        void UpdateMonitorInfo(const monitor::proto::MonitorInfo& monitor_info); 
     signals:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                   const QVector<int> &roles);
    
    private:
        void fillData(std::vector<QVariant>& container,const monitor::proto::CpuStat& cpu_load_info);
    private:
        std::vector<std::vector<QVariant>> m_monitor_data;
        QStringList m_header;
        enum class CpuStat {
            CPU_ID = 0,
            CPU_PERCENT,
            CPU_USER_PERCENT,
            CPU_SYSTEM_PERCENT,
            CPU_NICE_PERCENT,
            CPU_IDLE_PERCENT,
            CPU_IO_WAIT_PERCENT,
            CPU_IRQ_PERCENT,
            CPU_SOFT_IRQ_PERCENT,
            COLUMN_MAX
        };
};
}// namespace monitor