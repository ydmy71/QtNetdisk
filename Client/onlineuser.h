#ifndef ONLINEUSER_H
#define ONLINEUSER_H

#include <QListWidgetItem>
#include <QWidget>

namespace Ui {
class Onlineuser;
}

class Onlineuser : public QWidget
{
    Q_OBJECT

public:
    explicit Onlineuser(QWidget *parent = nullptr);
    ~Onlineuser();
    void update_onlineuser_WigdetList(QStringList userlist);


private slots:
    void on_onlineuser_LW_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::Onlineuser *ui;
};

#endif // ONLINEUSER_H
