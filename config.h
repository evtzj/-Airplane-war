#ifndef CONFIG_H
#define CONFIG_H
#define GAME_WIDTH 512  //此处尺寸可随意修改，但是要保证跟map一致，不然后面没办法开发
#define GAME_HEIGHT 768
#define MAP_SCROOL_SPEED 2
#define GAME_RATE 8
#define GAME_TITLE "Lumispire"
#define BULLET_SPEED 10
#define BULLET_NUM 200
#define BULLET_INTERVAL 20
#define ENEMY_NUM 20
#define ENEMY_SPEED 2
#define ENEMY_INTERVAL 50
#define BOMB_NUM 20
#define BOMB_INTERVAL 10
#define BOMB_MAX 7 //爆炸索引，一共7张图播放一个动画
#define ENEMY_HEALTH 400
#define BOSS_HEALTH 8000
#define ENEMY_BULLET_NUM 100
#define ENEMY_SHOOT_INTERVAL 80
#define ENEMY_BULLET_SPEED 3
#define PLAYER_LIFE 5 //残机数量



//路径存放便捷版
#define GAME_ICON ":/res/app.ico"
#define MAP1 ":/res/img_bg_level_2.jpg"
#define PLAYER_PLANE ":/res/character1.png"
#define BULLET_PATH ":/res/bullet_4.png"
#define ENEMY_N_PATH ":/res/img-plane_5.png"
#define BOMB_PATH ":/res/bomb-%1.png"


#endif // CONFIG_H
