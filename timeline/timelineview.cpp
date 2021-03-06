#include "timelineview.h"
#include "timelineeventitem.h"

#include <QtWidgets>
#include <QPersistentModelIndex>

TimeLineView::TimeLineView(QWidget *pParentWgt)
    : QAbstractItemView(pParentWgt)
{
    _pVBoxViewsLayout = new QVBoxLayout;
    _pVBoxViewsLayout->setSpacing(0);
    _pVBoxViewsLayout->setMargin(0);
    _pEventItemGraphicsView =
            new TimeLineEventGraphicsView(_pEventItemGraphicsScene = new QGraphicsScene());

    _pTimeLineGraphicsView = new TimeLineGraphicsView(new QGraphicsScene());
    _pTimeLineGraphicsView->setSyncView(_pEventItemGraphicsView);
    _pTimeLineGraphicsView->setZoomRange(0.7, 35.0);

    _pVBoxViewsLayout->addWidget(_pEventItemGraphicsView);
    _pVBoxViewsLayout->addWidget(_pTimeLineGraphicsView);

    viewport()->setLayout(_pVBoxViewsLayout);
}

void TimeLineView::dataChanged(const QModelIndex &topLeft,
                               const QModelIndex &bottomRight,
                               const QVector<int> &)
{
    QAbstractItemView::dataChanged(topLeft, bottomRight);

    if (bottomRight.column() == 0)
    {
        for (int r = topLeft.row(); r <= bottomRight.row(); r++)
        {
            QString s = model()->data(model()->index(r, 0)).toString();
            if (_timeLineEventTypes.contains(s)) continue;
            _timeLineEventTypes << s;

            //_timeLineEventTypes.removeDuplicates();

            QRectF sr = _pEventItemGraphicsScene->sceneRect();
            sr.setHeight(_timeLineEventTypes.count()*55);
            _pEventItemGraphicsScene->setSceneRect(sr);
        }
        return;
    }

    if (bottomRight.column() > 0)
    {
        for (int r = topLeft.row(); r <= bottomRight.row(); r++)
        {
            qreal x, w;
            QRectF ctrlRect;
            QDateTime dt = model()->data(model()->index(r, 1)).toDateTime();

            if (!_pTimeLineGraphicsView->begin().isValid() || _pTimeLineGraphicsView->begin() > dt)
                _pTimeLineGraphicsView->setBegin(dt);

            if (model()->index(r, 2).isValid())
            {
                x = _pTimeLineGraphicsView->begin().secsTo(dt);
                w = model()->data(model()->index(r, 2)).toInt()*60;
                dt = dt.addSecs(w);
            }

            if (!_pTimeLineGraphicsView->end().isValid() || _pTimeLineGraphicsView->end() < dt)
                _pTimeLineGraphicsView->setEnd(dt);

            ctrlRect = QRectF(x/3600.0,
                              _timeLineEventTypes.indexOf(QRegExp(model()->data(model()->index(r, 0)).toString()))*55,
                              w/3600.0,
                              50);

            if (_pEventItemGraphicsScene->items(ctrlRect).count() || bottomRight.column() < 2) continue;

            TimeLineEventItem *pI = new TimeLineEventItem();
            pI->setRect(ctrlRect);
            pI->setModel(model());
            pI->setType(model()->data(model()->index(r, 0)).toString());
            pI->setPersistentIndexes(QPersistentModelIndex(model()->index(r, 0)));
            pI->setPersistentIndexes(QPersistentModelIndex(model()->index(r, 1)));
            pI->setPersistentIndexes(QPersistentModelIndex(model()->index(r, 2)));
            _pEventItemGraphicsScene->addItem(pI);
        }
    }
    //qDebug() << _timeLineEventTypes;
}

QRect TimeLineView::visualRect(const QModelIndex &index) const
{
    return QRect();
}

void TimeLineView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{

}

QModelIndex TimeLineView::indexAt(const QPoint &point) const
{
    return QModelIndex();
}

QModelIndex TimeLineView::moveCursor(QAbstractItemView::CursorAction cursorAction,
                                     Qt::KeyboardModifiers modifiers)
{
    return QModelIndex();
}

int TimeLineView::horizontalOffset() const
{
    return _pEventItemGraphicsView->horizontalScrollBar()->value();
}

int TimeLineView::verticalOffset() const
{
    return _pEventItemGraphicsView->verticalScrollBar()->value();
}

bool TimeLineView::isIndexHidden(const QModelIndex &index) const
{
    return false;
}

void TimeLineView::setSelection(const QRect &,
                                QItemSelectionModel::SelectionFlags command)
{

}

QRegion TimeLineView::visualRegionForSelection(const QItemSelection &selection) const
{
    return QRegion();
}

                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
