#ifndef TIMELINEEVENTITEM_H
#define TIMELINEEVENTITEM_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPersistentModelIndex>
#include <QAbstractItemModel>
#include <QGraphicsProxyWidget>

enum resizeDirection
{
    rd_none,
    rd_left,
    rd_right
};

class TimeLineEventItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

    QString _type;
    resizeDirection _resizeDirection;
    QList<QPersistentModelIndex> _modelIndexesList;
    QAbstractItemModel *_pModel;
    QPointF _pressPos;
    QRectF _r;
    QGraphicsProxyWidget *_pClosePushButton;

public:
    TimeLineEventItem(QGraphicsRectItem *pParentWgt = NULL);
    void setType(const QString &s);
    void setPersistentIndexes(const QPersistentModelIndex &i) { _modelIndexesList.append(i); }
    void setModel(QAbstractItemModel *pM) { _pModel = pM; }

protected:
    void paint(QPainter *pPntr, const QStyleOptionGraphicsItem *pO, QWidget *pW);
    void mousePressEvent(QGraphicsSceneMouseEvent *pE);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *pE);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *pE);

private slots:
    void close();
};

#endif // TIMELINEEVENTITEM_H
