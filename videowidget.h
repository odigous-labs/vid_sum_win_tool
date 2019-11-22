#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QVideoWidget>

class RubberBand;

class VideoWidget:public QVideoWidget
{
public:
    VideoWidget(QWidget *parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent *ev);

private:
    RubberBand *rubberBand_up;
    RubberBand *rubberBand_down;
    RubberBand *rubberBand_left;
    RubberBand *rubberBand_right;
    QPoint origin;
    QRect rect;
};

#endif // VIDEOWIDGET_H
