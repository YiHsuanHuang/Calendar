#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_calendarWidget_clicked(const QDate &date);

    void on_timeEdit_timeChanged(const QTime &time);

    void on_Enter_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *clock;
    QVector<QString> timeSequence;

private slots:
    void updateTime();
    void on_load_clicked();
    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);
};

#endif // MAINWINDOW_H
