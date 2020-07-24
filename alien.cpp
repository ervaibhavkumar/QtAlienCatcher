#include "alien.h"
#include "config.h"

#include <random>

Alien::Alien(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    DisplayAlien();
}

void Alien::DisplayAlien() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dsAlien(minAlienSize, maxAlienSize);

    QPixmap oPixmap(":/images/RedAlien.png");
    int size = dsAlien(mt);
    setPixmap(oPixmap.scaled(QSize(size, size), Qt::KeepAspectRatio));
}
