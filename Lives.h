/*
 * @author Ismar Tričić <ismar.tricic[at]gmail.com>
 */

#ifndef LIVES_H
#define LIVES_H

#include <QGraphicsSimpleTextItem>

class Lives : public QGraphicsSimpleTextItem
{
public:
    Lives(QGraphicsScene*);
    void updateText();
    void increase();
    void decrease();
    void reset();

private:
    int lives = 3;
};

#endif // LIVES_H
