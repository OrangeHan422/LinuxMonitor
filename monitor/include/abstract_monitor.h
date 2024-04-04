#pragma once

#include <string>

#include "abstract_monitor.h"
#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"
#include "read_file.h"

namespace monitor{
class AbstractMonitor{
    public:
        AbstractMonitor() = default;
        virtual ~AbstractMonitor() = default;
        virtual void UpdateOnce(monitor::proto::MonitorInfo& monitor_info) = 0;
        virtual void Stop() = 0;
};
}//namespace monitor