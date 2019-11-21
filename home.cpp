#include "home.h"
#include "ui_home.h"
#include "video.h"
#include "videowidget.h"

#include <QFileDialog>
#include <QStyle>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include <QPainter>

Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);

    //initializing variables
    videoWidget =new VideoWidget(this);
    ui->gridLayout->addWidget(videoWidget);
    mediaPlayer = new QMediaPlayer;
    media_playlist = new Playlist();
    msg_box = new MessageBox(this);

    //initalizing ui elements
    mediaPlayer->setVolume(50);
    mediaPlayer->setVideoOutput(videoWidget);
    videoWidget->show();
    this->play_list_viewmodel = new QStringListModel();
    ui->play_list_view->setModel(this->play_list_viewmodel);
    this->mediaPlayer->setPlaylist(media_playlist->getMedia_playlist());
    ui->play_button->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->previous_button->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->next_button->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui->open_button->setIcon(style()->standardIcon(QStyle::SP_FileIcon));
    ui->comboBox->addItem("Keyframes");
    ui->comboBox->addItem("Skim");
    ui->object_radio_btn->setChecked(true);

    //connecting signal and slots
    connect(this,SIGNAL(refresh_playlist()),this,SLOT(on_refresh_playlist_signal_emitted()));
    connect(this,SIGNAL(playing_started()),this,SLOT(on_playing_started()));
    connect(mediaPlayer,&QMediaPlayer::positionChanged,this,&Home::on_media_position_changed);
    connect(mediaPlayer,&QMediaPlayer::durationChanged, this, &Home::on_media_duration_changed);
    connect(ui->slider,&QSlider::sliderMoved,this,&Home::on_media_seek);

}

Home::~Home()
{
    delete ui;
}


void Home::on_play_button_clicked()
{
    if(this->is_playing){
        ui->play_button->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        ui->play_button->setText("Play");
        this->mediaPlayer->pause();    
    }else{
        ui->play_button->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        ui->play_button->setText("Pause");
        this->mediaPlayer->play();
        emit on_playing_started();

    }
    is_playing = !is_playing;

}

//add the logic to refresh the playlist
void Home::on_refresh_playlist_signal_emitted()
{

    this->play_list_viewmodel->setStringList(*this->media_playlist->getPlayList());
    this->ui->play_button->setEnabled(true);
}

void Home::on_open_button_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Video"), "D://", tr("Video Files (*.avi *.mp4 *.flv)"));
    if(fileName != nullptr){
        Video *video = new Video(fileName);
        try{
            media_playlist->addVideo(video);
        }catch(std::runtime_error e){
            msg_box->showError(e.what());
            delete video;
        }
        emit refresh_playlist();
    }
}

void Home::on_next_button_clicked()
{
    this->media_playlist->next();
    emit on_playing_started();
}

void Home::on_previous_button_clicked()
{
    this->media_playlist->previous();
    emit on_playing_started();
}

void Home::on_media_changed(int status)
{
    qDebug()<<"media changed signal received";
}

void Home::on_playing_started()
{
    qDebug()<<"playing started";
    ui->slider->setRange(0,(this->mediaPlayer->duration()/1000));
    qDebug()<<"range set to"<<(this->mediaPlayer->duration()/1000);
    ui->selected_video_label->setText(mediaPlayer->currentMedia().canonicalUrl().toString());
}

void Home::on_media_position_changed(qint64 progress)
{
    ui->slider->setValue(progress/1000);

    qDebug()<<"Progress"<<(progress/1000);
}

void Home::on_media_duration_changed(qint64 duration)
{
    ui->slider->setMaximum(duration/1000);
    qDebug()<<"duration changed"<<duration/1000;
}

void Home::on_media_seek(int position)
{
    mediaPlayer->setPosition(position*1000);
}




void Home::on_gen_sum_btn_clicked()
{
    QProcess p;
    QStringList params;
    QString pythonPath = "C:/ProgramData/Anaconda3/python.exe";
    QString pythonScript = "D:/Campus/FYP/Implementations/windows_tool/python_scripts/video_to_frames.py";
    QString inputVideo = "D:/Campus/FYP/Implementations/windows_tool/python_scripts/Jumps.mp4";
    QString outputPath = "D:/Campus/FYP/Implementations/windows_tool/python_scripts/fold/";
    params << pythonScript<<inputVideo<<outputPath;
    p.start(pythonPath, params);
    p.waitForFinished(-1);
    while(p.canReadLine()){
        qDebug()<<"this has been executed";
        qDebug()<<p.readLine();
    }
//    QString p_stdout = p.readAll();
//    QString p_stderr = p.readAllStandardError();
//    if(!p_stderr.isEmpty())
//        qDebug()<<"Python error:"<<p_stderr;
    //    qDebug()<<"Python result="<<p_stdout;
}

void Home::mousePressEvent(QMouseEvent *ev)
{

}

void Home::paintEvent(QPaintEvent *ev)
{

}
