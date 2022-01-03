QT += widgets
QT += gui
QT += xml

SOURCES += \
    main.cpp \
    src/CitiesCard.cpp \
    src/CitiesGame.cpp \
    src/CitiesPlayer.cpp \
    src/CitiesQtModel.cpp \
    src/View.cpp \
    src/DrawPile.cpp \
    src/Bank.cpp \
    src/BaseCard.cpp \
    src/board.cpp \
    src/game.cpp \
    src/NobleCard.cpp \
    src/Player.cpp \
    src/ResourceCard.cpp \
    src/qtcontroller.cpp \
    src/view/viewboard.cpp \
    src/view/viewbonus.cpp \
    src/view/viewcard.cpp \
    src/view/viewcitiesboard.cpp \
    src/view/viewcitiescard.cpp \
    src/view/viewcitiesgame.cpp \
    src/view/viewclickable.cpp \
    src/view/viewcost.cpp \
    src/view/viewdrawpile.cpp \
    src/view/viewgame.cpp \
    src/view/viewnoblecard.cpp \
    src/view/viewplayer.cpp \
    src/view/viewresourcecard.cpp \
    src/view/viewtoken.cpp \
    src/qtmodel.cpp \

HEADERS += \
    src/rules.h \
    src/View.h \
    src/model.h \
    src/Splendor.h \
    src/DrawPile.h \
    src/Bank.h \
    src/BaseCard.h \
    src/board.h \
    src/Deck.h \
    src/game.h \
    src/NobleCard.h \
    src/Player.h \
    src/ResourceCard.h \
    src/qtcontroller.h \
    src/view/viewboard.h \
    src/view/viewbonus.h \
    src/view/viewcard.h \
    src/view/viewcitiesboard.h \
    src/view/viewcitiescard.h \
    src/view/viewcitiesgame.h \
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
    data.qrc \
