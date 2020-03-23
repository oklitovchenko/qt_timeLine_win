QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestTaskTimeLine
TEMPLATE = app


SOURCES += main.cpp\
        testtaskmainwindow.cpp \
    timelinedockwidget.cpp \
    timeline/timelinegraphicslineitem.cpp \
    timeline/timelinegraphicstextitem.cpp \
    timeline/timelineeventitem.cpp \
    timeline/timelineview.cpp \
    timeline/timelinegraphicsview.cpp \
    timeline/timelineeventgraphicsview.cpp

HEADERS  += testtaskmainwindow.h \
    timelinedockwidget.h \
    timeline/timelinegraphicslineitem.h \
    timeline/timelinegraphicstextitem.h \
    timeline/timelineeventitem.h \
    timeline/timelineview.h \
    timeline/timelinegraphicsview.h \
    timeline/timelineeventgraphicsview.h

FORMS    += testtaskmainwindow.ui \
    timelinedockwidget.ui \
    timeline/timelineeventitem.ui

RESOURCES += \
    tasktimeline.qrc
