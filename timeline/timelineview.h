#ifndef TIMELINEVIEW_H
#define TIMELINEVIEW_H

#include "timelinegraphicsview.h"
#include "timelineeventgraphicsview.h"

#include <QAbstractItemView>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
QT_END_NAMESPACE

class TimeLineView : public QAbstractItemView
{
    Q_OBJECT

    TimeLineGraphicsView *_pTimeLineGraphicsView;
    TimeLineEventGraphicsView *_pEventItemGraphicsView;
    QGraphicsScene *_pEventItemGraphicsScene;
    QVBoxLayout *_pVBoxViewsLayout;
    QStringList _timeLineEventTypes;

public:
    TimeLineView(QWidget *pParentWgt = NULL);

    QRect visualRect(const QModelIndex &index) const Q_DECL_OVERRIDE;
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) Q_DECL_OVERRIDE;
    QModelIndex indexAt(const QPoint &point) const Q_DECL_OVERRIDE;

protected slots:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                     const QVector<int> &roles = QVector<int>()) Q_DECL_OVERRIDE;
/*
    void rowsInserted(const QModelIndex &parent, int start, int end) Q_DECL_OVERRIDE;
    void rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end) Q_DECL_OVERRIDE;
*/
protected:
    QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction,
                           Qt::KeyboardModifiers modifiers) Q_DECL_OVERRIDE;

    int horizontalOffset() const Q_DECL_OVERRIDE;
    int verticalOffset() const Q_DECL_OVERRIDE;

    bool isIndexHidden(const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setSelection(const QRect&, QItemSelectionModel::SelectionFlags command) Q_DECL_OVERRIDE;

    QRegion visualRegionForSelection(const QItemSelection &selection) const Q_DECL_OVERRIDE;

private:

};

#endif // TIMELINEVIEW_H
