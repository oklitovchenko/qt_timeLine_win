#include "timelinegraphicsview.h"

#include <QApplication>
#include <QDebug>
#include <QPropertyAnimation>
#include <QGLWidget>
#include <QtWidgets>


#include "timelineeventitem.h"

TimeLineGraphicsView::TimeLineGraphicsView(QGraphicsScene *pScene, QWidget *pParentWgt)
    : QGraphicsView(pScene, pParentWgt),
      m_timeLineBegin(QDateTime()),
      m_timeLineEnd(QDateTime()),
      m_pSyncView(NULL)
{
    m_zoomRange.min = m_zoomRange.max = 0.0;
    m_scaleFactor = 1.05;

    //setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

    setMinimumHeight(105);
    setMaximumHeight(105);

    setSceneRect(0, 0, 0, 100);

    //setCacheMode(QGraphicsView::CacheNone);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate
                          /*QGraphicsView::FullViewportUpdate
                           * QGraphicsView::MinimalViewportUpdate*/);

    setTransformationAnchor(AnchorUnderMouse);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setDragMode(QGraphicsView::ScrollHandDrag); 
}

void TimeLineGraphicsView::setBegin(QDateTime dt)
{
    dt = QDateTime(dt.addDays(-dt.date().day()+1).date(), QTime(0, 0, 0));
    if (m_timeLineBegin.isValid())
    {
        qreal dx = dt.daysTo(m_timeLineBegin)*24;
        QRectF r = sceneRect();
        setSceneRect(r.x(), r.y(), r.width()+dx, r.height());

        foreach(QGraphicsItem *pTimeLineItem, scene()->items(r))
        {
            pTimeLineItem->data(0xff).isValid()
                    ? pTimeLineItem->setData(0xff, pTimeLineItem->data(0xff).toPointF()+QPoint(dx, 0))
                    : pTimeLineItem->moveBy(dx, 0);
        }
        drawTimeLine(dt, m_timeLineBegin);
        scene()->update();

        r = sceneRect();
        m_pSyncView->setSceneRect(r.x(), r.y(),
                                  r.width()+dx,
                                  m_pSyncView->scene()->sceneRect().height());

        r = m_pSyncView->sceneRect();
        foreach(QGraphicsItem *pTimeLineItem, m_pSyncView->scene()->items(r))
            pTimeLineItem->moveBy(dx, 0);
        m_pSyncView->scene()->update();
    }

    m_timeLineBegin = dt;
}

void TimeLineGraphicsView::setEnd(QDateTime dt)
{
    dt = QDateTime(dt.addMonths(1).addDays(-dt.date().day()+1).date(), QTime(0, 0, 0));
    QRectF r = sceneRect();
    if (m_timeLineEnd.isValid())
    {
        setSceneRect(r.x(), r.y(), m_timeLineBegin.daysTo(dt)*24, r.height());
        r = sceneRect();
        m_pSyncView->setSceneRect(r.x(), r.y(), r.width(),
                                  m_pSyncView->scene()->sceneRect().height());
        m_pSyncView->scene()->update();
        drawTimeLine(m_timeLineEnd, dt);
    }
    else if (m_timeLineBegin.isValid())
    {
        setSceneRect(r.x(), r.y(), m_timeLineBegin.daysTo(dt)*24, r.height());
        r = sceneRect();
        m_pSyncView->setSceneRect(r.x(), r.y(), r.width(),
                                  m_pSyncView->scene()->sceneRect().height());
        m_pSyncView->scene()->update();
        drawTimeLine(m_timeLineBegin, dt);
    }
    m_timeLineEnd = dt;
}

void TimeLineGraphicsView::setSyncView(QGraphicsView *pView)
{
    m_pSyncView = pView;
    connect(horizontalScrollBar(), SIGNAL(valueChanged(int)),
            m_pSyncView->horizontalScrollBar(), SLOT(setValue(int)));
    connect(m_pSyncView->horizontalScrollBar(), SIGNAL(valueChanged(int)),
            horizontalScrollBar(), SLOT(setValue(int)));
}

