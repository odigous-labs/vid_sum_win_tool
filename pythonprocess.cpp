#include "pythonprocess.h"
#include <QProcess>

PythonProcess::PythonProcess(QString *path, QStringList *params)
{
    this->pythonPath = path;
    this->params = params;
}

void PythonProcess::run()
{

    QProcess p;
    p.start(*pythonPath,*params);
    p.waitForFinished(-1);
    while( p.canReadLine()){
        *result = *result + p.readLine();
    }
    QString p_stdout = p.readAll();
    QString p_stderr = p.readAllStandardError();
    if(!p_stderr.isEmpty()){
        *result = *result + p_stdout;
      *result = *result + p_stderr;
    }
    emit resultReady(result);
}
