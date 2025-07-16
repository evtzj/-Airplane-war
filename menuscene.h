#ifndef MENUSCENE_H
#define MENUSCENE_H
#include <QMainWindow>
#include"gameview.h"
#include"MainScene.h"
#include"enums.h"
class QPushButton;

class MenuScene : public QMainWindow
{
    Q_OBJECT
public:

    MenuScene(QWidget *parent = nullptr);
    ~MenuScene();


private slots:

    void startSinglePlayer();
    void startCoopMode();
    void startVersusMode();


private :
    void setupMenu();

    QPushButton*btnSingle;
    QPushButton*btnCoop;
    QPushButton*btnVersus;

    GameView*gameView;
    MainScene*mainScene;
};

#endif // MENUSCENE_H
