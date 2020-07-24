#include "game.h"
#include "spaceship.h"
#include "config.h"

#include <QWidget>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsScene>

Game::Game(QSize sizeOfScreen, QGraphicsView *parent)
    : QGraphicsView(parent),
      screenSize(sizeOfScreen)
{
    QGraphicsScene *scene = new QGraphicsScene();
    setScene(scene);

    scene->setSceneRect(0,0,screenSize.width(),screenSize.height());
    setBackgroundBrush(QBrush(QImage(":/images/SpaceInvadersBg.jpg")));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Game::Start() {
    scene()->clear();

    ship = new Spaceship();
    ship->setPos(screenSize.width() / 2, screenSize.height() / 2);
    ship->setFocus();
    scene()->addItem(ship);
}

void Game::keyPressEvent(QKeyEvent *event) {
    if (ship == nullptr) return;

    switch (event->key()) {
        case Qt::Key_Up : {
            moveForward();
            break;
        }
        case Qt::Key_Down: {
            moveBackward();
            break;
        }
        case Qt::Key_Left: {
            rotateAnticlockwise();
            break;
        }
        case Qt::Key_Right: {
            rotateClockwise();
            break;
        }
    }
}

void Game::moveForward() {
    int angle = ship->rotation();
    if (angle == 0) {
        // no rotation is done yet.
        ship->setPos(ship->x() , ship->y() - translationOffset);
    }
    else if (angle == 180 || angle == -180) {
        // upside down.
        ship->setPos(ship->x(), ship->y() + translationOffset);
    }
    else if (angle == 90) {
        // anticlockwise perpendicular
        ship->setPos(ship->x() + translationOffset, ship->y());
    }
    else if (angle == -90) {
        // clockwise perpendicular
        ship->setPos(ship->x()  - translationOffset, ship->y());
    }
    else if (angle > 0 && angle < 90) {
        // rotation was done in anti-clockwise direction and never came to 0
        // ship is in 4th quadrant
        ship->setPos(ship->x() + translationOffset, ship->y() - translationOffset);
    }
    else if (angle > 90 && angle < 180) {
        // rotation was done in clockwise direction and never came back to -ve
        // ship is in 3rd quadrant
        ship->setPos(ship->x() + translationOffset, ship->y() + translationOffset);
    }
    else if (angle > -180 && angle < -90) {
        // ship is in 2nd quadrant
        ship->setPos(ship->x() - translationOffset, ship->y() + translationOffset);
    }
    else if (angle > -90 && angle < 0) {
        // ship is in 1st quadrant
        ship->setPos(ship->x() - translationOffset, ship->y() - translationOffset);
    }
}

void Game::moveBackward() {
    int angle = ship->rotation();
    if (angle == 0) {
        // no rotation is done yet.
        ship->setPos(ship->x() , ship->y() + translationOffset);
    }
    else if (angle == 180 || angle == -180) {
        // upside down.
        ship->setPos(ship->x(), ship->y() - translationOffset);
    }
    else if (angle == 90) {
        // anticlockwise perpendicular
        ship->setPos(ship->x() - translationOffset, ship->y());
    }
    else if (angle == -90) {
        // clockwise perpendicular
        ship->setPos(ship->x()  + translationOffset, ship->y());
    }
    else if (angle > 0 && angle < 90) {
        // rotation was done in anti-clockwise direction and never came to 0
        // ship is in 4th quadrant
        ship->setPos(ship->x() - translationOffset, ship->y() + translationOffset);
    }
    else if (angle > 90 && angle < 180) {
        // rotation was done in clockwise direction and never came back to -ve
        // ship is in 3rd quadrant
        ship->setPos(ship->x() - translationOffset, ship->y() - translationOffset);
    }
    else if (angle > -180 && angle < -90) {
        // ship is in 2nd quadrant
        ship->setPos(ship->x() + translationOffset, ship->y() - translationOffset);
    }
    else if (angle > -90 && angle < 0) {
        // ship is in 1st quadrant
        ship->setPos(ship->x() + translationOffset, ship->y() + translationOffset);
    }
}

void Game::rotateAnticlockwise() {
    int angle = ship->rotation();
    if (angle < -180) {
        angle += 360;
    }
    ship->setRotation(angle - rotationAngle);
}

void Game::rotateClockwise() {
    int angle = ship->rotation();
    if (angle >= 180) {
        angle = angle - 360;
    }
    ship->setRotation(angle + rotationAngle);
}
