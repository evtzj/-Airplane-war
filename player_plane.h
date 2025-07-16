#ifndef PLAYER_PLANE_H
#define PLAYER_PLANE_H

#include <QPixmap>
#include <QRect>
#include <QKeyEvent>
#include <QPoint>
#include <QTimer>
#include "Bullet.h"
#include "config.h"
#include <qdatetime.h>


class Player_Plane {
public:
    Player_Plane();

    void shoot();

    void setPosition(int x,int y);

    QPoint getPosition() const; //我忘了这个干啥的，估计就是字面意思把

    void move(int dx, int dy);      // 相对移动

    Bullet m_Bullets[BULLET_NUM];

    int m_recoder;

    void onHit(); //受击

    void respawn();      // 复活方法

    int m_Lives;  // 当前残机数
    bool m_IsInvincible; // 无敌状态（复活保护）

    void updateInvincibility();  //确认是否处于无敌状态

    qint64 m_InvincibleEndTime = 0;//特殊的计时器，反正就是拿来计算无敌时间的


public:
    QPixmap m_Plane;  //图像

    int m_X;
    int m_Y;

    int m_normalSpeed = 3;  // 正常速度
    int m_slowSpeed = 1;    // 减速速度
    bool m_isSlow = false;  // 减速状态

    QRect m_Rect;//边框
};

#endif // PLAYER_PLANE_H
