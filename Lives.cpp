#include "Lives.h"
#include "Game.h"

#include <QGraphicsScene>

extern Game* game;

Lives::Lives(QGraphicsScene* scene)
{
    setPos(10, 35);
    setBrush(QBrush(Qt::white));
    setScale(2);
    setZValue(100);
    updateText();

    scene->addItem(this);
}

// Ažurira tekst sa aktuelnim brojem života
void Lives::updateText()
{
    setText(QString("Lives: %1").arg(lives));
}

// Povećava rezultat za 1
void Lives::increase()
{
    ++lives;
    updateText();
}

// Smanjuje rezultat za 1 i provjerava da li je rezultat 0
void Lives::decrease()
{
    --lives;
    updateText();

    if (!lives)
    {
        game->gameOver();
    }
}

// Resetuje živote na 3
void Lives::reset()
{
    lives = 3;
    updateText();
}
