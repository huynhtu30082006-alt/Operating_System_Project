#include "ganttwidget.h"

void GanttWidget::clear()
{
    processes.clear();
    update();
}
void GanttWidget::setData(const vector<Process>& L)
{
    processes = L;

    int scale = 30, baseX = 20;
    int maxTime = 0;
    for (auto& p : processes)
    {
        maxTime = max(maxTime, p.get_completionTime());
    }
    setMinimumSize(baseX + maxTime * scale + 40, 150); //quyết định kích thước scroll
    update(); //gọi paintEvent
}

void GanttWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int scale = 30;
    int baseX = 20;
    int y = 40;
    int timeY = y + 70;

    int currentTime = 0;

    for (const auto& p : processes)
    {
        // VẼ IDLE NẾU CÓ KHOẢNG TRỐNG
        if (p.get_startTime() > currentTime)
        {
            int idleStart = currentTime;
            int idleEnd = p.get_startTime();

            int idleX = baseX + idleStart * scale;
            int idleW = (idleEnd - idleStart) * scale;

            QRect idleRect(idleX, y, idleW, 40);
            painter.setBrush(QColor(80, 80, 80)); // xám
            painter.drawRect(idleRect);
            painter.drawText(idleRect, Qt::AlignCenter, "IDLE");

            painter.drawText(idleX, timeY, QString::number(idleStart));
            painter.drawText(idleX + idleW, timeY, QString::number(idleEnd));

            painter.setBrush(Qt::NoBrush);
        }

        // PROCESS
        int startX = baseX + p.get_startTime() * scale;
        int w = (p.get_completionTime() - p.get_startTime()) * scale;

        QRect rect(startX, y, w, 40);
        painter.drawRect(rect);

        painter.drawText(rect, Qt::AlignCenter,
                         QString::fromStdString(p.get_pid()));

        painter.drawText(startX, timeY,
                         QString::number(p.get_startTime()));

        painter.drawText(startX + w, timeY,
                         QString::number(p.get_completionTime()));

        currentTime = p.get_completionTime();
    }
}
