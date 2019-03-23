#ifndef INTERFACE_H
#define INTERFACE_H

class QString;

class AbsInterface
{
protected:
    QString *protocol;
    QString *hostname;
    QString *port;
    QString *username;
    QString *passwd;
    QString *source;
    QString *destination;
    QString *fileSize;
    bool anon;

public:
    virtual void renderUi() = 0;
};

#endif // INTERFACE_H
