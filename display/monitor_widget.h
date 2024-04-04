#pragma once

#include <QStandardItemModel>
#include <QtWidgets>
#include <string_view>
#include "cpu_load_model.h"
#include "cpu_softirq_model.h"
#include "cpu_stat_model.h"
#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor{
class MonitorWidget:public QWidget{
    Q_OBJECT
    public:
        explicit MonitorWidget(QWidget* parent = nullptr){};
        ~MonitorWidget() = default;
        QWidget* ShowAllMonitorWidget(std::string_view name);
        QWidget* InitCpuMonitorWidget();
        QWidget* InitButtonMenu(std::string_view name);

        void UpdateData(const monitor::proto::MonitorInfo& monitor_info);

    private slots:
        void ClickCpuButton();

    private:
        QTableView* m_cpu_load_monitor_view{nullptr};
        QTableView* m_cpu_softirq_monitor_view{nullptr};
        QTableView* m_cpu_stat_monitor_view{nullptr};

        CpuLoadModel* m_cpu_load_model{nullptr};
        CpuSoftirqModel* m_cpu_softirq_model{nullptr};
        CpuStatModel* m_cpu_stat_model{nullptr};

        QStackedLayout* m_stack_menu{nullptr};
};

}//namespace monitor