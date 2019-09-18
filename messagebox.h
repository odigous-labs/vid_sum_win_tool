#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMessageBox>
#include <QWidget>


class MessageBox
{
public:
    MessageBox(QWidget *parent);
    ~MessageBox();
    QMessageBox *msg_box;
    void showError(QString error_mdg);

};

#endif // MESSAGEBOX_H
