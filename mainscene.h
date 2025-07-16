#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QIcon>
#include <QTimer>
#include <QPainter>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QAudioOutput>

#include "map.h"
#include "player_plane.h"
#include "enemy_n.h"
#include "bomb.h"

class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //场景初始化

    void initScene();

    void playGame();

    void updatePosition();

    void paintEvent(QPaintEvent*) override;

    void keyPressEvent(QKeyEvent *event) override;   //WASD控制移动，shift相关的，不用管

    void keyReleaseEvent(QKeyEvent *event) override;

    void enemyToScene();

    void collisionDetection();  //碰撞相关行为

    void gameOver();  //这个是你要写的！

    Enemy_N m_enemys[ENEMY_NUM];

    int m_recorder;

    Player_Plane* getPlayer();

    QTimer m_Timer;

    Player_Plane m_Player;

    Map m_Map;

    Bomb m_Bombs[BOMB_NUM];

    QMediaPlayer *m_bgmPlayer;  // 背景音乐播放器
    QAudioOutput *m_audioOutput; // 音频输出控制

    QMediaPlayer *m_explosionPlayer;  // 爆炸音效播放器
    QAudioOutput *m_explosionOutput;

    QHash<int, bool> m_keyPressed;//不用管

};
#endif // MAINSCENE_H
