#include "player_plane.h"

Player_Plane::Player_Plane() :   //初始化列表，c++语法，你就当成是变量初始化的特殊方式
    m_Lives(PLAYER_LIFE),
    m_IsInvincible(false),
    m_normalSpeed(3),
    m_slowSpeed(1),
    m_isSlow(false)
{
    m_Plane.load(":/res/character1.png");  // 确保使用正确的路径宏

    // 初始化位置
    m_X = GAME_WIDTH * 0.5 - m_Plane.width() * 0.5;
    m_Y = GAME_HEIGHT - m_Plane.height();

    // 初始化碰撞矩形
    m_Rect.setWidth(m_Plane.width());
    m_Rect.setHeight(m_Plane.height());
    m_Rect.moveTo(m_X, m_Y);

    // 初始化计时器
}

void Player_Plane::onHit() {
    if (m_IsInvincible) return;
    m_Lives--;
    m_IsInvincible = true;
    m_InvincibleEndTime = QDateTime::currentMSecsSinceEpoch() + 2000;  // 2秒后结束无敌
    respawn();
}

void Player_Plane::respawn() {
    m_X = GAME_WIDTH / 2 - m_Plane.width() / 2;
    m_Y = GAME_HEIGHT - m_Plane.height();
    m_Rect.moveTo(m_X, m_Y);

    // 激活无敌状态（持续2秒）
    m_IsInvincible = true;
    m_InvincibleEndTime = QDateTime::currentMSecsSinceEpoch() + 2000;
}

void Player_Plane::updateInvincibility()
{
    if (m_IsInvincible && QDateTime::currentMSecsSinceEpoch() >= m_InvincibleEndTime) {
        m_IsInvincible = false;
    }
}

void Player_Plane::shoot()
{
    if(m_recoder < 0) m_recoder = 0;//安全判断
    m_recoder++;
    if(m_recoder<BULLET_INTERVAL){return;}
    m_recoder=0;
    for(int i=0;i<BULLET_NUM;i++)
    {
        for(int i = 0; i < BULLET_NUM; i++)
        {
            if(m_Bullets[i].m_Free)
            {
                m_Bullets[i].m_Free = false;
                m_Bullets[i].m_X = m_X + m_Rect.width()/2 - m_Bullets[i].m_Bullet.width()/2; // 居中发射
                m_Bullets[i].m_Y = m_Y;
                break;  // 找到一颗可用子弹就退出循环
            }
        }
    }
}

void Player_Plane::setPosition(int x, int y)
{
    m_X=x;
    m_Y=y;
    m_Rect.moveTo(m_X,m_Y);
}

void Player_Plane::move(int dx, int dy)
{
    qreal speed = m_isSlow ? m_slowSpeed : m_normalSpeed;//三目运算符
    setPosition(m_X + dx * speed, m_Y + dy * speed);

    // 简单边界检查
    if(m_X < 0) setPosition(0,m_Y);
    if(m_Y < 0) setPosition(m_X,0);
    if(m_X > GAME_WIDTH-m_Rect.width())
        setPosition(GAME_WIDTH-m_Rect.width(),m_Y);
    if(m_Y > GAME_HEIGHT-m_Rect.height())
        setPosition(m_X,GAME_HEIGHT-m_Rect.height());
}



QPoint Player_Plane::getPosition() const {
    return QPoint(m_X, m_Y);
}
