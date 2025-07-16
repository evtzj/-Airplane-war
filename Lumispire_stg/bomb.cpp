#include "bomb.h"

Bomb::Bomb() {
    m_Free = true;
    m_Recorder = 0;
    m_index = 0;
    for(int i = 1 ;i <= BOMB_MAX ;i++)
    {
        //字符串拼接，类似  ":/res/bomb-1.png"
        QString str = QString(BOMB_PATH).arg(i);//总之就是依次压进去，我草了
        m_pixArr.push_back(QPixmap(str));
    }
}

void Bomb::updateInfo()
{

    if(m_Free)
    {
        return ;
    }
    m_Recorder++;
        if(m_Recorder<BOMB_INTERVAL){return;}
     m_Recorder=0;
     m_index++;
    if(m_index > BOMB_MAX-1)
    {
        m_index = 0;
        m_Free = true;
    }

}
