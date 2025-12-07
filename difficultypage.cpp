#include "DifficultyPage.h"
#include <QPushButton>
#include <QLabel>

// 构造函数 - 绝对正确的写法
DifficultyPage::DifficultyPage(QWidget *parent) : QWidget(parent)
{
    // 设置窗口大小
    this->setFixedSize(720, 600);

    // 设置背景颜色
    this->setStyleSheet("background-color:black;");

    // 创建标题
    QLabel *label = new QLabel("选择游戏难度", this);
    label->setGeometry(0, 100, 720, 50);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 24px; font-weight: bold;");

    // 创建按钮
    QPushButton *btnEasy = new QPushButton("简单模式", this);
    QPushButton *btnNormal = new QPushButton("普通模式", this);
    QPushButton *btnHard = new QPushButton("困难模式", this);
    QPushButton *btnBack = new QPushButton("返回主界面", this);

    // 设置按钮位置
    btnEasy->setGeometry(260, 200, 200, 50);
    btnNormal->setGeometry(260, 270, 200, 50);
    btnHard->setGeometry(260, 340, 200, 50);
    btnBack->setGeometry(300, 430, 120, 40);

    // 设置按钮样式
    btnEasy->setStyleSheet("font-size: 20px; background-color: #4CAF50; color: white;");
    btnNormal->setStyleSheet("font-size: 20px; background-color: #2196F3; color: white;");
    btnHard->setStyleSheet("font-size: 20px; background-color: #f44336; color: white;");
    btnBack->setStyleSheet("font-size: 16px; background-color: #666; color: white;");

    // 连接信号
    QObject::connect(btnEasy, &QPushButton::clicked, this, [=](){
        emit difficultySelected(1);
    });

    QObject::connect(btnNormal, &QPushButton::clicked, this, [=](){
        emit difficultySelected(2);
    });

    QObject::connect(btnHard, &QPushButton::clicked, this, [=](){
        emit difficultySelected(3);
    });

    QObject::connect(btnBack, &QPushButton::clicked, this, [=](){
        emit backButtonClicked();
    });
}
