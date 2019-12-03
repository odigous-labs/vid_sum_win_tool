#ifndef HOME_H
#define HOME_H

#include "playlist.h"
#include "video.h"
#include "messagebox.h"
#include "filereader.h"

#include <QMainWindow>
#include <QMediaPlayer>
#include <QStringListModel>

//#include <QtMultimediaWidgets/qvideowidget.h>
#include "videowidget.h"
#include "videoframegrabber.h"


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
    void on_gen_sum_btn_clicked();
    void on_mouse_click_on_video();
    void handleResults(const QString *results);
    void on_capture_btn_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::Home *ui;
    VideoWidget *videoWidget =nullptr;
    QMediaPlayer *mediaPlayer =nullptr;
    bool is_playing = false;
    MessageBox *msg_box = nullptr;
    QStringListModel *play_list_viewmodel;
    Playlist *media_playlist;
    VideoFrameGrabber *grabber;
    FileReader *reader = nullptr;
    QString *pythonPath = nullptr;
protected:
    void mousePressEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent *ev);

signals:
    void refresh_playlist();
    void playing_started();

};
#endif // HOME_H
