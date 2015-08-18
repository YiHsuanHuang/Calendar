#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QDebug>
#include <QString>
#include <QTime>
#include <QFileDialog>
#include <QTimer>
#include <QVector>


QString timetoString;
QString datetoString;
QString totaltoString;
QString todolist;
QTime choose_time;
QTime current_time;
QTime time;
QTime t;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}


MainWindow::~MainWindow()
{
    delete ui;


}

int status = 0;

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    datetoString = date.toString() + '\0';
    status++;
    //ui->textBrowser->append(date.toString());
}

void MainWindow::on_timeEdit_timeChanged(const QTime &time)
{
    choose_time = time;
    timetoString = time.toString();
    status++;
//    if(status >= 2)
//    {
//        ui->Enter->setEnabled(true);
//    }
    //qDebug() << choose_time;
}

void MainWindow::on_Enter_clicked()
{
    todolist = ui->lineEdit->text();
    totaltoString = datetoString + '\0' + timetoString  + '\0' + todolist;
    ui->textBrowser->append(totaltoString);


    clock = new QTimer;
    clock->setInterval(1000);
    connect(clock, SIGNAL(timeout()), this, SLOT(updateTime()));

    current_time = current_time.currentTime();
    clock->start();

    QFile nfile("todolist.txt");
    if(nfile.open(QFile::Append|QFile::Text))
    {
        QTextStream out(&nfile);
        out << totaltoString << endl;
    }
}


void MainWindow::updateTime()
{

    time = time.currentTime();
    qDebug() << time.toString("hh:mm:ss.zzz");

    //timeSequence.append(time.toString("hh:mm:ss.zzz"));

    t = choose_time.addSecs(-60*30);

    //qDebug() << choose_time.toString("hh:mm:ss.zzz");
    //qDebug() << t;
    //qDebug() << current_time.toString("hh:mm:ss");
    //clock->start();
    if(time >= t)
    {
        clock->stop();
        ui->warning->append("warning!!!");
    }
    //QDateTime date;
    //date = date.currentDateTime();
    //qDebug() << date.toString("yyyy-MM-dd");
}

void MainWindow::on_load_clicked()
{
    QFile nfile("todolist.txt");

    if(nfile.open(QIODevice::ReadOnly))
    {
        QString nline;
        QTextStream in(&nfile);
        while(!in.atEnd())
        {
            nline = in.readLine();
            ui->textBrowser->append(nline);
        }
    }
}

void MainWindow::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->Enter->setEnabled(true);
}
