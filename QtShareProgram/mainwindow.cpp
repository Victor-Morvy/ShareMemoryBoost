#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    windows_shared_memory shdmem{open_or_create, "Boost", read_write, 4};

    region = new mapped_region{shdmem, read_write};
    std::cout << std::hex << region->get_address() << '\n';

    p = (int*)region->get_address();

    _timer = new QTimer;

    _spin_box = ui->spinBox;
    connect(_timer, SIGNAL(timeout()), this, SLOT(update()));

    _timer->start(62);
}

MainWindow::~MainWindow()
{
    delete _timer;
    delete region;
    delete ui;
}

void MainWindow::update()
{
    _spin_box->blockSignals(true);

    _spin_box->setValue((int)*p);

    _spin_box->blockSignals(false);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    *p = arg1;
}

