#ifndef CURLPROGRESS_H
#define CURLPROGRESS_H

#include <QDialog>
#include<QProgressBar>
#include<QLineEdit>
#include<QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QTimer>

class CurlProgress : public QDialog
{
    Q_OBJECT

public:
    CurlProgress(QString fileName, QString source, QString destination, QWidget *parent = nullptr);
    ~CurlProgress();
    void renderUi();
    void updateValues(QString totalCurrentSize, double progressPerc, QString speed, QString remainingTime);

    QTimer *timer;
    QPushButton *getPauseButton() const;
    QPushButton *getCancelButton() const;
    QProgressBar *getProgressBar() const;
signals:
    void terminateCurl();

private:
    QLabel *fileNameLabel;
    QLabel *speedLabel;
    QLabel *totalCurrentLabel;
    QLabel *remainingTimeLabel;
    QProgressBar *progressBar;
    QLineEdit *sourceLineEdit;
    QLineEdit *destinationLineEdit;
    QPushButton *destinationFileChanger;
    QPushButton *destinationButton;
    QPushButton *pauseButton;
    QPushButton *cancelButton;
    QPushButton *closeButton;
    QVBoxLayout *mainLayout;

    QString fileName;
    QString totalCurrentSize;
    QString remainingTime;
    double progressPerc;
    QString speed;
    QString source;
    QString destination;
};

#endif // CURLPROGRESS_H
