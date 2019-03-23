#include<QCoreApplication>
#include"curludbackend.h"
#include<QDebug>
#include<unistd.h>

int main(int c, char **v)
{
    QCoreApplication core(c, v);

    CurlUDBackend cb;
    cb.applyPressed("ihimanshu.xyz", "SFTP", "2222", "pi", "466453", false, "/home/gnu/Downloads/ConsoleAct.v2.3.(Portable).7z", "ihimanshu.xyz/home/pi/some.rar");
    cb.uploadPressed();
//    FILE *file = fopen("/home/gnu/Downloads/ConsoleAct.v2.3.(Portable).7z", "r");


    return core.exec();
}
