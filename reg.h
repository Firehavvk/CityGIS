#pragma once
#ifndef REG_H
#define REG_H

#include <QDialog>
#include "gisdatabase.h"

namespace Ui {
class reg;
}

class reg : public QDialog
{
    Q_OBJECT

public:
    explicit reg(QWidget *parent = 0);
    ~reg();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::reg *ui;
    gisDatabase dbase;
};

#endif // REG_H
