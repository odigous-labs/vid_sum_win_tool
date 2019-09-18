#ifndef HOME_H
#define HOME_H

#include "playlist.h"
#include "video.h"
#include "messagebox.h"

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
    void on_next_button_clicked();
    void on_previous_button_clicked();
    void on_media_changed(int status);
    void on_playing_started();
    void on_media_position_changed(qint64 progress);
    void on_media_duration_changed(qint64 duration);
    void on_media_seek(int position);

private:
    Ui::Home *ui;
    QVideoWidget *videoWidget =nullptr;
    QMediaPlayer *mediaPlayer =nullptr;
    bool is_playing = false;
    MessageBox *msg_box = nullptr;
    QStringListModel *play_list_viewmodel;
    Playlist *media_playlist;


signals:
    void refresh_playlist();\
    void playing_started();

};
#endif // HOME_H
