#ifndef MAP_H
#define MAP_H

#include "config.h"
#include <QPixmap>

class Map   //这个很简单不用管
{
public:
    Map();
    void mapPosition();

    QPixmap m_map1;
    QPixmap m_map2;

    int m_map1_posY;
    int m_map2_posY;

    int m_scroll_speed;
};

#endif // MAP_H
