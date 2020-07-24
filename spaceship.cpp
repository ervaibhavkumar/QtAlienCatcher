#include "spaceship.h"

#include <QGraphicsScene>

Spaceship::Spaceship(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    DisplayShip();
}

void Spaceship::DisplayShip() {
    QPixmap oPixmap(":/images/BlueCannon.png");
    setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
}
