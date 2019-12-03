#ifndef PYTHONPROCESS_H
#define PYTHONPROCESS_H

#include <QThread>

class PythonProcess : public QThread
{
    Q_OBJECT
public:
    QString *pythonPath=nullptr;
    QStringList *params=nullptr;
    PythonProcess(QString *path, QStringList *params);
    QString *result;
    void run() override;
signals:
    void resultReady(const QString *s);
};

#endif // PYTHONPROCESS_H
