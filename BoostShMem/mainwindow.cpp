#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boost/interprocess/shared_memory_object.hpp"
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
#include <QDebug>

using namespace boost::interprocess;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //    shared_memory_object shdmem{open_or_create, "Boost", read_write};
    //    shdmem.truncate(1024);
    //    qDebug() << shdmem.get_name() << '\n';
    //    offset_t size;
    //    if (shdmem.get_size(size))
    //    qDebug() << size << '\n';
    shared_memory_object shdmem{open_or_create, "Region", read_write};
    shdmem.truncate(0x400000);

    mapped_region region{shdmem, read_write};
    std::cout << std::hex << region.get_address() << '\n';

    void* mem = region.get_address();
    char* reg = (char*)mem;
    int i = 0;
    reg[i++] = 'O';
    reg[i++] = 'L';
    reg[i++] = 'A';

    std::cout << reg << std::endl;

    std::cout << std::dec << region.get_size() << '\n';
    mapped_region region2{shdmem, read_only};
    std::cout << std::hex << region2.get_address() << '\n';
    std::cout << std::dec << region2.get_size() << '\n';

    mapped_region region3{shdmem, read_write};
    std::cout << "Regiao 3 " << std::hex << region3.get_address() << '\n';

       std::cout << "PULAAA" << std::endl;


    shared_memory_object shdmem2{open_or_create, "Region", read_write};
    mapped_region region4{shdmem2, read_write};
    std::cout << "Regiao 4 " << std::hex << region4.get_address() << '\n';

    std::cout << std::hex << region.get_address() << '\n';

    void* mem2 = region4.get_address();
    char* reg2 = (char*)mem2;

    std::cout << reg2 << std::endl;

    reg2[i++] = ' ';
    reg2[i++] = 'M';
    reg2[i++] = 'U';
    reg2[i++] = 'N';
    reg2[i++] = 'D';
    reg2[i++] = 'O';
    reg2[i++] = '\0';

    void* mem3 = region3.get_address();
    char* reg3 = (char*)mem3;
    std::cout << reg3 << std::endl;

    std::cout << "---------" << std::endl;
    void* mem5 = region.get_address();
    char* reg5 = (char*)mem5;
    std::cout << reg5 << std::endl;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

