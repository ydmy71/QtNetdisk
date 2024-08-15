#ifndef FILE_H
#define FILE_H

#include <QWidget>
#include"protocol.h"
#include<QListWidgetItem>
#include"sharefile.h"
namespace Ui {
class File;
}

class File : public QWidget
{
    Q_OBJECT

public:
    explicit File(QWidget *parent = nullptr);
    ~File();
    QString m_strcurpath;
    QString m_userpath;
    void flushfile();
    QList<FileInfo*> m_filelist;
    QString m_strmvfilename;
    QString m_strmvpath;
    QString m_uploadpath;
    bool m_bupload;
    QString m_strsharefile;
    void uploadfile();
    ShareFile* getsharefile();
    void updateFilelist(QList<FileInfo*>pfilelist);
private slots:
    void on_mkdir_PB_clicked();

    void on_delfile_PB_clicked();

    void on_deletefile_PB_clicked();

    void on_delfile_PB_2_clicked();

    void on_rename_PB_clicked();

    void on_listWidget_file_itemDoubleClicked(QListWidgetItem *item);

    void on_return_PB_clicked();

    void on_movefile_PB_clicked();

    void on_upload_PB_clicked();

    void on_sharefile_PB_clicked();
    
private:
    Ui::File *ui;
    ShareFile *m_pShareFile;
};

#endif // FILE_H
