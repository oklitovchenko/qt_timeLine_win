#include "timelineeventgraphicsview.h"

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

TimeLineEventGraphicsView::TimeLineEventGraphicsView(QGraphicsScene *pScene, QWidget *pParentWgt)
    : QGraphicsView(pScene, pParentWgt),
      isLeftMouseButtonPressed(false)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void TimeLineEventGraphicsView::mousePressEvent(QMouseEvent *pE)
{
    QGraphicsView::mousePressEvent(pE);
    isLeftMouseButtonPressed = true;
    setMsCursor(pE->pos());
}

void TimeLineEventGraphicsView::mouseMoveEvent(QMouseEvent *pE)
{
    QGraphicsView::mouseMoveEvent(pE);
    setMsCursor(pE->pos());
}

void TimeLineEventGraphicsView::mouseReleaseEvent(QMouseEvent *pE)
{
    QGraphicsView::mouseReleaseEvent(pE);
    isLeftMouseButtonPressed = false;
    setMsCursor(pE->pos());
}

void TimeLineEventGraphicsView::setMsCursor(QPoint point)
{
    if (itemAt(point)->data(0xbb) == 0xbb00cc)
        return;

    if (itemAt(point)->data(0xbb) != 0xbb00ff)
        return;

    QGraphicsRectItem *pI = dynamic_cast<QGraphicsRectItem *>(itemAt(point));

    QRectF r = pI->mapRectToScene(pI->rect());
    QPointF p = mapToScene(point);

    if (p.x() <= r.topLeft().x()+3 || p.x() >= r.topRight().x()-3)
        pI->setCursor(Qt::SizeHorCursor);
    else if (p.x() >= r.topLeft().x()+3 && p.x() <= r.topRight().x()-3)
        pI->setCursor(isLeftMouseButtonPressed ? Qt::ClosedHandCursor : Qt::OpenHandCursor);
}
