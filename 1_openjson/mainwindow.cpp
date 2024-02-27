#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpFunc.h"

#include <QDebug>
#include <QSettings>

QString accname;
//extern char glb_serverip[MAX_CHAR_LEN_64]
char glb_serverip[18];
//extern int Default_line; // in file: qt_pjsip_interface.c
int Default_line;

const int pixh = 48;
const int pixw = 48;

// 获取 sip-config.json 文件位置，具体配置写在 qt.config.ini
QString getPos_SipConf() {
    QSettings *s = new QSettings("D:\\proj_qt6\\qt.config.ini", QSettings::IniFormat);
    s->beginGroup("globals");
    QString sipconf = s->value("path_sip").toString();
    s->endGroup();

    if (sipconf.length() == 0) {
        qDebug() << "没有配置好";
    }
    return sipconf;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setAttribute(Qt::WA_AcceptTouchEvents);
    ui->setupUi(this);
    // setStyleSheet("background-color:rgb(155,155,255)");

    // 启动时候设置默认号码, 通过读取json配置文件获取号码
    QJsonObject obj=OpenJson(getPos_SipConf());
    QJsonObject sip_account = obj["SIP Account"].toObject();

    int i = sip_account["Default Line"].toInt();
    QJsonArray line=sip_account["Line"].toArray();
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
    auto subs_info = default_line["Subscriber Information"].toObject();

    Default_line = i;

    if (i != 1) {
        curAccountID = -1;
    } else {
        curAccountID = i;
        accname = GetAccount_defaultLine(obj);
    }

    // 设置话机拨打出去时信令 2024@10.5.43.172 中服务器的IP地址
    qstrncpy(glb_serverip, GetProxy_defaultLine(obj).constData(), sizeof(glb_serverip));
    qDebug() << glb_serverip;

    // 调整 ui 内的显示内容
    UpdateUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateUI()
{
    auto pixmap = QPixmap(":/images/reg.png");
    ui->labelICON->setPixmap(pixmap.scaled(pixh,pixw,Qt::KeepAspectRatio, Qt::SmoothTransformation));

    if (curAccountID == -1)
        ui->labelAccount->setText("No account");
    else
        ui->labelAccount->setText(accname);

    // DND图标控制, 默认不显示, 由 13 号按钮控制, 如果显示就同时显示文字
    if (m_DNDState) {
        ui->labelDND->setVisible(true);
        ui->labelDNDinIDLE->setText("Do not disturb");
    } else {
        ui->labelDND->setVisible(false);
        ui->labelDNDinIDLE->setText("");
    }

    // 联网图标控制, 默认网线插入成功联网, 如果断网就显示另一个断网图标
    if (state_RJ45) {
        ui->labelNet->setVisible(true);
        ui->labelNetOff->setVisible(false);
    } else {
        ui->labelNet->setVisible(false);
        ui->labelNetOff->setVisible(true);
    }
}

void MainWindow::on_pushButton_1_clicked()
{
    qDebug() << "点击" << ui->pushButton_1->text();
}


void MainWindow::on_pushButton_13_pressed()
{
    m_DNDState = !m_DNDState;
    this->UpdateUI();
}

