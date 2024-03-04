#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

/*
模拟菜单里 Basic 功能的 Time & data 选项里内容
  General Manual/SNTP

*/

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int delete_num;
};

/*

note: 原先用类的方式写在 showadvance.h
*/
void show_TimeandDate(QListWidget *);

#endif // MAINWINDOW_H
