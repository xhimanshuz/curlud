#include<QApplication>
#include"CurlUDFrontend/Includes/uploadui.h"
#include"CurlUDBackend/curludbackend.h"
#include<QVBoxLayout>

int main(int c, char **v)
{
    QApplication app(c, v);
    app.setWindowIcon(QIcon("://Data/icon.png"));

    UploadUi ui;
    CurlUDBackend cb;
    QObject::connect(&ui, &UploadUi::apply, [&cb, &ui](QString hostname, QString protocol, QString port, QString username, QString passwd, bool anon, QString source, QString destination){
        cb.applyPressed(hostname, protocol, port, username, passwd, anon, source, destination);
        ui.destinationLineEdit->setText(destination);
        ui.renderUi();
    });
    QObject::connect(&ui, &UploadUi::uploadClicked, [&cb]{
        cb.uploadPressed();
    });
    ui.show();

    return app.exec();
}
