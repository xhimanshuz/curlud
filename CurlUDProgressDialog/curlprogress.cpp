#include "curlprogress.h"

CurlProgress::CurlProgress(QString fileName, QString source, QString destination, QWidget *parent)
    : QDialog(parent)
{
    this->fileName = fileName;
    this->source = source;
    this->destination = destination;

    mainLayout = new QVBoxLayout;
    renderUi();
    this->setLayout(mainLayout);

    timer = new QTimer;
    connect(timer, &QTimer::timeout, [this]{
        this->progressBar->setValue(progressPerc);
    });

    this->resize(500, 150);
}

CurlProgress::~CurlProgress()
{

}

void CurlProgress::renderUi()
{
    fileNameLabel = new QLabel(QString("<b>"+ this->fileName+"</b>"));
    totalCurrentLabel = new QLabel(this->totalCurrentSize);
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(fileNameLabel);
    hbox->addStretch();
    hbox->addWidget(new QLabel("Remaining/Total Size: "));
    hbox->addWidget(totalCurrentLabel);
    mainLayout->addLayout(hbox);

    progressBar = new QProgressBar;
    progressBar->setValue(progressPerc);
    progressBar->setRange(0, 99);
    progressBar->setTextVisible(true);
    mainLayout->addWidget(progressBar);

    speedLabel = new QLabel(speed);
    QHBoxLayout *subHBox = new QHBoxLayout;
    subHBox->addWidget(new QLabel("Speed: "));
    subHBox->addWidget(speedLabel);
    hbox = new QHBoxLayout;
    hbox->addLayout(subHBox);
    hbox->addStretch();
    remainingTimeLabel = new QLabel(remainingTime);
    subHBox = new QHBoxLayout;
    subHBox->addWidget(new QLabel("Remaining Time: "));
    subHBox->addWidget(remainingTimeLabel);
    hbox->addLayout(subHBox);
    mainLayout->addLayout(hbox);

    sourceLineEdit = new QLineEdit(source);
    hbox = new QHBoxLayout;
    hbox->addWidget(new QLabel("Source: "), 1);
    hbox->addWidget(sourceLineEdit, 5);
    mainLayout->addLayout(hbox);

    destinationLineEdit = new QLineEdit(destination);
    destinationFileChanger = new QPushButton("...");
    destinationFileChanger->resize(QSize(destinationFileChanger->size().height(), destinationFileChanger->size().height()));
    hbox = new QHBoxLayout;
    hbox->addWidget(new QLabel("Destination: "), 1);
    hbox->addWidget(destinationLineEdit, 5);
    hbox->addWidget(destinationFileChanger);
    mainLayout->addLayout(hbox);

    pauseButton = new QPushButton("Pause");
    cancelButton = new QPushButton("Cancel");
    connect(cancelButton, &QPushButton::clicked, this, &CurlProgress::terminateCurl);
    closeButton = new QPushButton("Close");
    connect(closeButton, &QPushButton::clicked, [this]{
        this->hide();
    });
    hbox = new QHBoxLayout;
    hbox->addStretch();
    hbox->addWidget(pauseButton);
    hbox->addWidget(cancelButton);
    hbox->addWidget(closeButton);
    mainLayout->addLayout(hbox);
}

void CurlProgress::updateValues(QString totalCurrentSize, double progressPerc, QString speed, QString remainingTime)
{
    totalCurrentLabel->setText(totalCurrentSize);
    this->progressPerc = progressPerc;
    speedLabel->setText(speed);
    remainingTimeLabel->setText(remainingTime);
}

QPushButton *CurlProgress::getPauseButton() const
{
    return pauseButton;
}

QPushButton *CurlProgress::getCancelButton() const
{
    return cancelButton;
}

QProgressBar *CurlProgress::getProgressBar() const
{
    return progressBar;
}
