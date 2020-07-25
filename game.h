#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QKeyEvent>

#include "spaceship.h"
#include "alien.h"

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QSize sizeOfScreen, QGraphicsView *parent = nullptr);
    void Start();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void moveForward();
    void moveBackward();
    void rotateAnticlockwise();
    void rotateClockwise();
    void emergeFromOtherEnd();
    void removeAlienOnCapture();

    void DisplayAliens();
    QSize getRandomPos();
    Alien* createNewAlien();
    void playSuccessSound();

    QSize screenSize;
    Spaceship* ship = nullptr;
};

#endif // GAME_H
