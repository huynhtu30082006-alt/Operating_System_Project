#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <vector>
#include "ganttwidget.h"
#include "list_process.h"
#include "ganttwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
            enum class AlgorithmType
            {
                NONE,
                FCFS,
                SJF
            };

            // Default state is before run or after remove
            AlgorithmType current_algo = AlgorithmType::NONE;

            MainWindow(QWidget *parent = nullptr);
            ~MainWindow();
            void button_add_process();
            void button_remove_process();
            void button_save_output();
            void button_load_process();
            void button_run_fcfs();
            void button_run_sjf();
            void button_exit();

            //Helper
            void showTable(const vector<Process>& L);
            void showTable();
            void showAverage(const vector<Process>& L);
            void gantt_chart(const vector<Process>& L);
            void clearAllView();
            void clearResultView();
            void refresh();

    private:
        Ui::MainWindow *ui;
        QLabel* labelNoData;
        list_process lp;
        vector<Process> currentResult;
        GanttWidget *ganttWidget;

};



#endif // MAINWINDOW_H
