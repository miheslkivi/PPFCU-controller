HEADERS       = client.h \
    dgconst.h
SOURCES       = client.cpp \
                main.cpp \
    dgconst.cpp
QT           += network
QT           += network widgets
QT           += widgets

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/ipc/localfortuneclient
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS 
#localfortuneclient.pro
#sources.path = $$[QT_INSTALL_EXAMPLES]/ipc/localfortuneclient
INSTALLS += target sources

