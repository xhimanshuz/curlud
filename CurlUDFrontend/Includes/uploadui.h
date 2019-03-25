#ifndef UPLOADUI_H
#define UPLOADUI_H

#include"interface.h"

#include <QWidget>
#include<QLabel>
#include<QComboBox>
#include<QLineEdit>
#include<QSpinBox>
#include<QGroupBox>
#include<QCheckBox>
#include<QPushButton>
#include<QTableView>
#include<QStandardItem>
#include<QStandardItemModel>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QFormLayout>
#include<QChart>
#include<QChartView>
#include<QtCharts>
#include<QFile>
#include<QFileInfo>
#include<QFileDialog>
#include<QUrl>
#include<QDir>
#include<QPixmap>

class UploadUi:public QWidget, public AbsInterface
{
    Q_OBJECT
public:
    explicit UploadUi(QWidget *parent = nullptr);
//    ~UploadUi();
    void renderUi();
    QLineEdit *destinationLineEdit;
    QVBoxLayout *mainLayout;
signals:
    void uploadClicked();
    void apply(QString hostname, QString protocol, QString port, QString username, QString passwd, bool anon, QString source, QString destination);

private:
    void updateInterface();

    QPushButton *terminateButton;
    QLabel *title;
    QComboBox *protocolComboBox;
    QLineEdit *hostLineEdit;
    QSpinBox *portSpinBox;
    QLineEdit *usernameLineEdit;
    QLineEdit *passwdLineEdit;
    QCheckBox *anonymousCheckBox;
    QCheckBox *showPassCheckBox;
    QPushButton *applyButton;
    QLineEdit *sourceLineEdit;
    QPushButton *uploadButton;
    QPushButton *resetButton;
    QPushButton *defaultDestination;
    QPushButton *sourceButton;
    QTableView *tableView;
    QStandardItemModel *model;
    QChartView *chartView;
    QChart *charts;

    QUrl sourceUrl;
    QUrl destUrl;

};

#endif // UPLOADUI_H
