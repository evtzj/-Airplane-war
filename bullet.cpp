#include "bullet.h"

Bullet::Bullet() {
    m_Bullet.load(BULLET_PATH);//加载图片

    m_Free=false;
    m_Speed=BULLET_SPEED;

    m_Rect.setWidth(m_Bullet.width());
    m_Rect.setHeight(m_Bullet.height());
    m_Rect.moveTo(m_X,m_Y);
}

void Bullet::updatePosition()
{
    if(m_Free){return;}
    else
    {
        m_Y-=m_Speed;   //-=speed意思是往上移动，玩家的子弹往上移动。而敌人的子弹在enemy那里速度加了个负号！！！
        m_Rect.moveTo(m_X,m_Y);
    }

    if(m_Y<=-m_Rect.height()){m_Free=true;}
}
