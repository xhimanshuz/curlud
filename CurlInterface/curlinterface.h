#ifndef CURLINTERFACE_H
#define CURLINTERFACE_H

#include<curl/curl.h>
#include<unistd.h>
#include<QThread>
#include<QObject>

class CurlInterface:public QThread
{
    Q_OBJECT

    CURL *handler = nullptr;
    CURLcode curlCode;
public:
    CurlInterface();
//    virtual ~CurlInterface();

    enum protocolEnum { sftp = 0, ftp } pE;
    bool verbose = false;
    curl_off_t speed;

    void run();
    void initialize();
    void setup(QString url, long port, QString userPass, bool isUpload, protocolEnum, FILE *file, long size);
    void download();
    void perform();
    void interface();
    static int progressCallback(void *data, curl_off_t totalDownload, curl_off_t currentDowload, curl_off_t totalUpload, curl_off_t currentUpload);
    static int readData(void* ptr, size_t size, size_t nmemb, void* stream);

signals:
    void messageSignal(QString msg);
    void started();
    void stopped(CURLcode errorCode);
    void errorSignal(QString);
    void progressSignal(curl_off_t totalDownload, curl_off_t currentDowload, curl_off_t totalUpload, curl_off_t currentUpload, curl_off_t speed);
};

#endif // CURLINTERFACE_H
