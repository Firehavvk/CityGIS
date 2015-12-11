#pragma once
#ifndef VIEWPORT
#define VIEWPORT

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QString>

#include <QMouseEvent>
#include <QtGui>

class viewport : public QGraphicsView
{

public:
    QGraphicsScene* scn;
    viewport(){scn = new QGraphicsScene();}
    ~viewport(){}

    void setImage(QString path)
    {
        QImage img(path);
        scn->addPixmap(QPixmap::fromImage(img));
    }
    void mousePressEvent(QMouseEvent *event)
    {
        qDebug() << "viewport: mouse click coords:" << event->x() << event->y();
        QGraphicsView::mousePressEvent(event);

        // get image coords from the view coord
        QPointF scenePt = mapToScene(event->pos());
        qDebug() << "bitmap: mouse click coords:" << scenePt.x() << scenePt.y();

    }
};

#endif // VIEWPORT

