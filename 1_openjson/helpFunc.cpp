#include "helpFunc.h"

#include <QFile>
#include <QJsonDocument>

QJsonObject OpenJson(QString file) {
    QFile f(file);
    if (!f.exists()) {
        ;
    }

    f.open(QIODevice::ReadOnly);
    QByteArray all = f.readAll();
    f.close();

    QJsonDocument doc = QJsonDocument::fromJson(all);

    return doc.object();
}

QString GetAccount_defaultLine(QJsonObject obj) {
    QJsonObject sip_account = obj["SIP Account"].toObject();

    /* 解析的配置文件相关的内容

    "SIP Account": {
        "Default Line": 0,                   // √
        "Line": [{
            "Line Enable": 1,                // √
            "Proxy and Registration": {},
            "RTP Advanced Setup": {},
            "Register Status": 1,
            "Subscriber Information": {},
            "Supplementary Services": {}
          }, {
          ...
          }],
        "QoS Settings": {},
        "Ring": [],
        "SIP Settings": {}
    },

    */

    int i = sip_account["Default Line"].toInt();
    auto line=sip_account["Line"].toArray();
    auto default_line = line[i].toObject();

    /* Line数组中单个元素 (default line) 内容:

        {
            "Line Enable": 1,                // √
            "Proxy and Registration": {},
            "RTP Advanced Setup": {},
            "Register Status": 1,
            "Subscriber Information": {
                "Account": "2024",           // √
                "Display Name": "2024",
                "Password": "sip123",
                "Phone Number": "2024"
            },
            "Supplementary Services": {}
        }

    */
    i = default_line["Line Enable"].toInt();
    auto child_obj = default_line["Subscriber Information"].toObject();
    QString account = child_obj["Account"].toString();

    return account;
}

QByteArray GetProxy_defaultLine(QJsonObject obj) {
    QJsonObject sip_account = obj["SIP Account"].toObject();

    /* 解析的配置文件相关的内容

    "SIP Account": {
        "Default Line": 0,                   // √
        "Line": [{
            "Line Enable": 1,                // √
            "Proxy and Registration": {},
            "RTP Advanced Setup": {},
            "Register Status": 1,
            "Subscriber Information": {},
            "Supplementary Services": {}
          }, {
          ...
          }],
        "QoS Settings": {},
        "Ring": [],
        "SIP Settings": {}
    },

    */
    int i = sip_account["Default Line"].toInt();
    // QJsonArray line=sip_account["Line"].toArray();
    auto line = sip_account.value("Line").toArray();
    auto default_line = line[i].toObject();

    /* Line数组中单个元素 (default line) 内容:

        {
            "Line Enable": 1,                       // √
            "Proxy and Registration": {
                "Allow DHCP Option 120 to Override SIP Server":	0,
                "Backup Outbound Port":	0,
                "Backup Outbound Server":	"",
                "Outbound Port":	0,
                "Outbound Server":	"",
                "Proxy Port":	5060,
                "Proxy Server":	"10.5.43.172",      // √
                "Transport":	0
            },
            "RTP Advanced Setup": {},
            "Register Status": 1,
            "Subscriber Information": {},
            "Supplementary Services": {}
        }

     */
    QJsonObject child_obj = default_line["Proxy and Registration"].toObject();
    QByteArray defaultline_proxy = child_obj["Proxy Server"].toString().toUtf8();

    return defaultline_proxy;
}
