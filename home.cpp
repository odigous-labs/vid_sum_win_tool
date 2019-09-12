#include "home.h"
#include "ui_home.h"
#include <QtMultimediaWidgets/qvideowidget.h>

Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);
    videoWidget =new QVideoWidget();
    ui->gridLayout->addWidget(videoWidget);
}

Home::~Home()
{
    delete ui;
}

