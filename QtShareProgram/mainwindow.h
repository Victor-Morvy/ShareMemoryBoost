#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "boost/interprocess/shared_memory_object.hpp"
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>

#include <QSpinBox>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer* _timer;

    QSpinBox* _spin_box;

private slots:
    void update();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    int* p;

    boost::interprocess::mapped_region* region;

};
#endif // MAINWINDOW_H
