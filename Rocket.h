/*
 * @author Ismar Tričić <ismar.tricic[at]gmail.com>
 */

#ifndef ROCKET_H
#define ROCKET_H

#include <QGraphicsPixmapItem>
#include <QMediaPlayer>

class Rocket :
        public QGraphicsPixmapItem,
        public QObject
{
public:
    enum RotationDirection { Left, Right };
    enum ShootingMode { Front, Rear };

    Rocket(QGraphicsScene*);
    ~Rocket() override;

    void rotate(RotationDirection);
    void shoot(ShootingMode);
    void reset();

protected:
    void keyPressEvent(QKeyEvent*) override;

private:
    QMediaPlayer* shootingSound;
};

#endif // ROCKET_H
