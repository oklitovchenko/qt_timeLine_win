#include "timelinegraphicslineitem.h"

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>

TimeLineGraphicsLineItem::TimeLineGraphicsLineItem()
    : m_vZoomMin(0),
      m_vZoomMax(0)
{

}

void TimeLineGraphicsLineItem::paint(QPainter *pPntr, const QStyleOptionGraphicsItem *pO, QWidget *pW)
{
    //QPointF p = pos();
    //isInVi
    qreal m11 = scene()->views()[0]->transform().m11();

    if ((m_vZoomMin ? m11 > m_vZoomMin : true) && (m_vZoomMax ? m11 < m_vZoomMax : true))
    {
        QPen pen(pen());
        pen.setWidthF(0.0);
        pPntr->setPen(pen);
        pPntr->drawLine(line());
    }
}
