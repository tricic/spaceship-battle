#include "Game.h"
#include "Asteroid.h"
#include "Missile.h"

#include <QTimer>
#include <QTypeInfo>
#include <QIcon>

#include <QDebug>

Game::Game(QWidget* parent)
{
    // Dimenzije scene
    int w = 800;
    int h = 800;

    // Kreiranje scene
    scene = new QGraphicsScene(1, 1, w, h, parent);

    // Setup Game-a (QGraphicsView)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(w + 2, h + 2);
    setBackgroundBrush(QBrush(QImage(":/images/resources/background.jpg")));
    setWindowIcon(QIcon(":/images/resources/spaceship.png"));
    setWindowTitle("IPIA - OOP | Final Project by Ismar Tričić");

    // Pozadinska muzika
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/audio/resources/background_music.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(70);
    music->play();

    // Zvuk kada asteroid pogodi raketu
    rocketHitSound = new QMediaPlayer();
    rocketHitSound->setMedia(QUrl("qrc:/audio/resources/rocket_hit_sound.wav"));

    // Zvuk za kraj igre
    gameOverSound = new QMediaPlayer();
    gameOverSound->setMedia(QUrl("qrc:/audio/resources/game_over_sound.wav"));

    // Raketa (igrač)
    rocket = new Rocket(scene);

    // Rezultat
    score = new Score(scene);

    // Životi
    lives = new Lives(scene);

    // Tekst za Game over
    gameOverText = new QGraphicsSimpleTextItem();
    gameOverText->setText("Game over. New game will start in few seconds.");
    gameOverText->setBrush(QBrush(Qt::white));
    gameOverText->setScale(3);
    gameOverText->setPos(60, 300);
    gameOverText->hide();
    scene->addItem(gameOverText);

    // Tajmer koji ce kreirati asteroide
    asteroidCreatorTimer = new QTimer();
    asteroidCreatorTimer->start(asteroidCreatorInterval);
    connect(asteroidCreatorTimer, &QTimer::timeout, this, &Game::createAsteroid);
}

Game::~Game()
{
    delete scene;
    delete playlist;
    delete music;
    delete rocketHitSound;
    delete gameOverSound;
    delete rocket;
    delete score;
    delete lives;
    delete gameOverText;
    delete asteroidCreatorTimer;
}

Rocket* Game::getRocket() const
{
    return rocket;
}

Score* Game::getScore() const
{
    return score;
}

Lives* Game::getLives() const
{
    return lives;
}

void Game::focusInEvent(QFocusEvent* e)
{
    QGraphicsView::focusInEvent(e);
    rocket->setFocus();
}

// Zaustavlja igru i poziva metod resetiranja igre nakon kratke pauze
void Game::gameOver()
{
    music->stop();
    gameOverSound->play();

    // Zaustavljanje kreiranje asteroida
    asteroidCreatorTimer->stop();

    // Brisanje asteroida i projektila sa scene
    for (auto item : scene->items())
    {
        if (typeid (*item) == typeid (Asteroid) || typeid (*item) == typeid (Missile))
        {
            scene->removeItem(item);
            delete item;
        }
    }

    // Prikazivanje teksta za kraj igre
    gameOverText->show();

    // Pozivanje resetGame metode nakon 5 sekundi
    QTimer::singleShot(5000, this, &Game::resetGame);

    // Ispisuje broj kreiranih i unistenih asteroida i projektila
    qDebug() << "Asteroids created: " << Asteroid::created;
    qDebug() << "Asteroids destroyed: " << Asteroid::destroyed;
    qDebug() << "Missiles created: " << Missile::created;
    qDebug() << "Missiles destroyed: " << Missile::destroyed;
}

// Resetuje igru - resetuje rezultat, zivote, polozaj rakete i interval kreiranja asteroida
void Game::resetGame()
{
    score->reset();
    lives->reset();
    rocket->reset();
    asteroidCreatorTimer->start(asteroidCreatorInterval);
    gameOverText->hide();
    music->play();
}

// Pokrece sound kada asteroid udari raketu
void Game::playRocketHitSound() const
{
    rocketHitSound->play();
}

// Kreira asteroid na sceni
void Game::createAsteroid()
{
    // Kreiranje objekta
    new Asteroid(scene);

    // Smanjivanje intervala kreiranja novih asteroida
    if (asteroidCreatorTimer->interval() >= 300)
    {
        asteroidCreatorTimer->setInterval(asteroidCreatorTimer->interval() - 30);
    }
}
