#include "shopping_basket.h"
#include "ui_shopping_basket.h"
#include "menu_restaurant.h"
#include<QLabel>
#include<QString>
#include<QTextStream>
#include<QListWidgetItem>
#include<string>
#include<QMessageBox>

shopping_basket::shopping_basket(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::shopping_basket)
{
    ui->setupUi(this);

    connect(this, &shopping_basket::click_back_button, this, &shopping_basket::send_message);

    connect(this, &shopping_basket::receive_message, this, &shopping_basket::on_back_button_clicked);

    socket.connectToHost("127.0.0.1",6006);

    if(socket.waitForConnected(1000))
    {

        receive_message();

    }

    show_list();

    ui->price_lineedit->setText(QString::number(sum));

}

shopping_basket::~shopping_basket()
{
    delete ui;
}

QMap<QString,QMap<QString,QPair<QString,QString>>> shopping_basket::shop_basket;

int shopping_basket::sum = 0;

void shopping_basket::show_list()
{

    QString food_type;

    QString food_name;

    QString food_details;

    QString p;

    QString price;

    for(auto i = shop_basket.begin(); i != shop_basket.end(); ++i)
    {

        food_type = i.key();

        QMap<QString,QPair<QString,QString>> shop = i.value();

        food_name = shop.firstKey();

        QPair<QString,QString> str = shop[food_name];

        food_details = str.first;

        price = str.second;

        QLabel *label = new QLabel();

        label->setText(food_type + " | " + food_name + " | " + food_details + " | " + price);//

        QListWidgetItem *li = new QListWidgetItem(ui->bord_ListWidget);

        ui->bord_ListWidget->setItemWidget(li,label);

    }

}

void shopping_basket::click_back_button()
{

    message = "back";

    emit click_server();

}

void shopping_basket::on_back_button_clicked()
{

    menu_restaurant *mr = new menu_restaurant();

    mr->setAttribute(Qt::WA_DeleteOnClose);

    mr->show();

    this->close();

}

void shopping_basket::send_message()
{

    if(socket.state() == QTcpSocket::ConnectedState)
    {

        QByteArray byte(this->message.c_str(),this->message.length());

        if(socket.write(byte) > 0)
        {

            if(!socket.waitForBytesWritten(1000))
            {

                QMessageBox::information(this,"not success","message not send!!!");

            }

        }

    }

}

void shopping_basket::receive_message()
{

    if(socket.state() == QTcpSocket::ConnectedState)
    {

        if(socket.waitForReadyRead(-1))
        {

            QByteArray byte = socket.readAll();

            this->message = std::string(byte.constData(),byte.length());

            if(message == "start back")
            {

                message = "";

                emit click_back();

            }

        }

    }

}

