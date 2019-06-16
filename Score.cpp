#include "Score.h"

#include <QGraphicsScene>

Score::Score(QGraphicsScene* scene)
{
    setPos(10, 10);
    setBrush(QBrush(Qt::white));
    setScale(2);
    setZValue(100);
    updateText();

    scene->addItem(this);
}

// Ažurira tekst sa aktuelnim brojem rezultata
void Score::updateText()
{
    setText(QString("Score: %1").arg(score));
}

// Povećava rezultat za 1
void Score::increase()
{
    ++score;
    updateText();
}

// Smanjuje rezultat za 1
void Score::decrease()
{
    --score;
    updateText();
}

// Resetuje rezultat na 0
void Score::reset()
{
    score = 0;
    updateText();
}
