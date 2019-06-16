/*
 * @author Ismar Tričić <ismar.tricic[at]gmail.com>
 */

#ifndef MISSILE_H
#define MISSILE_H

#include "Rocket.h"

#include <QGraphicsPixmapItem>
#include <QMediaPlayer>

class Missile :
        public QGraphicsPixmapItem,
        public QObject
{
public:
    static int created;
    static int destroyed;

    Missile(const Rocket*, bool oppositeDirection = false);
    ~Missile() override;

private slots:
    void move();

private:
    QTimer* moveTimer;
};

#endif // MISSILE_H
