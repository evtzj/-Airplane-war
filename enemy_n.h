#ifndef ENEMY_N_H
#define ENEMY_N_H

#include <QPixmap>
#include "config.h"
#include "bullet.h"

class Enemy_N
{
public:
    Enemy_N();

    void updatePosition();
public:
    QPixmap m_Enemy_N;
    int m_X;
    int m_Y;
    int m_Health;      // 当前血量
    int m_MaxHealth;   // 初始血量

    QRect m_Rect;

    bool m_Free;//确保敌机是不是在场上，跟子弹的逻辑一样

    int m_Speed;

    void hit();//受击行为

    void shoot();//设计行为

    Bullet m_Bullets[ENEMY_BULLET_NUM];  // 敌机子弹数组，这里面子弹初始化会带上“enemybullet”判定

    int m_ShootRecorder;  // 发射间隔计数器
    void clearAllBullets(); //默认敌机被击杀会清除他发射的所有子弹

};

#endif // ENEMY_N_H
