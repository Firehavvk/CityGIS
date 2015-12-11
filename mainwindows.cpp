#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "viewport.h"

#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mapView.setImage("C:\\QtProjects\\gis\\CityGIS\\maps\\mapTambov.png");
    //mapView.move(50,15);
    mapView.setScene(mapView.scn);


    //try
    //{
        ui->verticalLayout_0->addWidget(&mapView);
    //}
    //catch(...)
    //{
    //    qDebug()<<"errrrrorrrrrr";
    //}
    mapView.show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
