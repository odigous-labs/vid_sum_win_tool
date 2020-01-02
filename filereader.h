#ifndef FILEREADER_H
#define FILEREADER_H

#include <QString>



class FileReader
{
public:
    FileReader();
    QString getPythonPath();
    QString getHighlightScriptPath();
    QString getOOIPath();
    QString getGeneralPath();
    QString getOutputPath();
    QStringList *paths;
    void readFile();
};

#endif // FILEREADER_H
