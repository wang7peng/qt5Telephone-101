#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpFunc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    show_TimeandDate(ui->TimeList);

    connect(ui->button_delete, &QPushButton::clicked, this, [=](){
        Delete(ui->TimeList, delete_num);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
只在 timeanddate_page.ui 里使用了一次

 */
void show_TimeandDate(QListWidget *f)
{
    insertList_withSpin2(f, "1. General");
    // 由第一个元素选项控制 2 和 3 行显示内容
    if (1) {
        insertList_withSpin2(f, "2. NTP server");
        insertList_withSpin2(f, "3. Time zone");
    } else {
        insertList_withSpin2(f, "2. Time");
        insertList_withSpin2(f, "3. Date");
    }
    insertList_withSpin2(f, "4. Time format");
    insertList_withSpin2(f, "5. Date format");
}
