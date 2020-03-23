#include "timelineeventitem.h"
#include "timelinegraphicstextitem.h"

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QSizePolicy>

TimeLineEventItem::TimeLineEventItem(QGraphicsRectItem *pParentWgt)
    : QGraphicsRectItem(pParentWgt),
      _resizeDirection(rd_none)
{
    setFlags(QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemIsSelectable);

    QPushButton *p = new QPushButton("x");
    _pClosePushButton = new QGraphicsProxyWidget(this);
    _pClosePushButton->setFlags(QGraphicsItem::ItemIgnoresTransformations);
    _pClosePushButton->setWidget(p);

    QRectF r = _pClosePushButton->rect();
    r.setWidth(r.height());
    _pClosePushButton->setMinimumWidth(r.height());
    _pClosePushButton->setGeometry(r);
    _pClosePushButton->setData(0xbb, 0xbb00cc);

    setData(0xbb, 0xbb00ff);

    connect(p, SIGNAL(clicked(bool)), SLOT(close()));
}

void TimeLineEventItem::setType(const QString &s)
{
    _type = s;
}

void TimeLineEventItem::paint(QPainter *pPntr, const QStyleOptionGraphicsItem *pO, QWidget *pW)
{

    QPen pen;
    pen.setWidthF(0.0);
    pPntr->setPen(pen);
    QPainterPath path;
    path.addRoundedRect(rect(), 5, 10);
    pPntr->fillPath(path, Qt::green);
    pPntr->drawPath(path);

    QRectF r = rect();

    pPntr->save();
    QTransform t = pPntr->combinedTransform();
    pPntr->scale(1.0/t.m11(), 1.0);
    pPntr->drawText(r.x()*t.m11(), r.y(), r.width()*t.m11(), r.height(),
                    Qt::AlignCenter,
                    _type +
                    ",\n begin time:" + _modelIndexesList.at(1).data().toString() +
                    ",\n duration: " + _modelIndexesList.at(2).data().toString() + " min");

    pPntr->restore();
    _pClosePushButton->setPos(r.right()-_pClosePushButton->rect().width()/t.m11()-10/t.m11(),
                              r.center().y()-_pClosePushButton->rect().height()/2);
}

void TimeLineEventItem::mousePressEvent(QGraphicsSceneMouseEvent *pE)
{
    _pressPos = pE->pos();
    _r = rect();

    _resizeDirection = mapToScene(_pressPos).x() <= mapToScene(_r.topLeft()).x()+3
            ? rd_left : mapToScene(_pressPos).x() >= mapToScene(_r.bottomRight()).x()-3
              ? rd_right : rd_none;

    _r = mapRectToScene(rect());

    QGraphicsRectItem::mousePressEvent(pE);
}

#define _UPDATE_SOURCE(a, b) \
    _pModel->setData(_pModel->index(_modelIndexesList.at(a).row(), \
    _modelIndexesList.at(a).column(), \
    _modelIndexesList.at(a).parent()), \
    b);

void TimeLineEventItem::mouseMoveEvent(QGraphicsSceneMouseEvent *pE)
{

    if (isSelected())
    {
        QPointF p = mapToItem(this, pE->pos());
        QRectF r = rect();
        QTransform t = transform();

        qDebug() << p;

        switch (_resizeDirection)
        {
        case rd_left:
            {
                r.setLeft(p.x());
                if (r.width() > _pClosePushButton->rect().width()/t.m11() + 20/t.m11())
                setRect(r);
            }
            break;
        case rd_right:

            {
                r.setRight(p.x());
                if (r.width() > _pClosePushButton->rect().width()/t.m11() + 20/t.m11())
                setRect(r);
            }
            break;
        default:
            moveBy(pE->pos().x()-_pressPos.x(), 0.0);
            break;
        }
        return;
    }

    QGraphicsRectItem::mouseMoveEvent(pE);
}

void TimeLineEventItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *pE)
{
    _resizeDirection = rd_none;

    QRectF r = mapRectToScene(rect());
    qreal b = r.left()-_r.left();

    if (b)
    {
        QDateTime dt = _modelIndexesList.at(1).data().toDateTime();
        _UPDATE_SOURCE(1, dt.addSecs(b*3600.0));
    }
    if (r.width()-_r.width())
        _UPDATE_SOURCE(2, (int)(rect().width()*3600.0/60.0));

    QGraphicsRectItem::mouseReleaseEvent(pE);
}

void TimeLineEventItem::close()
{
    int ret = QMessageBox::warning(NULL, ("Warning!") ,
                                   tr("Event type: ") + _type +
                                   tr("\n begin: ") + _modelIndexesList.at(1).data().toString() +
                                   tr("\n duration: ") + _modelIndexesList.at(2).data().toString() +
                                   tr("\nDo you want to delete event?"),
                                   QMessageBox::Yes | QMessageBox::Cancel,
                                   QMessageBox::Cancel);
    switch (ret)
    {
      case QMessageBox::Yes :
          _pModel->removeRow(_modelIndexesList.at(0).row());
          deleteLater();
          break;
      default :
          break;
    }

}

