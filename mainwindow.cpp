#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QFile>
#include <QDir>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    startPage(nullptr),
    settingPage(nullptr),
    rankingPage(nullptr),
    gamePage(nullptr),
    difficultyPage(nullptr),
    middlePage(nullptr),
    mediaPlayer(nullptr),
    audioOutput(nullptr)
{
    // 设置窗口大小和标题
    setFixedSize(720, 600);
    setWindowTitle("Greedy Snake");
    QTranslator*translator=new QTranslator(this);
    // 创建页面
    startPage = new StartPage(this);
    settingPage = nullptr;
    rankingPage = nullptr;
    gamePage = nullptr;
    middlePage =nullptr;
    difficultyPage=(nullptr);
    // 设置开始页面为当前页面
    setCentralWidget(startPage);


    // if (startPage) {
    //     // Start Game 连接（保持不变）
    //     connect(startPage, &StartPage::StartPageStart, this, [=](){
    //         if (!middlePage) {
    //             middlePage = new MiddlePage(this);
    //             connect(middlePage, &MiddlePage::startGame, this, [=](){
    //                 if (!gamePage) {
    //                     gamePage = new GamePage(this);
    //                     connect(gamePage, &GamePage::exitGame, this, [=](){
    //                         setCentralWidget(startPage);
    //                     });
    //                 }
    //                 setCentralWidget(gamePage);
    //             });
    //         }
    //         setCentralWidget(middlePage);
    //     });

    if (startPage) {
        // 1. Start Game 按钮 - 显示难度选择页面
        connect(startPage, &StartPage::StartPageStart, this, [=](){
            // 创建难度选择页面
            if (!difficultyPage) {
                difficultyPage = new DifficultyPage(this);

                // 连接难度选择信号
                connect(difficultyPage, &DifficultyPage::difficultySelected, this, [=](int level){
                    // 根据选择的难度进入游戏
                    if (!gamePage) {
                        gamePage = new GamePage(this);
                        connect(gamePage, &GamePage::exitGame, this, [this](){
                            setCentralWidget(startPage);
                        });
                    }
                    // 可以在这里根据难度设置游戏参数
                    // setCentralWidget(gamePage);
                    // gamePage->startGame();
                });

                // 连接返回按钮
                connect(difficultyPage, &DifficultyPage::backButtonClicked, this, [this](){
                    setCentralWidget(startPage);
                });
            }

            // 显示难度选择页面
            setCentralWidget(difficultyPage);
        });

        connect(startPage, &StartPage::StartPageSettings, this, [=](){
            qDebug() << "===== 点击了 Settings 按钮 =====";

            // 创建 SettingPage（如果还未创建）
            if (!settingPage) {
                qDebug() << "创建新的 SettingPage 对象";
                settingPage = new SettingPage(translator, this);

                // 调试：检查 settingPage 是否创建成功
                qDebug() << "SettingPage 地址：" << settingPage;

                // 重要：使用新的连接方式
                // 方法1：使用 lambda 表达式
                connect(settingPage, &SettingPage::backButtonClicked, this, [this]() {
                    qDebug() << "!!! 接收到 SettingPage 的 backButtonClicked 信号 !!!";
                    qDebug() << "startPage 地址：" << startPage;

                    if (startPage) {
                        qDebug() << "正在返回主界面...";
                        setCentralWidget(startPage);
                        qDebug() << "已返回主界面";
                    } else {
                        qDebug() << "错误：startPage 为 nullptr";
                    }
                });

                // 也可以添加传统连接方式作为备份
                connect(settingPage, SIGNAL(backButtonClicked()),
                        this, SLOT(returnToMainPage()));

                qDebug() << "SettingPage 信号连接完成";
            } else {
                qDebug() << "使用已存在的 SettingPage";
            }

            // 显示设置页面
            setCentralWidget(settingPage);
            settingPage->setFocus();
            qDebug() << "SettingPage 已显示，等待返回操作";
            qDebug() << "===============================";
        });
        connect(startPage, &StartPage::StartPageRanking, this, [=](){
            if (!rankingPage) {
                rankingPage = new RankingPage(this);
                connect(rankingPage, &RankingPage::backButtonClicked, this, [=](){
                    setCentralWidget(startPage);
                });
            }
            setCentralWidget(rankingPage);
        });

        // Exit 按钮连接
        connect(startPage, &StartPage::StartPageExit, this, &QApplication::quit);
    }

    // // 初始化连接
    // setupConnections();

    // // 应用主题
    // applyTheme("light");



    // 初始化音频
    setupAudio();
}

MainWindow::~MainWindow()
{
    // 清理音频资源
    if (mediaPlayer) {
        mediaPlayer->stop();
        delete mediaPlayer;
    }
    if (audioOutput) {
        delete audioOutput;
    }
}

void MainWindow::setupAudio()
{
    // 创建音频播放器
    audioOutput = new QAudioOutput(this);
    audioOutput->setVolume(0.5);

    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setAudioOutput(audioOutput);

    // 设置音频文件路径（修改这里）
    QString audioPath = "D:\\work\\GreedySnake\\music\\backgroundMusic.mp3.mp3";  // 改成你的音频文件路径

    mediaPlayer->setSource(QUrl::fromLocalFile(audioPath));
    mediaPlayer->setLoops(QMediaPlayer::Infinite);
    mediaPlayer->play();
}

void MainWindow::returnToMainPage()
{
    qDebug() << "returnToMainPage() 槽函数被调用";
    if (startPage) {
        setCentralWidget(startPage);
        qDebug() << "通过槽函数返回主界面成功";
    }
}

// void MainWindow::applyTheme(QString theme)
// {
//     // 简单的主题设置
//     if (theme == "dark") {
//         // 深色主题
//         qApp->setStyleSheet("QMainWindow { background-color: #2b2b2b; color: black; }");
//     } else {
//         // 浅色主题
//         qApp->setStyleSheet("QMainWindow { background-color: #f0f0f0; color: black; }");
//     }
// }
