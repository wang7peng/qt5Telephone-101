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

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_13_pressed();

private:
    Ui::MainWindow *ui;

    int m_callState = 0;

    bool m_DNDState = false;
    bool state_RJ45 = true;
    int curAccountID = -1;
};
#endif // MAINWINDOW_H
