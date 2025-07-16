#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include "enums.h"

class GameView : public QGraphicsView {
    Q_OBJECT

public:
    GameView(GameMode mode, QWidget *parent = nullptr);
};

#endif // GAMEVIEW_H
