#include "video.h"

#include <QFile>
#include <QFileInfo>

Video::Video(QString video_file_path)
{
    this->url = new QUrl(video_file_path);

}

Video::~Video()
{

}

QString Video::getVideoName()
{
    QFile f(this->url->url());
    QFileInfo file_info(f.fileName());
    return file_info.fileName();

}

QUrl *Video::getUrl() const
{
    return url;
}
