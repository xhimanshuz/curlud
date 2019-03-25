QT += widgets charts

HEADERS += \
    CurlUDFrontend/Includes/uploadui.h \
    CurlUDBackend/curludbackend.h \
    CurlInterface/curlinterface.h \
    CurlUDProgressDialog/curlprogress.h

SOURCES += \
    main.cpp \
    CurlUDFrontend/uploadui.cpp \
    CurlUDBackend/curludbackend.cpp \
    CurlInterface/curlinterface.cpp \
    CurlUDProgressDialog/curlprogress.cpp


RESOURCES += \
    CurlUDFrontend/res.qrc

DESTDIR = $$PWD/../CurlUD_Application/

LIBS += -lcurl

