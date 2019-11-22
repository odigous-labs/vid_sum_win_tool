#include "videowidget.h"
#include <QDebug>
#include <QMouseEvent>
#include "rubberband.h"
#include <QStyleOptionRubberBand>
#include <QPainter>

VideoWidget::VideoWidget(QWidget *parent)
    : QVideoWidget(parent),rubberBand_up(nullptr),
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
    //QVideoWidget::mouseMoveEvent(event);
}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"Mouse Press event occured";
    origin = event->pos();
    if (!rubberBand_up)
        rubberBand_up = new RubberBand( this->parentWidget());
    if (!rubberBand_down)
        rubberBand_down = new RubberBand( this->parentWidget());
    if (!rubberBand_left)
        rubberBand_left = new RubberBand(this->parentWidget());
    if (!rubberBand_right)
        rubberBand_right =  new RubberBand(this->parentWidget());

    rubberBand_up->setGeometry(QRect(origin, QSize()));
    rubberBand_down->setGeometry(QRect(origin, QSize()));
    rubberBand_left->setGeometry(QRect(origin,QSize()));
    rubberBand_right->setGeometry(QRect(origin,QSize()));
    rubberBand_up->show();
    rubberBand_down->show();
    rubberBand_left->show();
    rubberBand_right->show();
    //QVideoWidget::mousePressEvent(event);
}


void VideoWidget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"Mouse Release event occured";
    rect = rubberBand_up->geometry();
    update();
    //QVideoWidget::mouseReleaseEvent(event);

}

void VideoWidget::paintEvent(QPaintEvent *ev)
{
    qDebug()<<"paint event occured";
    QVideoWidget::paintEvent(ev);
    QPainter painter(this);
    painter.save();
    painter.setBrush(Qt::red);
    if(!rect.isNull())
       painter.drawRect(rect);
    painter.restore();
}

