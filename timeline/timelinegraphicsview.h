#ifndef TIMELINEGRAPHICSVIEW_H
#define TIMELINEGRAPHICSVIEW_H

#include "timelinegraphicstextitem.h"
#include "timelinegraphicslineitem.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDateTime>
#include <QMouseEvent>

struct zoomRange
{
    qreal min, max;
};

enum gradation
{
    minute,
    hour,
    day,
    mounth
};

class TimeLineGraphicsView : public QGraphicsView
{
    Q_OBJECT

    QDateTime m_timeLineBegin, m_timeLineEnd;
    zoomRange m_zoomRange;
    qreal m_scaleFactor;

    //TimeLineGraphicsLineItem *pL;
    //TimeLineGraphicsTextItem *pT;

    QGraphicsView *m_pSyncView;

public:
    explicit TimeLineGraphicsView(QGraphicsScene *pScene, QWidget *pParentWgt = NULL);
    ~TimeLineGraphicsView(){}
    void setBegin(QDateTime dt);
    void setEnd(QDateTime dt);
    QDateTime begin() { return m_timeLineBegin; }
    QDateTime end() { return m_timeLineEnd; }
    void setSyncView(QGraphicsView *pView);

protected:
    void drawBackground(QPainter *pPainter, const QRectF &rect);
    /*
    void mousePressEvent(QMouseEvent *pE);
    void mouseMoveEvent(QMouseEvent *pE);
    void mouseReleaseEvent(QMouseEvent *pE);
    void resizeEvent(QResizeEvent *pE);
    */
    void wheelEvent(QWheelEvent *pE);

public slots:
    void setZoomRange(qreal min, qreal max) { m_zoomRange.min = min; m_zoomRange.max = max; }
    void drawTimeLine(QDateTime dtb, QDateTime dte);
};

#endif // TIMELINEGRAPHICSVIEW_H
