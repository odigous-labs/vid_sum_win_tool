#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "video.h"

#include <QList>
#include <QMediaPlaylist>



class Playlist
{
public:
    Playlist();
    ~Playlist();
    QList<Video*> *video_list = nullptr;
    QMediaPlaylist *media_playlist = nullptr;
    QStringList *string_list = nullptr;
    QStringList* getPlayList();
    void addVideo(Video* video);
    void next();
    void previous();
    QString currentMediaURL();
    QMediaPlaylist *getMedia_playlist() const;
private:
    bool isVideoExist(Video* video);
};

#endif // PLAYLIST_H
