#ifndef TIMELINEGRAPHICSTEXTITEM_H
#define TIMELINEGRAPHICSTEXTITEM_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>

class TimeLineGraphicsTextItem : public QGraphicsTextItem
{
    Q_OBJECT

    qreal m_vZoomMin, m_vZoomMax;

public:
    TimeLineGraphicsTextItem();

protected:
    void paint(QPainter *pPntr, const QStyleOptionGraphicsItem *pO, QWidget *pW);

public slots:
    void setVZoomRange(qreal min, qreal max) { m_vZoomMin = min; m_vZoomMax = max; }
};

#endif // TIMELINEGRAPHICSTEXTITEM_H
