#include "messagebox.h"

MessageBox::MessageBox(QWidget *parent)
{
    this->msg_box = new QMessageBox(parent);
}

MessageBox::~MessageBox()
{
    delete msg_box;
}

void MessageBox::showError(QString error_msg)
{
    msg_box->setIcon(QMessageBox::Critical);
    msg_box->setText(error_msg);
    msg_box->exec();
}

void MessageBox::showInfo(QString info_msg)
{
    msg_box->setIcon(QMessageBox::Information);
    msg_box->setText(info_msg);
    msg_box->exec();
}
