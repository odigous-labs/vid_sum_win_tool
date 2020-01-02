#include "filereader.h"
#include "messagebox.h"

#include <QFile>
#include <QTextStream>

FileReader::FileReader()
{
    paths = new QStringList();
}


QString FileReader::getPythonPath()
{
    return paths->at(0);
}

QString FileReader::getHighlightScriptPath()
{
    return paths->at(3);
}

QString FileReader::getOOIPath()
{
    return paths->at(2);
}

QString FileReader::getGeneralPath()
{
    return paths->at(1);
}

QString FileReader::getOutputPath()
{
    return paths->at(4);
}

void FileReader::readFile()
{

    QFile file("config.txt");
    QString line;
    if(!file.open(QIODevice::ReadOnly)) {
        MessageBox msgBox(0);
        msgBox.showError("Cannot Open Configuration File");
    }

    QTextStream in(&file);
    int counter = 0;
    while(!in.atEnd()) {
       paths->insert(counter,in.readLine());
       counter = counter +1;
    }
    file.close();
}


