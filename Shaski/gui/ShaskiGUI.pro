QT       += widgets
CONFIG   += c++17
TEMPLATE = app
TARGET   = shaski_gui

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    BoardWidget.cpp \
    ../sources/Game.cpp \
    ../sources/Board.cpp \
    ../sources/Player.cpp

HEADERS += \
    MainWindow.hpp \
    BoardWidget.hpp \
    ../headers/Game.hpp \
    ../headers/Board.hpp \
    ../headers/Player.hpp

