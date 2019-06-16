#include "Explosion.h"

#include <QTimer>
#include <QGraphicsScene>

Explosion::Explosion(qreal x, qreal y) :
    QGraphicsPixmapItem(),
    QObject()
{
    // Velicina 24x24
    setPixmap(QPixmap(":/images/resources/explosion.png"));
    setPos(x, y);

    // Zvuk eksplozije
    sound = new QMediaPlayer();
    sound->setMedia(QUrl("qrc:/audio/resources/explosion_sound.wav"));
    sound->setVolume(20);
    sound->play();

    QTimer::singleShot(duration, this, &Explosion::deleteMe);
}

Explosion::~Explosion()
{
    delete sound;
}

// Uklanja item iz scene i uništava se
void Explosion::deleteMe()
{
    scene()->removeItem(this);
    delete this;
}
