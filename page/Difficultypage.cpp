#include "DifficultyPage.h"
#include <QPushButton>
#include <QLabel>

// blx的在
// 难度选择页面的构造函数，创建按钮，设置按钮位置，设置按钮样式，设置信号与槽的连接
// 难度选择页面的信号，难度选择信号，难度选择信号的槽函数，启动游戏信号，启动游戏信号的槽函数，返回按钮信号，返回按钮信号的槽函数
// 难度选择页面的函数，改变语言函数，后端写的，不用管
// 点击按钮时，发送信号，调用函数来改变难度，并启动游戏，blx就发送信号,别的后端写
DifficultyPage::DifficultyPage(QWidget *parent) : QWidget(parent)
{
    // 设置窗口大小
    this->setFixedSize(720, 600);

    // 设置背景颜色
    this->setStyleSheet("background-color:black;");

    // 创建标题
    label = new QLabel("please select difficulty", this);
    // 设置标题位置在坐标（0，100）处，大小为720x50，居中对齐，字体大小为24px，加粗
    label->setGeometry(0, 100, 720, 50);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 24px; font-weight: bold;");

    // 创建按钮
    btnEasy = new QPushButton("easy mode", this);   // 简单按钮
    btnNormal = new QPushButton("normal mode", this);   // 普通按钮
    btnHard = new QPushButton("hard mode", this);   // 困难按钮
    btnBack = new QPushButton("back", this);   // 返回按钮

    // 设置按钮位置
    //设置简单按钮位置在坐标（260，200）处，大小为200x50，字体大小为20px
    btnEasy->setGeometry(260, 200, 200, 50);
    //设置普通按钮位置在坐标（260，270）处，大小为200x50，字体大小为20px
    btnNormal->setGeometry(260, 270, 200, 50);
    //设置困难按钮位置在坐标（260，340）处，大小为200x50，字体大小为20px
    btnHard->setGeometry(260, 340, 200, 50);
    //设置返回按钮位置在坐标（300，430）处，大小为120x40，字体大小为16px
    btnBack->setGeometry(300, 430, 120, 40);

    // 设置按钮样式后端写的，不用管
    btnEasy->setStyleSheet("font-size: 20px; background-color: #4CAF50; color: white;");
    btnNormal->setStyleSheet("font-size: 20px; background-color: #2196F3; color: white;");
    btnHard->setStyleSheet("font-size: 20px; background-color: #f44336; color: white;");
    btnBack->setStyleSheet("font-size: 16px; background-color: #666; color: white;");

    //当点击按钮时，发送信号，调用函数来改变难度，并启动游戏，blx就发送信号,别的后端写
    QObject::connect(btnEasy, &QPushButton::clicked, this, [=](){
        //发送难度改变的信号，调用函数来改变难度，并启动游戏，blx就发送信号,别的后端写
        emit difficultySelected(1);
        emit startGame();
    });
    //当点击按钮时，发送信号，调用函数来改变难度，并启动游戏，blx就发送信号,别的后端写
    QObject::connect(btnNormal, &QPushButton::clicked, this, [=](){
        //发送难度改变的信号，调用函数来改变难度，并启动游戏，blx就发送信号,别的后端写
        emit difficultySelected(2);
        emit startGame();
    });

    //当点击按钮时，发送信号，调用函数来改变难度，并启动游戏，blx就发送信号,别的后端写
    QObject::connect(btnHard, &QPushButton::clicked, this, [=](){
        //发送难度改变的信号，调用函数来改变难度，并启动游戏，blx就发送信号,别的后端写
        emit difficultySelected(3);
        emit startGame();
    });
    //当点击按钮时，发送信号，调用函数来返回上一页，blx就发送信号,别的后端写
    QObject::connect(btnBack, &QPushButton::clicked, this, [=](){
        emit backButtonClicked();
    });

}

// 改变语言，后端写的，不用管
void DifficultyPage::changeLanguage(const QString language){
    if(language == "zh"){
        this->label->setText("请选择难度");
        btnEasy->setText("简单模式");
        btnNormal->setText("普通模式");
        btnHard->setText("困难模式");
        btnBack->setText("返回");
    }else if(language == "en"){
        this->label->setText("please select difficulty");
        btnEasy->setText("easy mode");
        btnNormal->setText("normal mode");
        btnHard->setText("hard mode");
        btnBack->setText("back");
    }
}