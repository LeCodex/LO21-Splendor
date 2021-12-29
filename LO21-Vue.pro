QT += widgets
QT += gui
QT += xml

SOURCES += \
    main.cpp \
    src/controller.cpp \
    src/DrawPile.cpp \
    src/Bank.cpp \
    src/BaseCard.cpp \
    src/board.cpp \
    src/controller.cpp \
    src/game.cpp \
    src/NobleCard.cpp \
    src/Player.cpp \
    src/ResourceCard.cpp \
    src/view/viewboard.cpp \
    src/view/viewbonus.cpp \
    src/view/viewcard.cpp \
    src/view/viewclickable.cpp \
    src/view/viewcost.cpp \
    src/view/viewdrawpile.cpp \
    src/view/viewgame.cpp \
    src/view/viewnoblecard.cpp \
    src/view/viewplayer.cpp \
    src/view/viewresourcecard.cpp \
    src/view/viewtoken.cpp \

HEADERS += \
    src/controller.h \
    src/Splendor.h \
    src/DrawPile.h \
    src/Bank.h \
    src/BaseCard.h \
    src/board.h \
    src/controller.h \
    src/Deck.h \
    src/game.h \
    src/NobleCard.h \
    src/Player.h \
    src/ResourceCard.h \
    src/view/viewboard.h \
    src/view/viewbonus.h \
    src/view/viewcard.h \
    src/view/viewclickable.h \
    src/view/viewcost.h \
    src/view/viewdrawpile.h \
    src/view/viewgame.h \
    src/view/viewnoblecard.h \
    src/view/viewplayer.h \
    src/view/viewresourcecard.h \
    src/view/viewtoken.h \

RESOURCES += \
    icons.qrc \
    data.qrc
