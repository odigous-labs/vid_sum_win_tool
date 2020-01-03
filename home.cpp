#include "home.h"
#include "ui_home.h"
#include "video.h"
#include "videowidget.h"
#include "videoframegrabber.h"
#include "filereader.h"


#include <QFileDialog>
#include <QStyle>
#include <QDebug>
#include <QProcess>
#include <QPainter>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QProgressDialog>
#include <QFutureWatcher>
#include "pythonprocess.h"
#include <QDesktopServices>

Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
{

    ui->setupUi(this);


    //initializing variables
    videoWidget =new VideoWidget(this);
    videoWidget->resize(1024,768);
    ui->verticalLayout_2->addWidget(videoWidget);
    //ui->label_2 = videoWidget;
    mediaPlayer = new QMediaPlayer;
    media_playlist = new Playlist();
    msg_box = new MessageBox(this);
    grabber = new VideoFrameGrabber(videoWidget);
    reader = new FileReader();
    reader->readFile();

    //initalizing ui elements
    mediaPlayer->setVolume(50);
    mediaPlayer->setVideoOutput(grabber);
    videoWidget->show();
    this->play_list_viewmodel = new QStringListModel();
    ui->play_list_view->setModel(this->play_list_viewmodel);
    this->mediaPlayer->setPlaylist(media_playlist->getMedia_playlist());
    ui->play_button->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->previous_button->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->next_button->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui->open_button->setIcon(style()->standardIcon(QStyle::SP_FileIcon));
    ui->comboBox->addItem("General Summary");
    ui->comboBox->addItem("Interest Oriented Summary");
    ui->comboBox->addItem("Highlight");
    ui->object_radio_btn->setChecked(true);
    ui->progressBar->setVisible(false);
    ui->cancelButton->setVisible(false);


    //connecting signal and slots
    connect(this,SIGNAL(refresh_playlist()),this,SLOT(on_refresh_playlist_signal_emitted()));
    connect(this,SIGNAL(playing_started()),this,SLOT(on_playing_started()));
    connect(mediaPlayer,&QMediaPlayer::positionChanged,this,&Home::on_media_position_changed);
    connect(mediaPlayer,&QMediaPlayer::durationChanged, this, &Home::on_media_duration_changed);
    connect(ui->slider,&QSlider::sliderMoved,this,&Home::on_media_seek);
    connect (videoWidget,SIGNAL(mousePressed()),this,SLOT(on_mouse_click_on_video()));

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
    params.clear();
    pythonPath = reader->getPythonPath();
    inputVideo =this->mediaPlayer->currentMedia().canonicalUrl().toString();
    if (inputVideo == ""){
        msg_box->showError("No video is selected");
        return;
    }
    QString outputPath = reader->getOutputPath();
    if(ui->comboBox->currentText() == "Highlight"){
        pythonScript = reader->getHighlightScriptPath();
        params <<pythonScript<< inputVideo<<outputPath;
    }else if (ui->comboBox->currentText() == "General Summary"){
        pythonScript = reader->getGeneralPath();
        params << pythonScript << inputVideo;
    }else{
        pythonScript = reader->getOOIPath();
    }
    ui->progressBar->setVisible(true);
    ui->progressBar->setMaximum(0);
    ui->progressBar->setMinimum(0);
    runProcess();
}

void Home::on_mouse_click_on_video()
{
    if(this->is_playing){
        ui->play_button->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        ui->play_button->setText("Play");
        this->mediaPlayer->pause();
        is_playing = false;
    }
}

void Home::handleResults(const QString *results)
{
    qDebug()<<results;
}

void Home::mousePressEvent(QMouseEvent *ev)
{

}

void Home::paintEvent(QPaintEvent *ev)
{

}

void Home::on_capture_btn_clicked()
{
    QImage currentImage = *grabber->currentImage;
    QRect selected = *videoWidget->currentRect;
    if (currentImage.isNull()){
        msg_box->showError("Invalid Image");
        return;
    }
    QImage cropped = currentImage.copy(selected);
    this->ooiPath = "D:/cropped.png";
    cropped.save(ooiPath,0,-1);


}

void Home::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Interest Oriented Summary"){
        ui->groupBox_3->setEnabled(true);
    }else{
        ui->groupBox_3->setEnabled(false);
    }

}

bool Home::runProcess()
{
    ui->gen_sum_btn->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->cancelButton->setVisible(true);
    p = new QProcess();

    p->setReadChannel(QProcess::StandardOutput);
    connect(p,SIGNAL(readyReadStandardOutput()),this,SLOT(readProcess()));
    //connect(p,SIGNAL(readyReadStandardError()),this,SLOT(readError()));
    connect (p,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(processFinished(int,QProcess::ExitStatus)));
    p->start(pythonPath,params);
    return true;
}

void Home::readProcess()
{
    QString output_buffer = p->readAllStandardOutput();
    if(output_buffer.contains('_')){
        QStringList words = output_buffer.split('_');
        if(words[0] == "application"){
            QString phasetype = words[1];
            QString processedSteps = words[2];
            QString all_steps = words[3];
            if(all_steps.toInt()==0){
                ui->progressBar->setRange(0,0);
                ui->progreess_bar_lbl->setText(phasetype+" Processing...");
            }else{
                ui->progressBar->setRange(0,all_steps.toInt());
                ui->progressBar->setValue(processedSteps.toInt());
                ui->progreess_bar_lbl->setText(phasetype);
            }
            qDebug()<<output_buffer;
        }
    }
}

void Home::readError()
{
    //qDebug()<<"Error Occured";
}

void Home::processFinished(int exitcode, QProcess::ExitStatus exitStatus)
{
    ui->progressBar->setVisible(false);
    if(exitStatus == QProcess::NormalExit && exitcode == 0){
        msg_box->showInfo("Video Summarized Successfully");
    }else{
        msg_box->showError("Video Couldnt Summarize see error log");
    }
    ui->gen_sum_btn->setEnabled(true);
    ui->comboBox->setEnabled(true);
    ui->cancelButton->setVisible(false);
    ui->progreess_bar_lbl->setText("");

}

void Home::on_image_radio_btn_clicked()
{
   this->ooiPath = QFileDialog::getOpenFileName(this,
        tr("Open Image as Interest"), "D://", tr("Image Files (*.jpg *.png *.jpeg)"));

}

void Home::on_output_btn_clicked()
{
    QUrl url(reader->getOutputPath());
    QDesktopServices::openUrl(url);
}

void Home::on_cancelButton_clicked()
{
    QMessageBox confirm;
    confirm.setText("Are you sure you want to cancel the process?");
    confirm.setIcon(QMessageBox::Question);
    confirm.addButton(QMessageBox::No);
    confirm.addButton(QMessageBox::Yes);
    int res = confirm.exec();
    if(res == QMessageBox::Yes){
        p->close();
    }
}
