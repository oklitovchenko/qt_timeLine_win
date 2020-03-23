#ifndef TESTTASKMAINWINDOW_H
#define TESTTASKMAINWINDOW_H

#include "timelinedockwidget.h"

#include <QMainWindow>
#include <QMdiArea>

namespace Ui {
class TestTaskMainWindow;
}

class TestTaskMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestTaskMainWindow(QWidget *pParentWgt = NULL);
    ~TestTaskMainWindow();

private:
    Ui::TestTaskMainWindow *_pUi;
    QMdiArea *_pMDI;

private slots:
    void openFile(const QString &path = QString());
};

#endif // TESTTASKMAINWINDOW_H
