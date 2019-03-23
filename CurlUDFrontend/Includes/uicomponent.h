#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include<QWidget>
#include<QLabel>
#include<QIcon>
#include<QPushButton>
#include<QHBoxLayout>

class UiComponent: public QWidget
{
    static UiComponent *instance;

public:
    static UiComponent *getInstance();
    QWidget* header(QString, QWidget*);

protected:
    explicit UiComponent(QWidget *parent = nullptr);
};
#endif // UICOMPONENT_H


