#include "UpBar.h"
#include "qobject.h"
#include "qtmetamacros.h"

//cst的
//在构造函数中初始化UI
//在initConnections中连接信号槽
//当点击按钮时，发送信号，调用槽函数
//点击开始按钮时，发送开始游戏信号
//点击停止按钮时，发送停止游戏信号
//点击结束按钮时，发送结束游戏信号
//cst就发送信号，别的接收信号，然后调用槽函数是后端写的。

UpBar::UpBar(QWidget *parent) : QWidget(parent){
    
    initUI();
    initConnections();
}

void UpBar::initUI(){

    //设置宽度720
    this->setFixedWidth(720);

    //创建结束按钮
    endBtn = new QPushButton(this);
    endBtn->setText("End");

    //创建停止按钮
    stopBtn = new QPushButton(this);
    stopBtn->setText("Stop");

    //创建开始按钮
    startBtn = new QPushButton(this);
    startBtn->setText("Start");

    //创建时间标签
    timeLabel = new QLabel(this);
    // timeLabel->setText("Time: 00:00:00");

    //后端写的
    time = QTime(0, 0, 0);
    timeLabel->setText(Time + time.toString("hh:mm:ss"));
 
    //创建分数标签
    scoreLabel = new QLabel(this);
    scoreLabel2 = new QLabel(this);
    scoreLabel3 = new QLabel(this);
    //后端写的
    scoreLabel->setText(playerName + Score + QString::number(0));
    scoreLabel2->setText(playerName2 + Score + QString::number(0));
    scoreLabel3->setText(playerName3 + Score + QString::number(0));

    //创建布局，并添加子控件
    playerLayout = new QVBoxLayout();
    //添加标签到布局中
    playerLayout->addWidget(scoreLabel);
    playerLayout->addWidget(scoreLabel2);
    playerLayout->addWidget(scoreLabel3);

    //创建玩家布局，并添加子控件
    playerLayout = new QVBoxLayout();
    //添加标签到布局中
    playerLayout->addWidget(scoreLabel);
    playerLayout->addWidget(scoreLabel2);
    playerLayout->addWidget(scoreLabel3);


    //创建布局，并添加子控件
    layout = new QHBoxLayout(this);
    //添加按钮到布局中，包括结束、停止、开始、时间标签和玩家布局
    layout->addWidget(endBtn);
    layout->addWidget(stopBtn);
    layout->addWidget(startBtn);
    layout->addWidget(timeLabel);
    layout->addLayout(playerLayout);

    //设置布局
    this->setLayout(layout);

}

void UpBar::initConnections(){
    //连接按钮信号槽，发送信号
    //发送结束游戏信号
    connect(endBtn, &QPushButton::clicked, this, [this](){emit endGame();});
    //发送停止游戏信号
    connect(stopBtn, &QPushButton::clicked, this, [this](){emit stopGame();});
    //发送开始游戏信号
    connect(startBtn, &QPushButton::clicked, this, [this](){emit startGame();});
    
}

//后端写的
void UpBar::changeScore(int player, int score){
    switch(player){
        case 1:
            this->score = score;
            scoreLabel->setText(playerName + Score + QString::number(score));
            break;
        case 2:
            this->score2 = score;
            scoreLabel2->setText(playerName2 + Score + QString::number(score));
            break;
        case 3:
            this->score3 = score;
            scoreLabel3->setText(playerName3 + Score + QString::number(score));
            break;
        default:
            break;
    }
}

//后端写的
void UpBar::changePlayerName(int player, QString name){
    switch(player){
        case 1:
            playerName = name;
            scoreLabel->setText(playerName + Score + QString::number(0));
            break;
        case 2:
            playerName2 = name;
            scoreLabel2->setText(playerName2 + Score + QString::number(0));
            break;
        case 3:
            playerName3 = name;
            scoreLabel3->setText(playerName3 + Score + QString::number(0));
            break;
        default:
            break;
    }
}

//后端写的
void UpBar::changeLanguage(QString language){
    if(language == "en"){
        endBtn->setText("End");
        stopBtn->setText("Stop");
        startBtn->setText("Start");
        Time = "Time: ";
        timeLabel->setText(Time + time.toString("hh:mm:ss"));
        scoreLabel->setText(playerName + Score + QString::number(0));
        scoreLabel2->setText(playerName2 + Score + QString::number(0));
        scoreLabel3->setText(playerName3 + Score + QString::number(0));
    }
    else if(language == "zh"){
        endBtn->setText("结束");
        stopBtn->setText("停止");
        startBtn->setText("开始");  
        Time = "时间: ";
        timeLabel->setText(Time + time.toString("hh:mm:ss"));
        Score = " 分数: ";
        scoreLabel->setText(playerName + Score +QString::number(score));
        scoreLabel2->setText(playerName2 + Score + QString::number(score2));
        scoreLabel3->setText(playerName3 + Score + QString::number(score3));

    }
}

//后端写的
void UpBar::addTime(){
    time = time.addSecs(1);
    timeLabel->setText(Time + time.toString("hh:mm:ss"));
}

