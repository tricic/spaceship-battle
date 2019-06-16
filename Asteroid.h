/*
 * @author Ismar Tričić <ismar.tricic[at]gmail.com>
 */

#ifndef ASTEROID_H
#define ASTEROID_H

#include <QGraphicsPixmapItem>
#include <QMediaPlayer>

class Asteroid :
        public QGraphicsPixmapItem,
        public QObject
{
public:
    static int created;
    static int destroyed;

    Asteroid(QGraphicsScene*);
    ~Asteroid() override;

private slots:
    void move();

private:
    QTimer* moveTimer;
};

#endif // ASTEROID_H
