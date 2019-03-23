#include "uicomponent.h"
UiComponent *UiComponent::instance = nullptr;

UiComponent::UiComponent(QWidget *parent): QWidget (parent)
{

}

UiComponent *UiComponent::getInstance()
{
    if(instance == nullptr)
        return new UiComponent;
    return instance;
}

QWidget* UiComponent::header(QString titleStr, QWidget *parent)
{
    QWidget *header = new QWidget;
    header->setStyleSheet("background-color: black");
    QLabel *title = new QLabel(titleStr);
    title->setStyleSheet("color: white");
    QPushButton *close = new QPushButton;
    close->setIcon(QIcon("://Data/closeIcon.png"));
    close->setStyleSheet("border: 0px");
    close->resize(QSize(16, 16));

    connect(close, &QPushButton::clicked, [parent]{
        parent->deleteLater();
        parent->close();
    });
    QHBoxLayout *layout = new QHBoxLayout;
//    layout->setMargin(0);
    layout->addWidget(title);
    layout->addStretch();
    layout->addWidget(close);
    header->setLayout(layout);
    return header;
}
