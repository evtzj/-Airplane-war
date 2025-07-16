#include "map.h"

Map::Map() {
    m_map1.load(MAP1);
    m_map2.load(MAP1);

    m_map1_posY=-GAME_HEIGHT;
    m_map2_posY=0;

    m_scroll_speed=MAP_SCROOL_SPEED;
}

void Map::mapPosition()
{
    m_map1_posY+=m_scroll_speed;
    if(m_map1_posY==0){m_map1_posY=-GAME_HEIGHT;}

    m_map2_posY+=m_scroll_speed;
    if(m_map2_posY==GAME_HEIGHT){m_map2_posY=0;}
}
