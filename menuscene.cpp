#include "menuscene.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <QMainWindow>
#include "gameview.h"
MenuScene::MenuScene(QWidget *parent)
    :QMainWindow(parent), gameView(nullptr)
{
    setupMenu();
    setWindowTitle("双人飞机大战 - 模式选择");
    resize(400, 300);
}

MenuScene::~MenuScene(){}

void MenuScene::setupMenu(){
    QWidget*central =new QWidget(this);
    QVBoxLayout*layout=new QVBoxLayout(central);
    btnSingle =new QPushButton("单人模式");
    btnCoop=new QPushButton("双人合作模式");
    btnVersus=new QPushButton("双人对战模式");
    layout->addWidget(btnSingle);
    layout->addWidget(btnCoop);
    layout->addWidget(btnVersus);
    connect(btnSingle,&QPushButton::clicked,this,&MenuScene::startSinglePlayer);
    connect(btnCoop,&QPushButton::clicked,this,&MenuScene::startCoopMode);
    connect(btnVersus,&QPushButton::clicked,this,&MenuScene::startVersusMode);
    setCentralWidget(central);

}
void MenuScene::startSinglePlayer() {
    gameView = new GameView(GameMode::SinglePlayer);
    setCentralWidget(gameView);
}
void MenuScene::startCoopMode() {
    gameView = new GameView(GameMode::Coop);
    setCentralWidget(gameView);
}

void MenuScene::startVersusMode() {
    gameView = new GameView(GameMode::Versus);
    setCentralWidget(gameView);
}
