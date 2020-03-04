include(../rasterwindow/rasterwindow.pri)

# work-around for QTBUG-13496
CONFIG += no_batch

SOURCES += \
    main.cpp

target.path = ../build-%{CurrentProject:Name}-%{CurrentKit:FileSystemName}-%{CurrentBuild:Name}
INSTALLS += target

DISTFILES +=

RESOURCES +=
