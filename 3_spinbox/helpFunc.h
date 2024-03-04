#ifndef HELPFUNC_H
#define HELPFUNC_H

/**
 * 辅助函数集
 *
 */

#include <QString>
#include <QListWidget>
#include <QHBoxLayout>
#include <QJsonObject>

// 功能: 将 json 文件内容解析成一个对象
QJsonObject OpenJson(QString);

int get_NTPsettings_int(QJsonObject obj, QString node);

/*
每个 item 有 label + myspinbox, 专门为 Time & Date 创建

note: 原先用类的方式写在 showfunction.h
*/
void insertList_withSpin2(QListWidget *, QString);

/*
实现点击删除按钮就清除列表功能

*/
void Delete(QListWidget *list, int delete_num);

#endif // HELPFUNC_H
