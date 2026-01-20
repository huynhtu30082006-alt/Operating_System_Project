#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "IO.h"
#include "algorithms.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ganttWidget = new GanttWidget;
    ui->scrollArea->setWidget(ganttWidget);
    ui->scrollArea->setWidgetResizable(false);

    labelNoData = new QLabel("No Process Available", ui->tableWidget);
    labelNoData->setAlignment(Qt::AlignCenter);
    labelNoData->setStyleSheet("color: gray; font-size: 16px; font-style: italic;");

    labelNoData->setGeometry(ui->tableWidget->rect());
    labelNoData->show();


    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::button_add_process);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::button_save_output);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::button_load_process);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::button_remove_process);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::button_run_fcfs);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::button_run_sjf);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::button_exit);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showTable()
{
    int column = 3;
    ui->tableWidget->setColumnCount(column);
    ui->tableWidget->setRowCount(currentResult.size());

    //Set name column
    QStringList headers;
    headers << "PID" << "Arrival" << "Burst";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    for(int i = 0; i < currentResult.size(); i++)
    {
        QTableWidgetItem *item0 = new QTableWidgetItem(QString::fromStdString(currentResult[i].get_pid()));
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(currentResult[i].get_arrivalTime()));
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(currentResult[i].get_burstTime()));

        item0->setTextAlignment(Qt::AlignCenter);
        item1->setTextAlignment(Qt::AlignCenter);
        item2->setTextAlignment(Qt::AlignCenter);

        ui->tableWidget->setItem(i, 0, item0);
        ui->tableWidget->setItem(i, 1, item1);
        ui->tableWidget->setItem(i, 2, item2);

    }

    //cột tự co dãn theo nội dung
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void MainWindow::showTable(const vector<Process>& L)
{
    labelNoData->hide();
    //Set number of column and row
    int column = 8;
    ui->tableWidget->setColumnCount(column);
    ui->tableWidget->setRowCount(L.size());

    //Set name column
    QStringList headers;
    headers << "PID" << "Arrival" << "Burst" << "Start" << "Completion" << "Turnaround" << "Waiting" << "Response";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < L.size(); i++)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(L[i].get_pid())));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(L[i].get_arrivalTime())));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(L[i].get_burstTime())));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(L[i].get_startTime())));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(L[i].get_completionTime())));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(L[i].get_turnaroundTime())));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(L[i].get_waitingTime())));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString::number(L[i].get_responseTime())));

    }

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        for (int col = 0; col < ui->tableWidget->columnCount(); ++col)
        {
            QTableWidgetItem *item = ui->tableWidget->item(row, col);
            if (item)
            {
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
    //cột tự co dãn theo nội dung
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void MainWindow::showAverage(const vector<Process>& L)
{
    if(L.empty())
    {
        ui->labelAvgWaiting->display(0.0);
        ui->labelAvgTurnaround->display(0.0);
        return;
    }

    double avgW = 0, avgT = 0;

    for(const auto&p : L)
    {
        avgW += p.get_waitingTime();
        avgT += p.get_turnaroundTime();
    }

    avgW/=L.size();
    avgT/=L.size();

    ui->labelAvgWaiting->display(avgW);
    ui->labelAvgTurnaround->display(avgT);

}

void MainWindow::clearResultView()
{
    currentResult.clear();
    ui->labelAvgWaiting->display(0);
    ui->labelAvgTurnaround->display(0);
    ganttWidget->clear();

}

void MainWindow::clearAllView()
{
    currentResult.clear();

    ui->tableWidget->clearContents();

    labelNoData->setGeometry(ui->tableWidget->rect());
    labelNoData->show();

    ui->labelAvgWaiting->display(0);
    ui->labelAvgTurnaround->display(0);
    ganttWidget->clear();


}

void MainWindow::button_add_process()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Choose file CSV", "", "CSV Files (*csv)");
    if (file_name.isEmpty())
    {
        return;
    } //user cancel

    IO i;
    i.readCSV(file_name.toStdString(), lp);
    currentResult = lp.get_ref_processes();
    QMessageBox::information(this, "Done", "Read File Successful");

    labelNoData->hide();
    showTable();
}

void MainWindow::button_remove_process()
{
    // Kiểm tra selection THẬT
    if (!ui->tableWidget->selectionModel()->hasSelection())
    {
        auto reply = QMessageBox::question(this, "Clear All", "No process selected.\n Do you want to remove All Processes?", QMessageBox::Yes | QMessageBox::No );

        if (reply == QMessageBox::Yes)
        {
            lp.clear();
            current_algo = AlgorithmType::NONE;
            clearAllView();
        }
        return;
    }

    // Remove 1 process
    int row = ui->tableWidget->currentRow();
    vector<Process>& prcs = lp.get_ref_processes();

    if (row >= 0 && row < prcs.size())
    {
        prcs.erase(prcs.begin() + row);
        refresh();
    }
}

void MainWindow::button_run_fcfs()
{
    current_algo = AlgorithmType::FCFS;

    currentResult= runFCFS(lp.get_val_processes());
    //sort theo arrival time trước
    vector<Process> display_prcs = sort_for_show_table(currentResult);
    showTable(display_prcs);
    showAverage(display_prcs);
    ganttWidget->setData(display_prcs);

}

void MainWindow::button_run_sjf()
{
    current_algo = AlgorithmType::SJF;

    currentResult = runSJF(lp.get_val_processes());
    //sort theo arrival time trước
    vector<Process> display_prcs = sort_for_draw_gantt(currentResult);
    showTable(display_prcs);
    showAverage(display_prcs);
    ganttWidget->setData(display_prcs);

}

void MainWindow::button_save_output()
{

    if (currentResult.empty())
    {
        QMessageBox::warning(
            this,
            "Cannot Save",
            "No result to save.\nPlease run an algorithm first."
            );
        return;
    }

    QString file_name = QFileDialog::getSaveFileName(this, "Save Output", "", "CSV Files (*.csv)");

    if (file_name.isEmpty())
    {
        return;
    }
    IO::save_to_file(file_name.toStdString(), currentResult);

    QMessageBox::information(this, "Done", "Save Output Successful");

}

void MainWindow::button_load_process()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Load Output File", "",  "CSV Files (*.csv);;Text files (*.txt)");

    if (file_name.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Can't found file!!!");
        return;
    }

    currentResult = IO::load_file(file_name.toStdString());

    lp.clear();

    for(int i = 0; i < currentResult.size(); i++)
    {
        Process P(currentResult[i].get_pid(), currentResult[i].get_arrivalTime(), currentResult[i].get_burstTime());
        lp.addProcess(P);
    }

    if(currentResult.empty())
    {
        return;
    }

    labelNoData->hide();

    showTable(currentResult);
    showAverage(currentResult);
    ganttWidget->setData(currentResult);

}

void MainWindow::refresh()
{
    if (lp.get_val_processes().empty())
    {
        clearAllView();
        return;
    }

    if (current_algo == AlgorithmType::FCFS)
    {
        currentResult= runFCFS(lp.get_val_processes());
        //sort theo arrival time trước
        vector<Process> display_prcs = sort_for_show_table(currentResult);
        showTable(display_prcs);
        showAverage(display_prcs);
        ganttWidget->setData(display_prcs);

    }
    else
    {
        currentResult = runSJF(lp.get_val_processes());
        //sort theo arrival time trước
        vector<Process> display_prcs = sort_for_draw_gantt(currentResult);
        showTable(display_prcs);
        showAverage(display_prcs);
        ganttWidget->setData(display_prcs);
    }

}

void MainWindow::button_exit()
{
    auto reply = QMessageBox::question(this, "Exit", "Do you want to exit?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        close();
    }
}
