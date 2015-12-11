#include "reg.h"
#include "ui_reg.h"

#include <QString>
#include <QMessageBox>
#include <QDebug>

reg::reg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reg)
{
    ui->setupUi(this);

    QPixmap pix(qApp->applicationDirPath()+"/logo.png");
    ui->label_0->setPixmap(pix);
    ui->label_0->setScaledContents(true);
    ui->label_1->setText(QString::fromUtf8("Логин:"));
    ui->label_2->setText(QString::fromUtf8("Имя:"));
    ui->label_3->setText(QString::fromUtf8("Пароль:"));
     ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    ui->label_4->setText(QString::fromUtf8("Повторите пароль:"));
     ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    ui->label_5->setText(QString::fromUtf8("Город:"));
}

reg::~reg()
{
    delete ui;
}

void reg::on_buttonBox_accepted()
{
   dbase.connect("CityGIS.sqlite");

   if(ui->lineEdit_3->text()==ui->lineEdit_4->text()
           && dbase.userIsNotExist(ui->lineEdit_1->text())
           && ui->lineEdit_1->text()!=""
           && ui->lineEdit_2->text()!=""
           && ui->lineEdit_3->text()!=""
           && ui->lineEdit_4->text()!=""
           && ui->lineEdit_5->text()!=""
     )
   {
       qDebug() << QString::fromUtf8("Пароли совпадают!");

       dbase.addUser(ui->lineEdit_1->text(),
                     ui->lineEdit_3->text(),
                     ui->lineEdit_2->text(),
                     dbase.addCity(ui->lineEdit_5->text())
                    );
   }
   else
   {
       if(ui->lineEdit_3->text()!=ui->lineEdit_4->text())
        qDebug() << QString::fromUtf8("Пароли не совпадают!") << ui->lineEdit_3->text() << ui->lineEdit_4->text();
       if(!(dbase.userIsNotExist(ui->lineEdit_1->text())))
        qDebug() << QString::fromUtf8("Пользователь c таким логином уже существует");
       if (ui->lineEdit_1->text()==""
        || ui->lineEdit_2->text()==""
        || ui->lineEdit_3->text()==""
        || ui->lineEdit_4->text()==""
        || ui->lineEdit_5->text()=="")
        qDebug() << QString::fromUtf8("Не все поля были заполнены");
   }
}

void reg::on_buttonBox_rejected()
{
    reg::close();
}
