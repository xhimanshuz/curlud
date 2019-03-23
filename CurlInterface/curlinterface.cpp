#include "curlinterface.h"
#include<QDebug>

CurlInterface::CurlInterface(): speed(0)
{

}

void CurlInterface::run()
{
    perform();
}

void CurlInterface::initialize()
{
    curl_global_init(CURL_GLOBAL_ALL);
    handler = curl_easy_init();
    if(!handler)
        emit errorSignal(tr("ERROR: handler %1").arg(curl_easy_strerror(curlCode)));
}

void CurlInterface::setup(QString url, long port, QString userPass, bool isUpload, CurlInterface::protocolEnum pE, FILE *file, long size)
{
//    hostname = ""
    if(isUpload)
    {
        curl_easy_setopt(handler, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(handler, CURLOPT_USERPWD, userPass.toStdString().c_str());
        curl_easy_setopt(handler, CURLOPT_READDATA, file);

        if(pE == CurlInterface::sftp && userPass!= "ANON")
            curl_easy_setopt(handler,CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PASSWORD);
    }
    curl_easy_setopt(handler, CURLOPT_URL, url.toStdString().c_str());
    curl_easy_setopt(handler,CURLOPT_PORT, port);

    curl_easy_setopt(handler, CURLOPT_XFERINFODATA, this);
    curl_easy_setopt(handler, CURLOPT_XFERINFOFUNCTION, CurlInterface::progressCallback);
    curl_easy_setopt(handler, CURLOPT_INFILESIZE_LARGE, (curl_off_t) size);
    curl_easy_setopt(handler, CURLOPT_NOPROGRESS, 0L);
    if(verbose)
        curl_easy_setopt(handler, CURLOPT_VERBOSE, 1L);
}

void CurlInterface::perform()
{
    emit started();

    curlCode = curl_easy_perform(handler);
    emit stopped(curlCode);

    curlCode = curl_easy_getinfo(handler, CURLINFO_SPEED_UPLOAD_T, &speed);
    messageSignal(curl_easy_strerror(curlCode));
    curl_easy_cleanup(handler);
    this->deleteLater();
}

int CurlInterface::progressCallback(void *data, curl_off_t totalDownload, curl_off_t currentDowload, curl_off_t totalUpload, curl_off_t currentUpload)
{
    CurlInterface *cI = reinterpret_cast<CurlInterface*>(data);

//    qDebug()<< totalDownl13dboad << currentDowload << totalUpload << currentUpload;
//    struct speedData *sd = static_cast<struct speedData*>(data);
    emit static_cast<CurlInterface*>(data)->progressSignal(totalDownload, currentDowload, totalUpload, currentUpload, cI->speed); //emmiting non=static sognal
}
