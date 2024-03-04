#include "helpFunc.h"
#include <QFile>
#include <QLabel>
#include <QJsonDocument>
#include <QJsonObject>
#include "myspinbox2.h"

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

void insertList_withSpin2(QListWidget *f, QString r)
{
    auto *label = new QLabel(r);
    QWidget *w = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(w);

    QString str = r.mid(2);

    auto obj=OpenJson("D:/proj_qt6/sip-config.json");
    mySpinBox2 *sp = new mySpinBox2(get_NTPsettings_int(obj, "Time Zone"));

    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(label);
    layout->addWidget(sp);

    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(item->sizeHint());

    f->addItem(item);
    f->setItemWidget(item, w);
}

int get_NTPsettings_int(QJsonObject obj, QString node)
{
    /*
    "Administration": {
        "Daylight Saving Time": 0,
        "Factory Default Lock": 0,
        "Language": 0,
        "NTP Settings": {
            "NTP Enable": 0,
            "NTP synchronization (1 - 1440min)": 60,
            "Option 42": 0,
            "Primary NTP Server": "",
            "Secondary NTP Server": "",
            "Sync with host": "",
            "Time Format": 0,
            "Time Zone": 8
        },
        "Syslog Setting": { },
        "Web Access": { }
    },
    */
    auto administration = obj["Administration"].toObject();
    auto NTP_setting = administration["NTP Settings"].toObject();

    return NTP_setting[node].toInt();
}

void Delete(QListWidget *list, int delete_num)
{
    QListWidgetItem *item = list->item(delete_num);
    auto *item_widget = list->itemWidget(item);

    //TODO
    //myLineEdit *line = item_widget->findChild<myLineEdit *>();

}