void TimeLineGraphicsView::drawTimeLine(QDateTime dtb, QDateTime dte)
{
    for (int i = dtb < m_timeLineBegin ? 0 : m_timeLineBegin.secsTo/*daysTo*/(m_timeLineEnd)/3600;
         dtb < dte; dtb = dtb.addSecs(3600)/*dtb.addDays(1)*/, i++)
    {
        //qDebug() << dtb << i;
        TimeLineGraphicsLineItem *pL;
        TimeLineGraphicsTextItem *pT;

        qreal j = i/*/60.0/**24*/;
        if (dtb.toString("dd hh:mm:ss") == "01 00:00:00")
        {
            pT = new TimeLineGraphicsTextItem();
            pT->setPlainText(dtb.toString("yyyy MMMM"));
            pT->setVZoomRange(0.15, 3.55);
            pT->setData(0xff, QPointF(j+dtb.daysTo(dtb.addMonths(1))*24/2, 75));
            pT->setPos(QPointF(j+dtb.daysTo(dtb.addMonths(1))*24/2, 75));
            pT->setFlags(QGraphicsItem::ItemIgnoresTransformations);
            scene()->addItem(pT);

            pL = new TimeLineGraphicsLineItem();
            pL->setLine(j, 0, j, 90);
            scene()->addItem(pL);
        }
        if (dtb.toString("hh:mm:ss") == "00:00:00")
        {
            pT = new TimeLineGraphicsTextItem();
            pT->setPlainText(dtb.toString("dd"));
            pT->setVZoomRange(0.6, 0.0);
            pT->setPos(QPointF(j+12, 60));
            pT->setData(0xff, QPointF(j+12, 60));
            pT->setFlags(QGraphicsItem::ItemIgnoresTransformations);
            scene()->addItem(pT);

            pT = new TimeLineGraphicsTextItem();
            pT->setPlainText(dtb.toString("yyyy MMMM"));
            pT->setVZoomRange(3.55, 0.0);
            pT->setPos(QPointF(j+12, 45));
            pT->setData(0xff, QPointF(j+12, 45));
            pT->setFlags(QGraphicsItem::ItemIgnoresTransformations);
            scene()->addItem(pT);

            if (dtb.toString("dd hh:mm") != "01 00:00")
            {
                pL = new TimeLineGraphicsLineItem();
                pL->setLine(j, 0, j, 75);
                scene()->addItem(pL);
            }

        }
        if (dtb.toString("mm:ss") == "00:00" &&
                dtb.toString("hh:mm") != "00:00")
        {
            pT = new TimeLineGraphicsTextItem();
            pT->setPlainText(dtb.toString("hh:mm"));
            pT->setVZoomRange(30.0, 0.0);
            pT->setPos(QPointF(j, 30));
            pT->setData(0xff, QPointF(j, 30));
            pT->setFlags(QGraphicsItem::ItemIgnoresTransformations);
            scene()->addItem(pT);

            pL = new TimeLineGraphicsLineItem();
            pL->setLine(j, 0, j, 30);
            pL->setVZoomRange(5.0, 0.0);
            scene()->addItem(pL);
        }

        QApplication::processEvents();
    }
    scene()->update();
}

void TimeLineGraphicsView::drawBackground(QPainter *pPainter, const QRectF &rect)
{
    Q_UNUSED(rect);

    QRadialGradient gradient(rect.width()/2.0, 0.0, rect.width()/2.0);
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    setBackgroundBrush(gradient);
    pPainter->setBrushOrigin(0.0, 0.0);
    pPainter->fillRect(rect, backgroundBrush());

    QPen pen(Qt::red);
    pen.setWidthF(5.0);
    pPainter->setPen(pen);
    pPainter->drawLine(rect.bottomLeft().x(), 0, rect.bottomRight().x(), 0);
}
/*
void TimeLineGraphicsView::mousePressEvent(QMouseEvent *pE)
{
    QGraphicsView::mousePressEvent(pE);
}

void TimeLineGraphicsView::mouseMoveEvent(QMouseEvent *pE)
{
    QGraphicsView::mouseMoveEvent(pE);
}

void TimeLineGraphicsView::mouseReleaseEvent(QMouseEvent *pE)
{
    QGraphicsView::mouseReleaseEvent(pE);
}

void TimeLineGraphicsView::resizeEvent(QResizeEvent *pE)
{
    QGraphicsView::resizeEvent(pE);
}
*/
void TimeLineGraphicsView::wheelEvent(QWheelEvent *pE)
{
    qreal factor = transform().scale(pow(m_scaleFactor, pE->delta() > 0 ? 1.0 : -1.0), 1.0).m11();
    qDebug() << factor;
    if ((m_zoomRange.min ? factor < m_zoomRange.min : false)
            || (m_zoomRange.max ? factor > m_zoomRange.max : false)) return;
    long double sc = pow(m_scaleFactor, pE->delta() > 0 ? 1.0 : -1.0);
    scale(sc, 1.0);
    m_pSyncView->scale(sc, 1.0);
    pE->accept();
}
