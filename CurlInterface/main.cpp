#include<QFile>
#include<QCoreApplication>
#include<sys/stat.h>
#include"curlinterface.h"
#include<QObject>
#include<QDebug>
#include<QThread>

int main(int c, char** v)
{
    QCoreApplication a(c, v);

    CurlInterface curl;
    QObject::connect(&curl, &CurlInterface::errorSignal, [](QString signal){
        qDebug()<<"SIGNAL: "<< signal;
    });
    QObject::connect(&curl, &CurlInterface::progressSignal, [](curl_off_t totalDownload, curl_off_t currentDowload, curl_off_t totalUpload, curl_off_t currentUpload){
//        system("clear");
        double per = ((double)currentUpload/(double)totalUpload)*100;
        qDebug()<< totalUpload << currentUpload << totalDownload <<currentDowload << per;
    });
    QObject::connect(&curl, &CurlInterface::messageSignal, [](QString msg){
        qDebug()<<"MSG:"<< msg;
    });

    curl.initialize();
    QFile f("/home/gnu/Documents/Other/google-cloud-sdk.tar.gz");
    if(!f.open(QFile::ReadOnly))
    {
        qDebug()<<"Error: FILE I/O";
        return 1;
    }
    struct stat stats;
    int statInt = fstat(f.handle(), &stats);

    curl.setup("sftp://ihimanshu.xyz/home/pi/google-cloud-sdk.tar.gz", 2222L, "pi:466453", true, CurlInterface::sftp, fdopen(f.handle(), "rb"), stats.st_size);
    curl.run();
    qDebug()<<"Finished";
    return a.exec();
}
