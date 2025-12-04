#pragma once

#include <QWidget>
#include <QPainter>
#include "../snake/Snake.h"
#include <QTimer>
#include <qaction.h>
#include "../food/Food.h"
#include "GameOverDialog.h"


class GameArea : public QWidget
{
    Q_OBJECT
public:
    explicit GameArea(QWidget *parent = nullptr);
    void start();
    void stop();
    bool isRunning() const;
    int getSnakeNumber() const;
    int getSnakeScore(Snake *snake);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Snake *snake;
    Snake *snake2;
    Snake *snake3;
    
    QTimer *timer;
    int FPS = 100;
    bool is_Running = false;
    bool is_Food_Generated = false;
    Food *food;

    void generateFood();
    bool checkEatFood(Snake *snake, Food *food);
    bool checkCollision(Snake *snake);
    bool checkCollisionBetweenSnakes(Snake *snake1, Snake *snake2);
    void printSnake(QPainter &painter, Snake *snake);
    void controlSnake(QKeyEvent *event, Snake *snake, Snake::Control control);

public slots:
    void restart();
    void exitGame();
    void setSnakeColour(int player, Snake::Colour colour);
    void setSnakeController(int player, Snake::Controller controller);
    void snakeDied(Snake *snake);

signals:
    void scoreChanged(int score);
    void gameOver();
    void snakeCollided(Snake *snake);

};