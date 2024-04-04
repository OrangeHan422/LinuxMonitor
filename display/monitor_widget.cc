#include "monitor_widget.h"

namespace monitor{

QWidget* MonitorWidget::ShowAllMonitorWidget(std::string_view name){
    QWidget* widget = new QWidget();
    m_stack_menu = new QStackedLayout();
    m_stack_menu->addWidget(InitCpuMonitorWidget());

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(InitButtonMenu(name),0,0);
    layout->addLayout(m_stack_menu,1,0);
    widget->setLayout(layout);
    return widget;
}

QWidget* MonitorWidget::InitCpuMonitorWidget(){
    QWidget* cpu_widget = new QWidget();
    // 平均负载信息
    QLabel *cpu_load_label = new QLabel(this);
    cpu_load_label->setText("Monitor CpuLoad:");
    cpu_load_label->setFont(QFont("Microsoft YaHei", 10));

    m_cpu_load_monitor_view = new QTableView();
    m_cpu_load_model = new CpuLoadModel();
    m_cpu_load_monitor_view->setModel(m_cpu_load_model);
    m_cpu_load_monitor_view->show();
    // 软中断信息
    QLabel *cpu_softirq_label = new QLabel(this);
    cpu_softirq_label->setText("Monitor CpuSoftirq:");
    cpu_softirq_label->setFont(QFont("Microsoft YaHei", 10));

    m_cpu_softirq_monitor_view = new QTableView();
    m_cpu_softirq_model = new CpuSoftirqModel();
    m_cpu_softirq_monitor_view->setModel(m_cpu_softirq_model);
    m_cpu_softirq_monitor_view->show();
    // cpu使用率
    QLabel *cpu_stat_label = new QLabel(this);
    cpu_stat_label->setText("Monitor CpuStat:");
    cpu_stat_label->setFont(QFont("Microsoft YaHei", 10));

    m_cpu_stat_monitor_view = new QTableView();
    m_cpu_stat_model = new CpuStatModel();
    m_cpu_stat_monitor_view->setModel(m_cpu_stat_model);
    m_cpu_stat_monitor_view->show();

    // cpu信息总体布局
    /*          cpu_percent
                cpu_percent_table
         load               softirq
        load_table          softirq_table*/
    QHBoxLayout* pLayout1 = new QHBoxLayout();
    pLayout1->addWidget(cpu_load_label,0,Qt::AlignCenter);
    pLayout1->addWidget(cpu_softirq_label,0,Qt::AlignCenter);
    


    m_cpu_stat_monitor_view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(cpu_stat_label,0,0);
    layout->addWidget(m_cpu_stat_monitor_view,1,0,1,2);
    layout->addLayout(pLayout1,2,0,1,2);
    layout->addWidget(m_cpu_load_monitor_view,3,0);
    layout->addWidget(m_cpu_softirq_monitor_view,3,1);


    cpu_widget->setLayout(layout);
    return cpu_widget;
}

QWidget* MonitorWidget::InitButtonMenu(std::string_view name){
    QPushButton* cpu_button = new QPushButton(QString::fromStdString(name.data()) + "_cpu_info",this);


    QFont* font = new QFont("Microsoft YaHei", 15);
    cpu_button->setFont(*font);

    QBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(cpu_button);

    QWidget* button_widget = new QWidget();
    button_widget->setLayout(layout);

    connect(cpu_button,SIGNAL(clicked()),this,SLOT(ClickCpuButton()));

    return button_widget;
}

void MonitorWidget::ClickCpuButton(){
    m_stack_menu->setCurrentIndex(0);
}


void MonitorWidget::UpdateData(const monitor::proto::MonitorInfo& monitor_info){
    m_cpu_load_model->UpdateMonitorInfo(monitor_info);
    m_cpu_softirq_model->UpdateMonitorInfo(monitor_info);
    m_cpu_stat_model->UpdateMonitorInfo(monitor_info);
}

}// namespace monitor