#pragma once
#include "abstract_monitor_model.h"

namespace monitor{
class CpuSoftirqModel:public AbstractMonitorModel{
    Q_OBJECT
    public:
        explicit CpuSoftirqModel(QObject* parent = nullptr);
        virtual ~CpuSoftirqModel() = default;
        int rowCount(const QModelIndex& parent = QModelIndex())const override;
        int columnCount(const QModelIndex& parent = QModelIndex())const override;
        QVariant headerData(int section,Qt::Orientation orientation,int role)const override;
        QVariant data(const QModelIndex& index,int role = Qt::DisplayRole)const override;
        void UpdateMonitorInfo(const monitor::proto::MonitorInfo& monitor_info); 
     signals:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                   const QVector<int> &roles);
    
    private:
        void fillData(std::vector<QVariant>& container,const monitor::proto::SoftIrq& cpu_load_info);
    private:
        std::vector<std::vector<QVariant>> m_monitor_data;
        QStringList m_header;
        enum class Softirq{
            CPU_ID = 0,
            HI,
            TIMER,
            NET_TX,
            NET_RX,
            BLOCK,
            IRQ_POLL,
            TASKLET,
            SCHED,
            HRTIMER,
            RCU,
            COLUMN_MAX
        };
};
}// namespace monitor