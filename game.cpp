#include "game.h"
#include "spaceship.h"
#include "config.h"

#include <QWidget>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <random>

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

    DisplayAliens();
}

void Game::keyPressEvent(QKeyEvent *event) {
    if (ship == nullptr) return;

    switch (event->key()) {
        case Qt::Key_Up : {
            emergeFromOtherEnd();
            removeAlienOnCapture();
            moveForward();
            break;
        }
        case Qt::Key_Down: {
            emergeFromOtherEnd();
            removeAlienOnCapture();
            moveBackward();
            break;
        }
        case Qt::Key_Left: {
            removeAlienOnCapture();
            rotateAnticlockwise();
            break;
        }
        case Qt::Key_Right: {
            removeAlienOnCapture();
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

void Game::emergeFromOtherEnd() {
    int xCoordinate = ship->x();
    int yCoordinate = ship->y();

    if (xCoordinate < 0 && yCoordinate >= 0) {
        // went off from left side
        ship->setPos(screenSize.width(), ship->y());
    }
    else if (xCoordinate >=0 && yCoordinate < 0) {
        // went off from top side
        ship->setPos(ship->x(), screenSize.height());
    } else if (xCoordinate >= screenSize.width() \
               && yCoordinate >=0 \
               && yCoordinate < screenSize.height()) {
        // went off from right side
        ship->setPos(0, ship->y());
    } else if (yCoordinate >= screenSize.height() \
               && xCoordinate >= 0 \
               && xCoordinate < screenSize.width()) {
        //went off from bottom side
        ship->setPos(ship->x(), 0);
    }
}

void Game::DisplayAliens() {
    for (auto i = 0; i < maxAliens; i++) {
        scene()->addItem(createNewAlien());
    }
}

QSize Game::getRandomPos() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dsWidth(0, screenSize.width() - 50);
    std::uniform_int_distribution<int> dsHeight(0, screenSize.height() - 50);
    int x = dsWidth(mt);
    int y = dsHeight(mt);
    QSize *size = new QSize(x,y);
    return *size;
}

void Game::removeAlienOnCapture() {
    for (auto const item : ship->collidingItems()) {
        Alien* alien = dynamic_cast<Alien*>(item);
        if (alien != nullptr) {
            scene()->removeItem(alien);
            playSuccessSound();
            scene()->addItem(createNewAlien());
        }
    }
}

Alien* Game::createNewAlien() {
    Alien* newAlien = new Alien();
    QSize pos = getRandomPos();

    newAlien->setPos(pos.width(), pos.height());
    newAlien->setFocus();
    return newAlien;
}

void Game::playSuccessSound() {
    QMediaPlayer *player = new QMediaPlayer(this);
    player->setMedia(QUrl("qrc:/audio/success.mp3"));
    player->play();

}
