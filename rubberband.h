#ifndef RUBBERBAND_H
#define RUBBERBAND_H

#include <QRubberBand>

class RubberBand:public QRubberBand
{
public:
    RubberBand(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *ev);

};

#endif // RUBBERBAND_H
