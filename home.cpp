#include "home.h"
#include "ui_home.h"
#include "video.h"

#include <QFileDialog>
#include <QStyle>
#include <QDebug>

Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);
    videoWidget =new QVideoWidget();
    ui->gridLayout->addWidget(videoWidget);
    mediaPlayer = new QMediaPlayer;
    mediaPlayer->setMedia(QUrl::fromLocalFile("D:/Entertainment/Movies/How.to.Train.Your.Dragon.2.2014.HDRip.XViD-juggs[ETRG].avi"));
    mediaPlayer->setVolume(50);
    mediaPlayer->setVideoOutput(videoWidget);
    videoWidget->show();
    this->video_list = new QList<Video*>();
    this->play_list = new QStringList();
    this->play_list_model = new QStringListModel();
    ui->play_list_view->setModel(this->play_list_model);

    ui->play_button->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->previous_button->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->next_button->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui->open_button->setIcon(style()->standardIcon(QStyle::SP_FileIcon));

    connect(this,SIGNAL(refresh_playlist()),this,SLOT(on_refresh_playlist_signal_emitted()));


}

Home::~Home()
{
    delete ui;
}


void Home::on_play_button_clicked()
{
    if(this->is_playing){
        ui->play_button->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        this->mediaPlayer->pause();

    }else{
        ui->play_button->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        this->mediaPlayer->play();
    }
    is_playing = !is_playing;
}

//add the logic to refresh the playlist
void Home::on_refresh_playlist_signal_emitted()
{
    this->play_list->clear();
    foreach (Video *video, *video_list) {
        this->play_list->append(video->getVideoName());
    }
    this->play_list_model->setStringList(*play_list);
}

void Home::on_open_button_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Video"), "D://", tr("Video Files (*.avi *.mp4 *.flv)"));
    Video *video =new Video(fileName);
    video_list->append(video);
    emit refresh_playlist();

}


