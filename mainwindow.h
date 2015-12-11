#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include "viewport.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    viewport mapView;
};

#endif // MAINWINDOW_H
