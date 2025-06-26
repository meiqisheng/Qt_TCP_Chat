#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->connectBtn->setStyleSheet("background-color: rgb(6,163,220)");
    ui->sendBtn->setStyleSheet("background-color: rgb(6,163,220)");
    ui->leport->setStyleSheet("color:blue");
    ui->leipAddress->setStyleSheet("color:blue");

    ui->listWidget->setStyleSheet("border:2px solid blue");

    socket = new QTcpSocket(this);
    connectState = false;     //未连接状态

    messageSound = new QSound(":/new/prefix1/sounds/iphone.wav", this);
    connectSound = new QSound(":/new/prefix1/sounds/keke.wav", this);

    this->setWindowIcon(QIcon(":/new/prefix1/image/qq.png"));

    connect(socket, &QTcpSocket::readyRead, this, &Widget::readMessage);    //接收信息
    connect(socket, &QTcpSocket::disconnected, this, &Widget::disconnectSlot);   //打印断开连接信息
}

Widget::~Widget()
{
    delete ui;
}


void Widget::readMessage()    //接收信息
{
    messageSound->play();
    QByteArray arr = socket->readAll();
    QString rawMsg = QString::fromUtf8(arr); // 原始消息格式应为 "[昵称]消息内容"

    // 解析昵称和消息内容
    QString senderName = "对方"; // 默认名称（可自定义）
    QString messageContent = rawMsg;

    // 检查消息格式是否为 [昵称]消息内容
    if (rawMsg.startsWith("[") && rawMsg.contains("]")) {
        int endPos = rawMsg.indexOf("]");
        senderName = rawMsg.mid(1, endPos - 1); // 提取昵称
        messageContent = rawMsg.mid(endPos + 1); // 提取消息内容
    }

    // 格式化显示（含对方昵称和时间戳）
    QString displayMsg = QString("[%1] %2\n%3")
                       .arg(senderName)
                       .arg(QDateTime::currentDateTime().toString("HH:mm:ss"))
                       .arg(messageContent);

    // 显示接收的消息（红色）
    ui->textReceive->setTextColor(Qt::red);
    ui->textReceive->append(displayMsg);
    ui->textReceive->setTextColor(Qt::black); // 恢复默认颜色
}


void Widget::disconnectSlot()    //打印连接断开信息
{
    ui->listWidget->addItem("clint disconnected");
}


void Widget::on_connectBtn_clicked()      //与客户端连接或者断开
{
    QString ipStr = ui->leipAddress->text();    //界面显示的地址
    quint16 currentPort = ui->leport->text().toInt();   //界面显示的当前端口
    if(!connectState)    //客户端还未连接服务端
    {
        socket->connectToHost(ipStr, currentPort);   //连接服务端
        if(socket->waitForConnected())   //等待连接成功
        {
            ui->listWidget->addItem("连接成功");
            ui->connectBtn->setText("关闭连接");
            ui->leport_2->setEnabled(false);
            connectSound->play();
            connectState = true;
        }

        else     //连接失败
        {
            QMessageBox::warning(this, "连接失败", socket->errorString());   //连接错误信息提醒
            ui->leport_2->setEnabled(true);
        }
    }

    else   //客户端已经连接
    {
        socket->close();   //关闭套接字，此时会发送disconnected信号
        connectSound->play();
        ui->connectBtn->setText("连接");
        connectState = false;  // 关键修复
        ui->leport_2->setEnabled(true);
    }
}


void Widget::on_sendBtn_clicked()    //给服务端发送信息
{
    QString str = ui->textSend->toPlainText();
    QString nickname = ui->leport_2->text();      // 从 leport_2 获取昵称
    QString formattedMsg = QString("[%1]%2").arg(nickname).arg(str);
    if(socket->isOpen() && socket->isValid())
    {
        socket->write(formattedMsg.toUtf8());    //给服务端发送信息
        ui->textSend->clear();
    }

    // 2. 本地显示自己发送的消息（蓝色）
    QString showStr = QString("[我] %1\n%2")  // "我"或直接用昵称
                         .arg(QDateTime::currentDateTime().toString("HH:mm:ss"))
                         .arg(str);
    ui->textReceive->setTextColor(Qt::blue);
    ui->textReceive->append(showStr);     //显示自己发送的信息
    ui->textReceive->setTextColor(Qt::black); // 恢复默认颜色（可选）
}








