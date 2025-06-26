#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->listenBtn->setStyleSheet("background-color: rgb(6,163,220)");


    ui->sendBtn->setStyleSheet("background-color: rgb(6,163,220)");


    ui->leport->setStyleSheet("color:blue");

    ui->ipBox->setStyleSheet("color:blue");
    ui->ipBox->setStyleSheet("background-color: rgb(6,163,220)");


    ui->textSend->setStyleSheet("border:red");


    ui->label_2->setStyleSheet("color:blue");
    ui->label_3->setStyleSheet("color:blue");
    ui->listWidget->setStyleSheet("border:2px solid blue");     //改变边框颜色
    //ui->textReceive->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px");
    //this->setStyleSheet("QWidget{border-top-left-radius:15px;border-top-right-radius:5px;}");

    this->setWindowIcon(QIcon(":/new/prefix1/images/qq.png"));

    connectSound = new QSound(":/new/prefix1/sounds/keke.wav", this);
    messSound = new QSound(":/new/prefix1/sounds/iphone.wav", this);
    severe = new QTcpServer(this);      //创建服务端
    this->enumAllIp();   //初始化ip地址
    connect(severe, &QTcpServer::newConnection, this, &Widget::newConnectSlot);     //有新连接时传入信号
}

Widget::~Widget()
{
    delete ui;
}

void Widget::enumAllIp()    //初始化本机所有可用的ipv4的地址并添加地址到列表框中
{
    QList <QHostAddress> addressList = QNetworkInterface::allAddresses();     //接收本机所有Ip地址
    QStringList addressList_str;
    for(int i = 0; i < addressList.size(); i++)
    {
        if(addressList.at(i).isNull()) continue;   //地址为空则跳过
        if(addressList.at(i).protocol() != QAbstractSocket::IPv4Protocol) continue;   //协议族不是ipv4的则跳过
        addressList_str.append(addressList.at(i).toString());      //符合条件的地址添加到列表中
    }

    ui->ipBox->addItems(addressList_str);   //将地址列表添加到地址列表框中
}

void Widget::newConnectSlot()    //新的客户端连接
{
    connectSound->play();
    clintSock = severe->nextPendingConnection();      //获取当前连接的客户端套接字
    clintList_sock.push_back(clintSock);           //将连接的客户端放入客户端列表中
    QString str = clintSock->peerAddress().toString() + ": " + QString::number(clintSock->peerPort()) + "已经连接";
    ui->listWidget->addItem(str);  //将连接信息放在列表窗口中

    connect(clintSock, &QTcpSocket::readyRead, this, &Widget::readMessage);  //准备接受信息
    connect(clintSock, &QTcpSocket::disconnected, this, &Widget::disConnectSlot);   //客户端的断开连接信息

}

void Widget::readMessage()      //读取客户端信息及给其他客户端发送信息
{
    QTcpSocket* currentClient = qobject_cast<QTcpSocket*>(sender()); // 直接获取信号发送者
    if (!currentClient || clintList_sock.isEmpty()) return;

    QByteArray arr = currentClient->readAll();
    if (arr.isEmpty()) return;

    messSound->play();

    // 1. 解析客户端消息（格式应为 [昵称]消息内容）
    QString rawMsg = QString::fromUtf8(arr);
    QString senderName = "Unknown";
    QString messageContent = rawMsg;

    if (rawMsg.startsWith("[") && rawMsg.contains("]")) {
        int endPos = rawMsg.indexOf("]");
        senderName = rawMsg.mid(1, endPos - 1); // 提取客户端昵称
        messageContent = rawMsg.mid(endPos + 1); // 提取实际消息
    }

    // 2. 服务端显示接收的消息（红色）
    QString displayMsg = QString("[%1] %2\n%3")
                       .arg(senderName)
                       .arg(QDateTime::currentDateTime().toString("HH:mm:ss"))
                       .arg(messageContent);
    ui->textReceive->setTextColor(Qt::red);
    ui->textReceive->append(displayMsg);
    ui->textReceive->setTextColor(Qt::black);

    // 3. 转发给其他客户端（原样转发原始消息）
    foreach (QTcpSocket* client, clintList_sock) {
        if (client != currentClient && client->isOpen()) {
            client->write(rawMsg.toUtf8());
        }
    }
}


void Widget::disConnectSlot()       //客户端断开连接时服务端显示断开信息
{
    connectSound->play();
    QString closeStr = QDateTime::currentDateTime().toString("dddd.yyyy.MM.dd HH:mm:ss") + ' ' + "clint close";
    ui->listWidget->addItem(closeStr);
}



void Widget::on_listenBtn_clicked()      //服务端开始监听
{
    QString currentIp = ui->ipBox->currentText();     //当前ip列表的Ip
    quint16 currentPort = ui->leport->text().toInt();       //当前文本框的显示的端口
    QHostAddress currentHostIP = QHostAddress(currentIp);   //地址字符串转换成主机Ip
    if(severe->isListening())     //客户端正在监听
    {
        severe->close();   //关闭客户端
        ui->listenBtn->setText("监听");
        ui->leport_2->setEnabled(true);
    }

    else    //客户端没有在监听
    {
        if(severe->listen(currentHostIP, currentPort))   //监听成功返回true
        {
            ui->listenBtn->setText("关闭监听");
            ui->leport_2->setEnabled(false);
        }

        else{    //监听失败
            QMessageBox::warning(this, "listen error", severe->errorString());   //出现错误提示消息框
            ui->leport_2->setEnabled(false);
        }
    }
}

void Widget::on_sendBtn_clicked()     //给客户端发送信息
{
    QString message = ui->textSend->toPlainText();
    QString nickname = ui->leport_2->text(); // 从 leport_2 获取服务端昵称

    if (message.isEmpty() || clintList_sock.isEmpty()) return;

    // 1. 构造带昵称的消息协议格式：[昵称]消息内容
    QString formattedMsg = QString("[%1]%2").arg(nickname).arg(message);

    // 2. 广播给所有客户端
    for (QTcpSocket* client : clintList_sock) {
        client->write(formattedMsg.toUtf8());
    }

    // 3. 服务端本地显示（蓝色）
    QString localDisplay = QString("[我] %1\n%2") // 标记为"服务端"或直接用昵称
                         .arg(QDateTime::currentDateTime().toString("HH:mm:ss"))
                         .arg(message);
    ui->textReceive->setTextColor(Qt::blue);
    ui->textReceive->append(localDisplay);
    ui->textReceive->setTextColor(Qt::black);

    ui->textSend->clear();
}





