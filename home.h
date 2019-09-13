#ifndef HOME_H
#define HOME_H

#include "video.h"

#include <QMainWindow>
#include <QMediaPlayer>
#include <QStringListModel>

#include <QtMultimediaWidgets/qvideowidget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Home; }
QT_END_NAMESPACE

class Home : public QMainWindow
{
    Q_OBJECT

public:
    Home(QWidget *parent = nullptr);
    ~Home();

private slots:
    void on_play_button_clicked();
    void on_refresh_playlist_signal_emitted();
    void on_open_button_clicked();

private:
    Ui::Home *ui;
    QVideoWidget *videoWidget =nullptr;
    QMediaPlayer *mediaPlayer =nullptr;
    bool is_playing = false;
    QList<Video*> *video_list;
    QStringList *play_list;
    QStringListModel *play_list_model;

signals:
    void refresh_playlist();

};
#endif // HOME_H
