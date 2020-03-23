#include "timelinegraphicstextitem.h"

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>

TimeLineGraphicsTextItem::TimeLineGraphicsTextItem()
    : m_vZoomMin(0),
      m_vZoomMax(0)
{

}

void TimeLineGraphicsTextItem::paint(QPainter *pPntr, const QStyleOptionGraphicsItem *pO, QWidget *pW)
{
    qreal m11 = scene()->views()[0]->transform().m11();
    setPos(data(0xff).toPointF());
    moveBy(-(boundingRect().width()/2)/m11, 0);
    if ((m_vZoomMin ? m11 > m_vZoomMin : true) && (m_vZoomMax ? m11 < m_vZoomMax : true))
        QGraphicsTextItem::paint(pPntr, pO, pW);
}
