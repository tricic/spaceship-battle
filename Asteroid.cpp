#include "Asteroid.h"
#include "Rocket.h"
#include "Game.h"

#include <QtMath>
#include <QTimer>
#include <QTypeInfo>
#include <QGraphicsScene>

#include <QDebug>

extern Game* game;

int Asteroid::created = 0;
int Asteroid::destroyed = 0;

Asteroid::Asteroid(QGraphicsScene* scene) :
    QGraphicsPixmapItem(),
    QObject()
{
    // Velicina 32x32
    setPixmap(QPixmap(":/images/resources/asteroid.png"));

    // Postavljanje tacke rotacije
    setTransformOriginPoint(boundingRect().center());

    // Postavljanje random pozicije
    qreal xMin = 15;
    qreal xMax = scene->width() - 32;

    qreal yMin = 15;
    qreal yMax = scene->height() - 32;

    qreal xRand = qrand() % (int(xMax) - int(xMin)) + xMin;
    qreal yRand = qrand() % (int(yMax) - int(yMin)) + yMin;

    if (qrand() % 2) // Spawnati vertikalno (gore ili dolje)
    {
        if (qrand() % 2) // Spawnati gore
        {
            setPos(xRand, yMin);
            setRotation(qrand() % 360);
        }
        else // Spawnati dolje
        {
            setPos(xRand, yMax);
            setRotation(qrand() % 360);
        }
    }
    else // Spawnati horizontalno (lijevi ili desno)
    {
        if (qrand() % 2) // Spawnati lijevo
        {
            setPos(xMin, yRand);
            setRotation(qrand() % 360);
        }
        else // Spawnati desno
        {
            setPos(xMax, yRand);
            setRotation(qrand() % 360);
        }
    }

    // Tajmer za pomjeranje
    moveTimer = new QTimer();
    moveTimer->start(50);
    connect(moveTimer, &QTimer::timeout, this, &Asteroid::move);

    // Dodavanje u scenu
    scene->addItem(this);
    ++created;
}

Asteroid::~Asteroid()
{
    ++destroyed;
    delete moveTimer;
}

// Pomjera asteroid
void Asteroid::move()
{
    // Računanje sljedeće [x,y] pozicije
    int multiplier = 7;
    qreal x =  this->x() + qCos(qDegreesToRadians(rotation() - 90)) * multiplier;
    qreal y =  this->y() + qSin(qDegreesToRadians(rotation() - 90)) * multiplier;

    // Postavljanje nove pozicije
    setPos(x, y);

    // Provjeravanje sudara sa granicama scene
    if (y < 10 || y > scene()->height() - 10) // Horizontalne granice
    {
        setRotation(180 - rotation());
    }
    else if (x < 10 || x > scene()->width() - 10) // Vertikalne granice
    {
        setRotation(360 - rotation());
    }
    // Provjera sudara sa raketom
    else if (collidesWithItem(game->getRocket()))
    {
        scene()->removeItem(this);
        game->playRocketHitSound();
        game->getLives()->decrease();
        delete this;
    }
}
