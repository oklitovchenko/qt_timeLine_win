#include "testtaskmainwindow.h"
#include "ui_testtaskmainwindow.h"

#include <QtWidgets>
#include <QDebug>

TestTaskMainWindow::TestTaskMainWindow(QWidget *pParentWgt)
    : QMainWindow(pParentWgt),
      _pUi(new Ui::TestTaskMainWindow)
{
    _pUi->setupUi(this);
    _pMDI = new QMdiArea();
    setCentralWidget(_pMDI);

    QMenu *pFileMenu = new QMenu(tr("&File"), this);
    QAction *pOpenAction = pFileMenu->addAction(tr("&New from file..."));
    pOpenAction->setShortcuts(QKeySequence::New);
    QAction *pQuitAction = pFileMenu->addAction(tr("E&xit"));
    pQuitAction->setShortcuts(QKeySequence::Quit);

    connect(pOpenAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(pQuitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    _pUi->mainToolBar->close();
    menuBar()->addMenu(pFileMenu);
}

TestTaskMainWindow::~TestTaskMainWindow()
{
    delete _pUi;
}

void TestTaskMainWindow::openFile(const QString &path)
{
    QString fileName;
    if (path.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("Choose a data file"), "", "*.tml");
    else
        fileName = path;

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return;

    TimeLineDockWidget *pTimeLineDockWidget = new TimeLineDockWidget;
    pTimeLineDockWidget->readDataFromStringFile(&file);
    QMdiSubWindow *pSubWindow = _pMDI->addSubWindow(pTimeLineDockWidget);
    pSubWindow->setAttribute(Qt::WA_DeleteOnClose);
    pSubWindow->showMaximized();

    file.close();
    statusBar()->showMessage(tr("Loaded %1").arg(fileName), 2000);
}
