#ifndef BULLET_H
#define BULLET_H

#include "config.h"
#include <QPixmap>

class Bullet
{
public:
    Bullet();

    void updatePosition();

public:
    QPixmap m_Bullet;  //所有的pixmap类都是拿来“画图”的。加载图片，更新坐标，QPainter那些都是用这个

    int m_X;
    int m_Y;
    int m_Speed;

    bool m_Free;//子弹是否处于空闲状态。子弹的逻辑是“一个固定大小数组，射出屏幕以后变为free状态收回来，然后当需要发射子弹时在数组中找到free的子弹射出去”
    bool m_IsEnemyBullet;//字面意思

    QRect m_Rect;//所有的m_Rect都是边框，作用都是碰撞判定
};

#endif // BULLET_H
