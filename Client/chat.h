#ifndef CHAT_H
#define CHAT_H

#include <QWidget>

namespace Ui {
class Chat;
}

class Chat : public QWidget
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = nullptr);
    ~Chat();
    QString m_strchatname;
    void  update_le(QString strmsg);
private slots:
    void on_send_PB_clicked();

private:
    Ui::Chat *ui;
};

#endif // CHAT_H
