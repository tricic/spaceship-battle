#include "Missile.h"
#include "Asteroid.h"
#include "Rocket.h"
#include "Game.h"
#include "Explosion.h"

#include <QtMath>
#include <QTimer>
#include <QGraphicsScene>
#include <QTypeInfo>

#include <QDebug>

extern Game* game;

int Missile::created = 0;
int Missile::destroyed = 0;

Missile::Missile(const Rocket* player, bool oppositeDirection) :
    QGraphicsPixmapItem(),
    QObject()
{
    // Velicina 10x24
    setPixmap(QPixmap(":/images/resources/missile.png"));

    // Postavljanje pozicije
    setPos(player->sceneBoundingRect().center());
    // Da centar projektila bude u sredini
    setX(this->x() - 5);
    setY(this->y() - 12);

    // Postavljanje tacke rotacije
    setTransformOriginPoint(boundingRect().center());

    // Rotiranje projektila shodno rotaciji rakete
    setRotation(oppositeDirection ? player->rotation() - 180 : player->rotation());

    // Tajmer
    moveTimer = new QTimer();
    moveTimer->start(50);
    connect(moveTimer, &QTimer::timeout, this, &Missile::move);

    ++created;
}

Missile::~Missile()
{
    ++destroyed;
    delete moveTimer;
}

// Pomjera projektil
void Missile::move()
{
    // Računanje sljedeće [x,y] pozicije
    int multiplier = 15;
    qreal x =  this->x() + qCos(qDegreesToRadians(rotation() - 90)) * multiplier;
    qreal y =  this->y() + qSin(qDegreesToRadians(rotation() - 90)) * multiplier;

    // Postavljanje nove pozicije
    setPos(x, y);

    // Provjera sudaranja sa krajevima scene
    if (y < 1 || x > scene()->width() - 32 || x < 1 || y > scene()->height() - 32)
    {
        Explosion* explosion = new Explosion(this->x(), this->y());
        scene()->addItem(explosion);

        scene()->removeItem(this);
        delete this;
    }
    // Provjera sudaranja sa asteroidima
    else
    {
        for (auto item : collidingItems())
        {
            if (typeid(*item) == typeid(Asteroid))
            {
                Explosion* explosion = new Explosion(item->x(), item->y());
                scene()->addItem(explosion);

                game->getScore()->increase();

                scene()->removeItem(item);
                scene()->removeItem(this);

                delete item;
                delete this;
            }
        }
    }
}
