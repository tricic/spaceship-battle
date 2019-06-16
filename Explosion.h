/*
 * @author Ismar Tričić <ismar.tricic[at]gmail.com>
 */

#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QGraphicsPixmapItem>
#include <QMediaPlayer>

class Explosion :
        public QGraphicsPixmapItem,
        public QObject
{
public:
    Explosion(qreal x, qreal y);
    ~Explosion() override;

private slots:
    void deleteMe();

private:
    QMediaPlayer* sound;
    int duration = 1000;
};

#endif // EXPLOSION_H
