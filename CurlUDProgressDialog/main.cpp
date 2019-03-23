#include "curlprogress.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CurlProgress w("GTA_SAN_ANDREAS.ISO", "https://filehippo.com/3797505be687bec748f6d1a0117f9368/GTA_SAN.iso", "/home/gnu/Downloads/GTA_SAN_ANDREAS.iso");
    w.updateValues("remaiin", 25.5, "speed", "retime");
    w.show();

    return a.exec();
}
