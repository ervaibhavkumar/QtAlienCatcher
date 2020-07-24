#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class Spaceship : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Spaceship(QGraphicsItem *parent = nullptr);

private:
    void DisplayShip();
};

#endif // SPACESHIP_H
