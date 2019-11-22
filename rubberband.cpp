#include "rubberband.h"
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QPaintEvent>

RubberBand::RubberBand(QWidget *parent):
    QRubberBand(QRubberBand::Rectangle,parent)
{

}

void RubberBand::paintEvent(QPaintEvent *ev)
{
//   qDebug()<<"paint event inside the rubberband class has called";
   QPainter painter;
    QPen pen(Qt::red, 6);
    pen.setStyle(Qt::SolidLine);
   painter.begin(this);
   painter.setPen(pen);
    //painter.setBrush(QColor(255, 0, 0, 255));
  painter.fillRect(ev->rect(),QBrush(QColor(255, 0, 0, 255)));
   painter.end();
    //QRubberBand::paintEvent(ev);

}


