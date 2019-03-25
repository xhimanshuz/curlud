#include "curludbackend.h"

CurlUDBackend::CurlUDBackend(): inProcess(false)
{

}

CurlUDBackend::~CurlUDBackend()
{

}

void CurlUDBackend::applyPressed(QString hostname, QString protocol, QString port, QString username, QString passwd, bool anon, QString source, QString &destination)
{
    this->hostname = hostname;
    this->protocol = protocol;
    this->port = port.toLong();
    this->username = username;
    destinationHandler(hostname, protocol, port, username, source, anon);
    destination = this->destination.toString();
    this->passwd = passwd;
    this->source = source;
    this->anon = anon;
}

void CurlUDBackend::uploadPressed()
{
    if(!inProcess)
    {
    fileHandling(source);

    CurlInterface *curl = new CurlInterface;
//    connect(&curl, &CurlInterface::start, this, &CurlUDBackend::started);
    connect(curl, &CurlInterface::progressSignal, [this](curl_off_t totalDownload, curl_off_t currentDowload, curl_off_t totalUpload, curl_off_t currentUpload, curl_off_t speed){
        this->progressSignal(totalDownload, currentDowload, totalUpload, currentUpload, speed);
    });
    curl->initialize();
    curl->setup(destination.toString(), port, QString(username+":"+passwd), true, CurlInterface::sftp, fdopen(file->handle(), "rb"), fileSize);
    proDialog = new CurlProgress(destination.fileName(), source, destination.toString());
    curl->start();
    proDialog->show();
    proDialog->timer->start(100);

    connect(curl, &CurlInterface::stopped, [this](CURLcode errorCode){
        QString msg = curl_easy_strerror(errorCode);
        if(errorCode != CURLE_OK)
        {
            QMessageBox msgbox;
            msgbox.setText(QString("Curl Error: "+ msg));
            msgbox.exec();
            return;
        }
        this->proDialog->getProgressBar()->setValue(99);
        this->proDialog->getCancelButton()->setEnabled(false);
        this->proDialog->getPauseButton()->setEnabled(false);
    });
    connect(proDialog, &CurlProgress::terminateCurl, curl, &CurlInterface::terminate);
    inProcess = true;
    }
    else
    {
        proDialog->show();
    }
}

void CurlUDBackend::progressSignal(curl_off_t totalDownload, curl_off_t currentDownload, curl_off_t totalUpload, curl_off_t currentUpload, curl_off_t speed)
{
    proDialog->updateValues(currentTotalSize(totalUpload, currentUpload), percentage(totalUpload, currentUpload), this->unitHandling(speed), "time");
}

// Adding Memory unit (bytes, KB, MB, GB) according to size to Size of file
QString CurlUDBackend::unitHandling(long size)
{
    if(size>1073741824)
        return QString(QString::number(size/1073741824.0, 'f', 2)+" GB");
    if(size>1048576)
        return QString(QString::number(size/1048576.0, 'f', 2)+" MB");
    if(size>1024)
        return QString(QString::number(size/1024.0, 'f', 2)+" KB");
    else
        return QString(QString::number(size)+ " bytes");
}

void CurlUDBackend::fileHandling(QString f)
{
//    qDebug()<< Q_FUNC_INFO;
    file = new QFile(f);
    if(!file->open(QFile::ReadOnly))
    {
        return;
    }
    fileInfo = new QFileInfo(*file);
    filename = file->fileName();

    struct stat fileStat;
    fstat(file->handle(), &fileStat);
    fileSize = fileStat.st_size;
}

void CurlUDBackend::destinationHandler(QString hostname, QString protocol, QString port, QString username, QString source, bool anon)
{
    this->destination.setScheme(protocol);
    this->destination.setHost(hostname);
    this->destination.setPort(port.toInt());
    ((!anon)?this->destination.setPath("/home/"+username+"/"):this->destination.setPath("/"));
    this->destination.setPath(this->destination.path()+QFileInfo(source).fileName());
}

QString CurlUDBackend::currentTotalSize(curl_off_t total, curl_off_t current)
{
    return QString(unitHandling(long(total)) +"/" +unitHandling(long(current)));
}

int CurlUDBackend::percentage(double total, double current)
{
    if(current == 0)
    {
        return 0;
    }
    return  int((current/total)*100);
}
