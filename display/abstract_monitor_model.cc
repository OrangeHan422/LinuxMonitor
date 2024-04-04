#include <QFont>
#include <QColor>
#include "abstract_monitor_model.h"

namespace monitor{
QVariant AbstractMonitorModel::headerData(int section,Qt::Orientation orientation,int role) const 
{
    switch(role){
        case Qt::FontRole:
            return QVariant::fromValue(QFont("Microsoft YaHei", 10, QFont::Bold));
        case Qt::BackgroundRole:
            return QVariant::fromValue(QColor(Qt::lightGray));
        default:
            break;
    }
    return QAbstractTableModel::headerData(section,orientation,role);
}

QVariant AbstractMonitorModel::data(const QModelIndex& index,int role)const
{
    switch (role)
    {
    case Qt::TextAlignmentRole:
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    case Qt::TextColorRole:
        return QVariant::fromValue(QColor(Qt::black));
    case Qt::BackgroundRole:
        return QVariant::fromValue(QColor(Qt::white));
    default:
        break;
    }
    return QVariant();
}
}// namespace monitor