#ifndef TIMELINEEVENTGRAPHICSVIEW_H
#define TIMELINEEVENTGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QPoint>

class TimeLineEventGraphicsView : public QGraphicsView
{
    Q_OBJECT
    bool isLeftMouseButtonPressed;

public:
    explicit TimeLineEventGraphicsView(QGraphicsScene *pScene, QWidget *pParentWgt = NULL);
    ~TimeLineEventGraphicsView(){}

protected:
    void mousePressEvent(QMouseEvent *pE);
    void mouseMoveEvent(QMouseEvent *pE);
    void mouseReleaseEvent(QMouseEvent *pE);

private:
    void setMsCursor(QPoint point);
};

#endif // TIMELINEEVENTGRAPHICSVIEW_H
