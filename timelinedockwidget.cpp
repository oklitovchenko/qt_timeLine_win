#include "timelinedockwidget.h"
#include "ui_timelinedockwidget.h"

#include <QtWidgets>

TimeLineDockWidget::TimeLineDockWidget(QWidget *pParentWgt)
    : QWidget(pParentWgt),
      _pUi(new Ui::TimeLineDockWidget)
{
    _pUi->setupUi(this);
    setupModels();
    setupViews();
}

TimeLineDockWidget::~TimeLineDockWidget()
{
    delete _pUi;
}

void TimeLineDockWidget::readDataFromStringFile(QIODevice *pF)
{
    QTextStream stream(pF);
    QString line;

    _pModel->removeRows(0, _pModel->rowCount(QModelIndex()), QModelIndex());

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            _pModel->insertRows(row, 1, QModelIndex());

            QStringList interval = line.split("|", QString::SkipEmptyParts);
            _pModel->setData(_pModel->index(row, 0, QModelIndex()), interval.value(0));
            _pModel->setData(_pModel->index(row, 1, QModelIndex()),
                             QDateTime::fromString(interval.value(1), "yyyy.MM.dd HH:mm"));
            _pModel->setData(_pModel->index(row, 2, QModelIndex()),
                             interval.value(2).toInt());

            row++;
        }
    }
    while (!line.isEmpty());
}

void TimeLineDockWidget::setupModels()
{
    _pModel = new QStandardItemModel(this);
    _pModel->insertColumns(0, 3);
    _pModel->setHeaderData(0, Qt::Horizontal, tr("Type"));
    _pModel->setHeaderData(1, Qt::Horizontal, tr("Begin, DateTime"));
    _pModel->setHeaderData(2, Qt::Horizontal, tr("Duration, minutes"));

    _pProxySortByBeginModel = new QSortFilterProxyModel(this);
    _pProxySortByBeginModel->setSourceModel(_pModel);
    _pProxySortByBeginModel->sort(1);

    _pProxySortByTypeModel = new QSortFilterProxyModel(this);
    _pProxySortByTypeModel->setSourceModel(_pModel);
    _pProxySortByTypeModel->sort(0);
}

void TimeLineDockWidget::setupViews()
{    
    _pTimeLineView = new TimeLineView;

    _pUi->VSplitter->addWidget(_pTimeLineView);
    _pUi->VSplitter->setStretchFactor(0, 0);
    _pUi->VSplitter->setStretchFactor(1, 1);

    _pUi->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _pUi->tableView->setModel(_pModel);
    _pUi->treeViewSortByBegin->setModel(_pProxySortByBeginModel);
    _pUi->treeViewSortByBegin->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _pUi->treeViewSortByType->setModel(_pProxySortByTypeModel);
    _pUi->treeViewSortByType->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _pTimeLineView->setModel(_pModel);

    QItemSelectionModel *pSelectionModel = new QItemSelectionModel(_pModel);
    _pUi->tableView->setSelectionModel(pSelectionModel);
    _pTimeLineView->setSelectionModel(pSelectionModel);

    QHeaderView *pHeaderViewTable = _pUi->tableView->horizontalHeader();
    pHeaderViewTable->setStretchLastSection(true);
    pHeaderViewTable->setSectionResizeMode(QHeaderView::ResizeToContents);
}

                                                                                                                                                                                                                                                                                                                                                                                                
