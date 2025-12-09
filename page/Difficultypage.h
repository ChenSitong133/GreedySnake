
#ifndef DIFFICULTYPAGE_H
#define DIFFICULTYPAGE_H

#include "qobject.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>

class DifficultyPage : public QWidget
{
    Q_OBJECT
public:
    DifficultyPage(QWidget *parent = nullptr);  // 不要 explicit
    void changeLanguage(QString language);
    QPushButton *btnEasy;   //简单难度按钮
    QPushButton *btnNormal;     //普通难度按钮
    QPushButton *btnHard ;     //困难难度按钮
    QPushButton *btnBack;      //返回按钮
    QLabel *label;  //游戏难度选择标签

signals:
    void difficultySelected(int level);
    void backButtonClicked();
    void startGame();
};

#endif // DIFFICULTYPAGE_H
