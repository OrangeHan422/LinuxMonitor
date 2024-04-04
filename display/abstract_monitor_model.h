#pragma once

#include <vector>
#include <QAbstractTableModel>
#include <QObject>

#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor{
class AbstractMonitorModel:public QAbstractTableModel{
    Q_OBJECT
    public:
    explicit AbstractMonitorModel(QObject *parent = nullptr)
            :QAbstractTableModel(parent){}
    QVariant data(const QModelIndex& index,int role = Qt::DisplayRole) const override;
    QVariant headerData(int section,Qt::Orientation orientation,int role) const override;
    virtual ~AbstractMonitorModel() = default;
};

}//namespace monitor