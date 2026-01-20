#ifndef GANTTWIDGET_H
#define GANTTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <vector>
#include "process.h"

class GanttWidget : public QWidget
{
    Q_OBJECT

    private:
        vector<Process> processes;

    public:
        GanttWidget(QWidget* parent = nullptr): QWidget(parent) {}
        void clear();
        void setData(const vector<Process>& list);
        void paintEvent(QPaintEvent*) override;


};

#endif // GANTTWIDGET_H
