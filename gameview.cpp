#include "gameview.h"
#include <QGraphicsScene>
#include <QDebug>
#include "mainscene.h"
GameView::GameView(GameMode mode, QWidget *parent)
    : QGraphicsView(parent)
{
    MainScene* w=nullptr;
    switch (mode) {
    case GameMode::SinglePlayer:
        qDebug() << "启动单人模式";
        w=new MainScene();
        w->show();
        break;
    case GameMode::Coop:
        qDebug() << "启动双人合作模式";
        break;
    case GameMode::Versus:
        qDebug() << "启动双人对战模式";
        break;
    }
}
