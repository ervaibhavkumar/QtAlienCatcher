#ifndef ALIEN_H
#define ALIEN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class Alien : public QObject, public QGraphicsPixmapItem
{
public:
    Alien(QGraphicsItem *parent = nullptr);

private:
    void DisplayAlien();
};

#endif // ALIEN_H
