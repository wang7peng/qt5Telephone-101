#ifndef MYSPINBOX2_H
#define MYSPINBOX2_H

#include <QToolButton>
#include <QWidget>
#include <QLabel>

/*
自定义小控件

在选项框左右加上小按钮控制数值增减

*/
class mySpinBox2 : public QWidget
{
    Q_OBJECT
public:
    explicit mySpinBox2(int num = -1, QWidget *parent = nullptr);

    QToolButton *leftArrow = new QToolButton;
    QToolButton *rightArrow = new QToolButton;

    QPixmap leftImage;
    QPixmap rightImage;
    QLabel *label = new QLabel;

    int default_num;
};


#endif // MYSPINBOX2_H
