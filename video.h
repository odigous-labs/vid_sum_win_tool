#ifndef VIDEO_H
#define VIDEO_H

#include <QUrl>



class Video
{
public:
    Video(QString video_file_path);
    ~Video();
    QString getVideoName();
    QUrl *getUrl() const;

private:
    QUrl *url=nullptr;


};

#endif // VIDEO_H
