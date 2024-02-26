#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void UpdateUI(); // 根据呼叫状态更新UI

private:
    Ui::MainWindow *ui;

    int m_callState = 0;
    int curAccountID = -1;
};
#endif // MAINWINDOW_H
