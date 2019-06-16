/*
 * @author Ismar Tričić <ismar.tricic[at]gmail.com>
 */

#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsSimpleTextItem>

class Score : public QGraphicsSimpleTextItem
{
public:
    Score(QGraphicsScene*);
    void updateText();
    void increase();
    void decrease();
    void reset();

private:
    int score = 0;
};

#endif // SCORE_H
