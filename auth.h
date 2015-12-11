#pragma once
#ifndef AUTH_H
#define AUTH_H

#include <QWidget>
#include "gisdatabase.h"
#include "mainwindow.h"

namespace Ui {
class Auth;
}

class Auth : public QWidget
{
    Q_OBJECT

public:
    explicit Auth(QWidget *parent = 0);
    ~Auth();

signals:
    void accessGranted();

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_lineEdit_2_returnPressed();
    void openMainWindow();

private:
    Ui::Auth *ui;
    gisDatabase dbase;
    MainWindow *mw;
};

#endif // AUTH_H
