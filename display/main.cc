#include <thread>
#include <memory>
#include <QApplication>
#include "stub/rpc_stub.h"
#include "monitor_widget.h"

int main(int argc,char* argv[]){
    QApplication app(argc,argv);

    monitor::MonitorWidget monitor_widget;
    monitor::RpcStub stub("localhost:50051");
    monitor::proto::MonitorInfo monitor_info;

    stub.GetMonitorInfo(&monitor_info);
    std::string name = monitor_info.name();

    QWidget* widget = monitor_widget.ShowAllMonitorWidget(std::move(name));
    widget->show();

    std::unique_ptr<std::thread> thread_ptr{std::make_unique<std::thread>([&monitor_info,&stub,&monitor_widget](){
        while(true){
            monitor_info.Clear();
            stub.GetMonitorInfo(&monitor_info);
            monitor_widget.UpdateData(monitor_info);
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    })};

    thread_ptr->detach();
    return app.exec();
}