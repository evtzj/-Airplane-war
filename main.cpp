#include "mainscene.h"
#include"menuscene.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //一些试图优化游戏的代码
    a.setKeyboardInputInterval(0);//试图优化游戏的代码
    MenuScene ms;
    ms.show();
    return a.exec();
}
