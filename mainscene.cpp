#include "mainscene.h"
#include "config.h"


MainScene::MainScene(QWidget *parent): QWidget(parent)
{
    initScene();

    playGame();

    setFocus(); // 让场景保持键盘焦点
    setFocusPolicy(Qt::StrongFocus);//不用管，优化移动

    m_keyPressed[Qt::Key_W] = false;
    m_keyPressed[Qt::Key_S] = false;
    m_keyPressed[Qt::Key_A] = false;
    m_keyPressed[Qt::Key_D] = false;
    m_keyPressed[Qt::Key_Shift] = false;
}

MainScene::~MainScene() {}

void MainScene::initScene()
{
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_ICON));

    m_Timer.setInterval(GAME_RATE);
    m_recorder=0;

    m_audioOutput = new QAudioOutput(this);
    m_audioOutput->setVolume(0.5);  // 音量范围 0.0~1.0

    m_bgmPlayer = new QMediaPlayer(this);
    m_bgmPlayer->setAudioOutput(m_audioOutput);
    m_bgmPlayer->setSource(QUrl("qrc:/res/bg.wav")); // 使用资源文件路径
    m_bgmPlayer->setLoops(QMediaPlayer::Infinite);  // 无限循环

    // 初始化爆炸音效
    m_explosionOutput = new QAudioOutput(this);
    m_explosionOutput->setVolume(0.8);  // 音量比BGM稍大

    m_explosionPlayer = new QMediaPlayer(this);
    m_explosionPlayer->setAudioOutput(m_explosionOutput);
    m_explosionPlayer->setSource(QUrl("qrc:/res/bomb.wav"));
}

void MainScene::playGame()
{
    m_Timer.start();

    m_bgmPlayer->play();

    connect(&m_Timer,&QTimer::timeout,[=](){   //每过一帧，就会开始检查刷新游戏状态
        enemyToScene();
        collisionDetection();
        updatePosition();
        update();
        m_Player.updateInvincibility();
    });
}

void MainScene::updatePosition()  //字面意思
{
    int dx = 0, dy = 0;
    if(m_keyPressed.value(Qt::Key_W, false)) dy -= 1;
    if(m_keyPressed.value(Qt::Key_S, false)) dy += 1;
    if(m_keyPressed.value(Qt::Key_A, false)) dx -= 1;
    if(m_keyPressed.value(Qt::Key_D, false)) dx += 1;

    if(dx != 0 || dy != 0) {
        m_Player.move(dx, dy);
    }

    m_Map.mapPosition();
    m_Player.shoot();

    for(int i=0;i<BULLET_NUM;i++)
    {
        if(m_Player.m_Bullets[i].m_Free==false)
        {
            m_Player.m_Bullets[i].updatePosition();
        }
    }//更新子弹位置

    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free==false)
        {
            m_enemys[i].shoot();
            m_enemys[i].updatePosition();  // 这会更新敌机及其子弹位置

        }
    }

    for(int i=0;i<BOMB_NUM;i++)//爆炸特效相关，不用管
    {
        if(m_Bombs[i].m_Free==false)
        {
            m_Bombs[i].updateInfo();
        }
    }


}

void MainScene::enemyToScene()//控制敌机出场的，不用管
{
    m_recorder++;
    if(m_recorder<ENEMY_INTERVAL){return;}
    else
    {
        m_recorder=0;
        for(int i=0;i<ENEMY_NUM;i++)
        {
            if(m_enemys[i].m_Free==true)
            {
                m_enemys[i].m_Free=false;
                m_enemys[i].m_X=rand()%(GAME_WIDTH-m_enemys[i].m_Rect.width());
                m_enemys[i].m_Y=-m_enemys[i].m_Rect.height();
                m_enemys[i].m_Health = m_enemys[i].m_MaxHealth;
                break;
            }
        }
    }
}

