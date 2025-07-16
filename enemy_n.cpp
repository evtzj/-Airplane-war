#include "enemy_n.h"
#include <QDebug>

Enemy_N::Enemy_N() {
    m_Enemy_N.load(ENEMY_N_PATH);
    m_X=0;
    m_Y=0;
    m_Free=true;
    m_Speed = ENEMY_SPEED;
    m_Rect.setWidth(m_Enemy_N.width());
    m_Rect.setHeight(m_Enemy_N.height());
    m_Rect.moveTo(m_X,m_Y);
    m_MaxHealth = ENEMY_HEALTH;
    m_Health = m_MaxHealth;

    m_ShootRecorder = 0; //所有recorder字样的都是用来“调频”。简单来讲，shoot的频率＝游戏帧率*recorder预设值的间隔（config文件的interval）


    for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
        m_Bullets[i].m_Free = true;  //初始默认为“空闲”状态，可以调用
        m_Bullets[i].m_IsEnemyBullet=true;   // 初始化敌机子弹（标记为敌方子弹）
        m_Bullets[i].m_Speed = -ENEMY_BULLET_SPEED;  // 敌机子弹速度
        m_Bullets[i].m_Bullet.load(":/res/bullet_3.png");  // 确保贴图路径正确
    }
}


void Enemy_N::updatePosition() {
    if(!m_Free) {       //不空闲的，也就是在场的敌机才会触发这个效果
        m_Y += m_Speed;
        m_Rect.moveTo(m_X, m_Y);

        if(m_Y >= GAME_HEIGHT + m_Rect.height()) {
            m_Free = true;  //标记回收
        }
    }
    // 更新子弹
    for(auto& bullet : m_Bullets) {
        if(!bullet.m_Free) {
            bullet.updatePosition();
        }
    }
}

void Enemy_N::clearAllBullets() {
    for(int i = 0; i < ENEMY_BULLET_NUM; i++) {
        m_Bullets[i].m_Free = true;  // 强制回收所有子弹
    }
}

void Enemy_N::hit() {
    if(m_Free) return;
    m_Health--;  //敌机hp减少
    if(m_Health <= 0) {
        m_Free = true;
    }
}

void Enemy_N::shoot() {
    if(m_Free) return;
    m_ShootRecorder++;
    if(m_ShootRecorder < ENEMY_SHOOT_INTERVAL) return;
    m_ShootRecorder = 0;//上面的看不懂没关系，意思就是间隔到了就开始触发下面的shoot行为

    for(int i = 0; i < ENEMY_BULLET_NUM; i++) {
        if(m_Bullets[i].m_Free) {
            m_Bullets[i].m_Free = false;
            // 从敌机底部中央发射
            m_Bullets[i].m_X = m_X + m_Rect.width()/2 - m_Bullets[i].m_Rect.width()/2;
            m_Bullets[i].m_Y = m_Y + m_Rect.height();
            break;
        }
    }
}
