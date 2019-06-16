/*
 * @author Ismar Tričić <ismar.tricic[at]gmail.com>
 */

#ifndef GAME_H
#define GAME_H

#include "Rocket.h"
#include "Score.h"
#include "Lives.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class Game : public QGraphicsView
{
public:
    Game(QWidget* parent = nullptr);
    ~Game() override;

    Rocket* getRocket() const;
    Score* getScore() const;
    Lives* getLives() const;

protected:
    virtual void focusInEvent(QFocusEvent*) override;

public slots:
    void gameOver();
    void resetGame();
    void playRocketHitSound() const;


private slots:
    void createAsteroid();

private:
    // Scena
    QGraphicsScene* scene;

    // Zvukovi
    QMediaPlaylist* playlist;
    QMediaPlayer* music;
    QMediaPlayer* rocketHitSound;
    QMediaPlayer* gameOverSound;

    // Raketa, rezultat, životi, tekst za kraj igre
    Rocket* rocket;
    Score* score;
    Lives* lives;
    QGraphicsSimpleTextItem* gameOverText;

    // Timer i interval za kreiranje asteroida
    QTimer* asteroidCreatorTimer;
    int asteroidCreatorInterval = 2000;
};

#endif // GAME_H
