#include "videowidget.h"
#include <QDebug>
#include <QMouseEvent>
#include "rubberband.h"
#include <QStyleOptionRubberBand>
#include <QPainter>

VideoWidget::VideoWidget(QWidget *parent)
    : QLabel(parent),
      currentRect(nullptr),
      rubberBand_up(nullptr),
      rubberBand_down(nullptr),
      rubberBand_left(nullptr),
      rubberBand_right(nullptr){

}

void VideoWidget::mouseMoveEvent(QMouseEvent *event)
{
    qDebug()<<"Mouse move event occured";
    int o_x = origin.x();
    int o_y = origin.y();
    int e_x = event->pos().x();
    int e_y =event->pos().y();
    qDebug()<<"o_x "<<o_x<<"o_y "<< o_y<<"e_x "<<e_x<<"e_y "<<e_y;
    rubberBand_up->setGeometry(QRect(o_x,o_y,e_x-o_x,2).normalized());
    rubberBand_down->setGeometry(QRect(o_x,e_y,e_x-o_x,2).normalized());
    rubberBand_right->setGeometry(QRect(e_x,e_y,2,o_y-e_y).normalized());
    rubberBand_left->setGeometry(QRect(o_x,o_y,2,e_y-o_y).normalized());
    currentRect->setBottomRight(event->pos());
    //QVideoWidget::mouseMoveEvent(event);

}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"Mouse Press event occured";
    origin = event->pos();
    if (!rubberBand_up)
        rubberBand_up = new RubberBand( this);
    if (!rubberBand_down)
        rubberBand_down = new RubberBand( this);
    if (!rubberBand_left)
        rubberBand_left = new RubberBand(this);
    if (!rubberBand_right)
        rubberBand_right =  new RubberBand(this);

    rubberBand_up->setGeometry(QRect(origin, QSize()));
    rubberBand_down->setGeometry(QRect(origin, QSize()));
    rubberBand_left->setGeometry(QRect(origin,QSize()));
    rubberBand_right->setGeometry(QRect(origin,QSize()));
    rubberBand_up->show();
    rubberBand_down->show();
    rubberBand_left->show();
    rubberBand_right->show();
    currentRect = new QRect(origin,origin);
    emit mousePressed();
    //QVideoWidget::mousePressEvent(event);
}


void VideoWidget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"Mouse Release event occured";
    rect = rubberBand_up->geometry();
    update();
    //QVideoWidget::mouseReleaseEvent(event);

}



