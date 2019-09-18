#include "playlist.h"

Playlist::Playlist()
{
    this->video_list = new QList<Video*>;
    this->media_playlist = new QMediaPlaylist();
    this->string_list = new QStringList();
}

Playlist::~Playlist()
{
    delete video_list;
    delete media_playlist;
}

QMediaPlaylist *Playlist::getMedia_playlist() const
{
    return media_playlist;
}

//this will check whether the given video already exist in the playlist
bool Playlist::isVideoExist(Video *video)
{
    foreach(Video *video_in_list, *video_list){
        if(video_in_list->getVideoName() == video->getVideoName()){
            return true;
        }
    }
    return false;
}




QStringList* Playlist::getPlayList()
{
    this->string_list->clear();
    foreach (Video *video, *video_list) {
        this->string_list->append(video->getVideoName());
    }
    return string_list;
}

void Playlist::addVideo(Video* video)
{
    if(isVideoExist(video)){
        throw  std::runtime_error("Video already exists in the playlist");
    }else{
        this->video_list->append(video);
        QMediaContent *media_content = new QMediaContent(*video->getUrl());
        this->media_playlist->addMedia(*media_content);
    }

}

void Playlist::next()
{
    this->media_playlist->next();
}

void Playlist::previous()
{
    this->media_playlist->previous();
}


