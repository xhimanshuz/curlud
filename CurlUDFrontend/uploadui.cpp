#include "CurlUDFrontend/Includes/uploadui.h"
#include<QDebug>

UploadUi::UploadUi(QWidget *parent): QWidget (parent)
{
    renderUi();
    this->setLayout(mainLayout);

    hostname = new QString;
    protocol = new QString;
    port = new QString;
    username = new QString;
    passwd = new QString;
    source = new QString;
    destination = new QString;
    fileSize = new QString;
    anon = false;
}

void UploadUi::renderUi()
{
    mainLayout = new QVBoxLayout;
    title = new QLabel("<h1>UPLOAD</h1>");
    mainLayout->addWidget(title);

    protocolComboBox = new QComboBox;
    protocolComboBox->addItems(QStringList()<< "FTP"<< "SFTP");
    hostLineEdit = new QLineEdit;
    hostLineEdit->setPlaceholderText(tr("hostname"));
    portSpinBox = new QSpinBox;
    portSpinBox->setValue(21);
    portSpinBox->setRange(1, 9000);
    connect(protocolComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int i){
        this->portSpinBox->setValue(((i)?22:21));
    });

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(protocolComboBox);
    hbox->addWidget(hostLineEdit);
    hbox->addWidget(portSpinBox);
    mainLayout->addLayout(hbox);

    sourceLineEdit = new QLineEdit;
    sourceLineEdit->setPlaceholderText(tr("Select file to upload"));
    this->sourceLineEdit->setReadOnly(true);
    sourceButton = new QPushButton("...");
    connect(sourceButton, &QPushButton::clicked, [this]{
        sourceUrl = QFileDialog::getOpenFileUrl(this, tr("Select File"));
//        qDebug()<< sourceUrl.fileName()<< sourceUrl.port()<< sourceUrl.path()<< sourceUrl.url();
        this->sourceLineEdit->setText(sourceUrl.path());
    });
    hbox = new QHBoxLayout;
    hbox->addWidget(new QLabel("Source"));
    hbox->addWidget(sourceLineEdit);
    hbox->addWidget(sourceButton);
    mainLayout->addLayout(hbox);

    destinationLineEdit = new QLineEdit;
    defaultDestination = new QPushButton("Default");

    hbox = new QHBoxLayout;
    hbox->addWidget(new QLabel("Destination"));
    hbox->addWidget(destinationLineEdit);
    hbox->addWidget(defaultDestination);
    mainLayout->addLayout(hbox);

    usernameLineEdit = new QLineEdit;
    usernameLineEdit->setPlaceholderText("Username");
    passwdLineEdit = new QLineEdit;
    passwdLineEdit->setEchoMode(QLineEdit::Password);
    passwdLineEdit->setPlaceholderText("Password");
    anonymousCheckBox = new QCheckBox("Anonymouse");
    connect(anonymousCheckBox, &QCheckBox::toggled, [this](bool b){
        usernameLineEdit->setEnabled(!b);
        passwdLineEdit->setEnabled(!b);
    });

    showPassCheckBox = new QCheckBox("Show Password");
    connect(showPassCheckBox, &QCheckBox::toggled, [this](bool s){
        passwdLineEdit->setEchoMode((s)?QLineEdit::Normal:QLineEdit::Password);
    });
    applyButton = new QPushButton("Apply");
    connect(applyButton, &QPushButton::clicked, [this]{
        *hostname = hostLineEdit->text();
        *protocol = protocolComboBox->currentText();
        *port = portSpinBox->text();
        *username = usernameLineEdit->text();
        *passwd = passwdLineEdit->text();
        *source = sourceLineEdit->text();
        *destination = destinationLineEdit->text();
        anon = anonymousCheckBox->isChecked();
        emit apply(*hostname, *protocol, *port, *username, *passwd, anon, *source, *destination);
        destinationLineEdit->setText(*destination);
    });

    QVBoxLayout *subVbox = new QVBoxLayout;
    subVbox->addWidget(showPassCheckBox);
    subVbox->addWidget(anonymousCheckBox);
    hbox = new QHBoxLayout;
    hbox->addLayout(subVbox);
    hbox->addStretch();
    hbox->addWidget(applyButton);
    QFormLayout *form = new QFormLayout;
    form->addRow(new QLabel(tr("Username")), usernameLineEdit);
    form->addRow(new QLabel(tr("Password")), passwdLineEdit);
    form->addRow(hbox);
    QGroupBox *gbox = new QGroupBox;
    gbox->setLayout(form);
    mainLayout->addWidget(gbox);

    uploadButton = new QPushButton(tr("Upload"));
    connect(uploadButton, SIGNAL(clicked()), this, SIGNAL(uploadClicked()));
    resetButton = new QPushButton(tr("Reset"));
    connect(resetButton, &QPushButton::clicked, [this]{
        this->hostLineEdit->clear();
        this->usernameLineEdit->clear();
        this->passwdLineEdit->clear();
        anonymousCheckBox->setChecked(false);
        sourceLineEdit->clear();
        destinationLineEdit->clear();
    });
    terminateButton = new QPushButton(tr("Stop"));
    hbox = new QHBoxLayout;
    hbox->addStretch();
    hbox->addWidget(terminateButton);
    hbox->addWidget(resetButton);
    hbox->addWidget(uploadButton);
    mainLayout->addLayout(hbox);

//    model = new QStandardItemModel;
//    tableView = new QTableView;
//    tableView->setModel(model);
//    mainLayout->addWidget(tableView);

//    chartView = new QChartView;
//    mainLayout->addWidget(chartView);

}

void UploadUi::updateInterface()
{


}
