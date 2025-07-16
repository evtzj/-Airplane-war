#ifndef BOMB_H
#define BOMB_H

#include "config.h"
#include <QPixmap>
#include <QVector>

class Bomb  //BOMB类，用于表示爆炸的效果，是一个“动图”。这个你们可以不用管，我自己已经做完了
{
public:
    Bomb();
    void updateInfo();
public:
    QVector<QPixmap> m_pixArr;

    int m_X;
    int m_Y;
    bool m_Free;//爆炸状态
    int m_Recorder;
    int m_index;
};

#endif // BOMB_H
