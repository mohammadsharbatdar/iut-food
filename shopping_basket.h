#ifndef SHOPPING_BASKET_H
#define SHOPPING_BASKET_H

#include <QWidget>
#include<string>
#include<QTcpSocket>
#include<QTcpServer>

namespace Ui {
class shopping_basket;
}

class shopping_basket : public QWidget
{
    Q_OBJECT

public:
    explicit shopping_basket(QWidget *parent = nullptr);

    void click_back_button();

    static QMap<QString,QMap<QString,QPair<QString,QString>>> shop_basket;

    static int sum;

    void show_list();

    void receive_message();

    std::string message;

    QTcpSocket socket;

    ~shopping_basket();

signals:

    void click_back();

    void click_server();

public slots:
    void on_back_button_clicked();

    void send_message();

private:
    Ui::shopping_basket *ui;
};

#endif // SHOPPING_BASKET_H

