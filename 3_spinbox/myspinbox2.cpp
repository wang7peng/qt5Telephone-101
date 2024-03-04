#include "myspinbox2.h"
#include <QHBoxLayout>

mySpinBox2::mySpinBox2(int num, QWidget *parent)
    :QWidget(parent)
{
    leftImage.load(":/images/leftArrow.png");
    rightImage.load(":/images/rightArrow.png");

    leftArrow->setIcon(QIcon(leftImage));
    leftArrow->setAutoRaise(true);
    rightArrow->setIcon(QIcon(rightImage));
    rightArrow->setAutoRaise(true);

    default_num = num;
    label->setAlignment(Qt::AlignCenter);
    if (num < 10) {
        label->setText(QString("GMT+0%1:00").arg(num));
    } else {
        label->setText(QString("GMT+%1:00").arg(num));
    }

    QHBoxLayout *layout = new QHBoxLayout;
    // layout->setMargin(0); // before QT6
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(leftArrow);
    layout->addWidget(label);
    layout->addWidget(rightArrow);

    setLayout(layout);

    // 按左箭头时数值-1
    connect(leftArrow, &QToolButton::clicked, label, [=](){
        if (default_num == 0) {
            default_num = 23;
        } else {
            default_num -=1;
        }

        if (default_num < 10) {
            label->setText(QString("GMT+0%1:00").arg(default_num));
        } else {
            label->setText(QString("GMT+%1:00").arg(default_num));
        }
    });

    // 按右箭头时数值+1
    connect(rightArrow, &QToolButton::clicked, label, [=](){
        if (default_num == 23) {
            default_num = 0;
        } else {
            default_num += 1;
        }

        if (default_num < 10) {
            label->setText(QString("GMT+0%1:00").arg(default_num));
        } else {
            label->setText(QString("GMT+%1:00").arg(default_num));
        }
    });
}
