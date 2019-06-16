#include "Rocket.h"
#include "Missile.h"

#include <QGraphicsScene>
#include <QKeyEvent>

#include <QDebug>

Rocket::Rocket(QGraphicsScene* scene) :
    QGraphicsPixmapItem(),
    QObject()
{
    // Postavljanje pixmap slike, slika je dimenzija 64x64
    setPixmap(QPixmap(":/images/resources/spaceship.png"));

    // Postavljanje tacke oko koje ce se raketa rotirati (odnosi se na sam pixmapitem objekat, ne na scenu)
    setTransformOriginPoint(boundingRect().center());

    // Postavljanje pozicije
    setPos(scene->width() / 2 - 32, scene->height() / 2 - 32);

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    setZValue(100);

    // Setup zvuka pucanja
    shootingSound = new QMediaPlayer;
    shootingSound->setMedia(QUrl("qrc:/audio/resources/shooting_sound.wav"));
    shootingSound->setVolume(70);

    scene->addItem(this);
}

Rocket::~Rocket()
{
}

// Rotiranje rakete
void Rocket::rotate(RotationDirection direction)
{
    switch (direction)
    {
    case Left:
        setRotation(rotation() - 5);
        break;

    case Right:
        setRotation(rotation() + 5);
        break;
    }
}

// Pucanje projektila
void Rocket::shoot(ShootingMode shootingMode)
{
    Missile* missile;

    switch (shootingMode)
    {
    case Front:
        missile = new Missile(this);
        break;

    case Rear:
        missile = new Missile(this, true);
        break;
    }

    scene()->addItem(missile);

    // Zvuk
    shootingSound->stop();
    shootingSound->play();
}

// Resetuje rotaciju rakete na default
void Rocket::reset()
{
    setRotation(0);
}

void Rocket::keyPressEvent(QKeyEvent* e)
{
    switch (e->key())
    {
    case Qt::Key_Left:
        rotate(Rocket::Left);
        break;

    case Qt::Key_Right:
        rotate(Rocket::Right);
        break;

    case Qt::Key_Up:
        shoot(Rocket::Front);
        break;

    case Qt::Key_Down:
        shoot(Rocket::Rear);
        break;

    default:
        break;
    }
}
