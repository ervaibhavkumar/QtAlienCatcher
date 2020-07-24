#include <QApplication>
#include <QScreen>

#include "game.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game *game = new Game(qApp->screens()[0]->size());
    game->showMaximized();
    game->Start();
    return a.exec();
}
