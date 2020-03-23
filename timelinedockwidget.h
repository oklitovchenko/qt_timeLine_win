#ifndef TIMELINEDOCKWIDGET_H
#define TIMELINEDOCKWIDGET_H

#include "timeline/timelineview.h"

#include <QDockWidget>

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
class QSortFilterProxyModel;
class QAbstractItemView;
class QItemSelectionModel;
QT_END_NAMESPACE

namespace Ui {
class TimeLineDockWidget;
}

class TimeLineDockWidget : public QWidget
{
    Q_OBJECT

    Ui::TimeLineDockWidget *_pUi;
    QAbstractItemView *_pTimeLineView;
    QAbstractItemModel *_pModel;
    QSortFilterProxyModel *_pProxySortByBeginModel;
    QSortFilterProxyModel *_pProxySortByTypeModel;
    QItemSelectionModel *_pSelectionModel;

public:
    explicit TimeLineDockWidget(QWidget *pParentWgt = NULL);
    ~TimeLineDockWidget();
    void readDataFromStringFile(QIODevice *pF);

private slots:
    void setupModels();
    void setupViews();
};

#endif // TIMELINEDOCKWIDGET_H
