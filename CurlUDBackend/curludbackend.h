#ifndef CURLUDBACKEND_H
#define CURLUDBACKEND_H

#include"CurlInterface/curlinterface.h"
#include"CurlUDProgressDialog/curlprogress.h"

#include <QObject>
#include<QUrl>
#include<QFile>
#include<QFileInfo>
#include<QThread>
#include<QMessageBox>

#include<sys/stat.h>
#include<curl/curl.h>
#include<iomanip>


class CurlUDBackend: QObject
{
    Q_OBJECT
public:
    CurlUDBackend();
    virtual ~CurlUDBackend();
signals:
    void transferDetail(QString filename, double totalTrasfer, double currentTransfer, int percantage, int speed, QString source, QString destination);
    void started();
    void stopped();
    void finished();

public slots:
    void applyPressed(QString hostname, QString protocol, QString port, QString username, QString passwd, bool anon, QString source, QString &destination);
    void uploadPressed();
//    void messageSignal(QString);
//    void errorSignal(QString);
    void progressSignal(curl_off_t totalDownload, curl_off_t currentDownload, curl_off_t totalUpload, curl_off_t currentUpload, curl_off_t speed);
    QString unitHandling(long size);
    void fileHandling(QString file);
    void destinationHandler(QString hostname, QString protocol, QString port, QString username,QString source, bool anon);
//    void destinationHandler();

private:
    QString currentTotalSize(curl_off_t total, curl_off_t current);
    int percentage(double total, double current);
    CurlProgress *proDialog;
    QUrl url;
    QString hostname;
    long port;
    QString protocol;
    QString username;
    QString passwd;
    bool anon;
    QString source;
    QUrl destination;
    QFile *file;
    QString filename;
    long fileSize;
    QString fileSizeUnit;
    QFileInfo *fileInfo;
};

#endif // CURLUDBACKEND_H
