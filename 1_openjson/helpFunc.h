#ifndef HELPFUNC_H
#define HELPFUNC_H
#include <QJsonObject>
#include <QJsonArray>

/**
 * 辅助函数集
 */

// 功能: 将 json 文件内容解析成一个对象
QJsonObject OpenJson(QString);

// 功能: 配置文件中提供了十个号码, 获取账号
QString GetAccount_defaultLine(QJsonObject);

// 功能: 配置文件中提供了十个号码, 获取默认号码的服务器IP
QByteArray GetProxy_defaultLine(QJsonObject);


#endif // HELPFUNC_H