void MainScene::collisionDetection()//碰撞相关
{
    //第一部分，敌机受击相关
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free)
        {
            continue;
        }
        for(int j=0;j<BULLET_NUM;j++)
        {
            if(m_Player.m_Bullets[j].m_Free){continue;}
            else
            {
                if(m_enemys[i].m_Rect.intersects(m_Player.m_Bullets[j].m_Rect))
                {
                    m_Player.m_Bullets[j].m_Free=true;

                    m_enemys[i].hit();  // 敌机受击

                    if(m_enemys[i].m_Health<=0)
                    {
                        m_enemys[i].clearAllBullets();
                        for(int k = 0; k < BOMB_NUM; k++)
                        {
                            if(m_Bombs[k].m_Free)
                            {
                                m_Bombs[k].m_Free = false;
                                m_Bombs[k].m_X = m_enemys[i].m_X;
                                m_Bombs[k].m_Y = m_enemys[i].m_Y;
                                m_explosionPlayer->play();
                                break;
                            }
                        }
                    }


                }
            }
        }
    }
    //第二部分，玩家受击相关
    for(auto& enemy : m_enemys) {
        if(enemy.m_Free) continue;

        for(auto& bullet : enemy.m_Bullets) {
            if(bullet.m_Free || !bullet.m_IsEnemyBullet) continue;

            if(m_Player.m_Rect.intersects(bullet.m_Rect)) {
                bullet.m_Free = true;  // 回收子弹
                m_Player.onHit();      // 触发受击逻辑

                // 游戏结束检查
                if(m_Player.m_Lives < 0) {
                    gameOver();
                }
                break;
            }
        }
    }
}

void MainScene::gameOver() {   //这个是你需要写的，上面实在live<0时触发gameover
    ;
}


void MainScene::paintEvent(QPaintEvent *)//painter控制所有绘图事件
{
    QPainter painter(this);

    painter.drawPixmap(0,m_Map.m_map1_posY,m_Map.m_map1);
    painter.drawPixmap(0,m_Map.m_map2_posY,m_Map.m_map2);

    painter.drawPixmap(m_Player.m_X,m_Player.m_Y,m_Player.m_Plane);

    for(int i=0;i<BULLET_NUM;i++)
    {
        if(m_Player.m_Bullets[i].m_Free==false)
        {
            painter.drawPixmap(m_Player.m_Bullets[i].m_X,m_Player.m_Bullets[i].m_Y,m_Player.m_Bullets[i].m_Bullet);
        }
    }

    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free==false)
        {
            painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].m_Enemy_N);
        }
    }

    for(int i=0;i<BOMB_NUM;i++)
    {
        if(m_Bombs[i].m_Free==false)
        {
            painter.drawPixmap(m_Bombs[i].m_X,m_Bombs[i].m_Y,m_Bombs[i].m_pixArr[m_Bombs[i].m_index]);
        }
    }

    for(auto& enemy : m_enemys) {
        if(enemy.m_Free) continue;

        for(auto& bullet : enemy.m_Bullets) {
            if(!bullet.m_Free) {
                painter.drawPixmap(bullet.m_X, bullet.m_Y, bullet.m_Bullet);
            }
        }
    }

    if (!m_Player.m_IsInvincible || (QDateTime::currentMSecsSinceEpoch() % 200 < 100)) {
        painter.drawPixmap(m_Player.m_X, m_Player.m_Y, m_Player.m_Plane);
    }
}


void MainScene::keyPressEvent(QKeyEvent *event) {
    if (m_keyPressed.contains(event->key())) {
        m_keyPressed[event->key()] = true;
        if(event->key() == Qt::Key_Shift) {
            m_Player.m_isSlow = true;
        }
    }
}

void MainScene::keyReleaseEvent(QKeyEvent *event) {
    if (m_keyPressed.contains(event->key())) {
        m_keyPressed[event->key()] = false;
        if(event->key() == Qt::Key_Shift) {
            m_Player.m_isSlow = false;
        }
    }
}

Player_Plane *MainScene::getPlayer()
{
    return &m_Player;
}
