#ifndef TIMELINEGRAPHICSLINEITEM_H
#define TIMELINEGRAPHICSLINEITEM_H

#include <QGraphicsItem>
#include <QGraphicsLineItem>

class TimeLineGraphicsLineItem : public QObject, public QGraphicsLineItem
{
    Q_OBJECT

    qreal m_vZoomMin, m_vZoomMax;

public:
    TimeLineGraphicsLineItem();

protected:
    void paint(QPainter *pPntr, const QStyleOptionGraphicsItem *pO, QWidget *pW);

public slots:
    void setVZoomRange(qreal min, qreal max) { m_vZoomMin = min; m_vZoomMax = max; }
};

#endif // TIMELINEGRAPHICSLINEITEM_H
