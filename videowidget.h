#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

//#include <QVideoWidget>
#include <QLabel>

class RubberBand;

class VideoWidget:public QLabel
{
     Q_OBJECT
public:
    VideoWidget(QWidget *parent = nullptr);
    QRect *currentRect;
protected:
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

private:
    RubberBand *rubberBand_up;
    RubberBand *rubberBand_down;
    RubberBand *rubberBand_left;
    RubberBand *rubberBand_right;
    QPoint origin;
    QRect rect;
signals:
    void mousePressed();
};

#endif // VIDEOWIDGET_H
