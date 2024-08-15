#ifndef INDEX_H
#define INDEX_H

#include <QWidget>
#include"file.h"
#include"friend.h"
namespace Ui {
class Index;
}

class Index : public QWidget
{
    Q_OBJECT
public:
    explicit Index(QWidget *parent = nullptr);
    ~Index();
    Friend* getFriend();
    File* getFile();
    static Index& getinstance();
private slots:
    void on_friend_push_clicked();

    void on_file_push_clicked();

private:
    Ui::Index *ui;
};

#endif // INDEX_H
