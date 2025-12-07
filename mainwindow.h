<<<<<<< HEAD
// #ifndef MAINWINDOW_H
// #define MAINWINDOW_H
// #include "page/MiddlePage.h"
// #include "page/RankingPage.h"
// #pragma once


// #include <QMainWindow>
// #include "page/StartPage.h"
// #include "page/GamePage.h"
// #include "page/MiddlePage.h"
// #include "page/SettingPage.h"
// #include "page/RankingPage.h"
// #include <QStackedWidget>
// #include <QFile>
// #include <QUrl>
// #include <QMediaPlayer>

// // #include <QMediaPlaylist>

// class MainWindow : public QMainWindow
// {
//     Q_OBJECT

// public:
//     MainWindow(QWidget *parent = nullptr);
//     ~MainWindow();

// private:
//     StartPage* startPage;
//     GamePage* gamePage;
//     SettingPage* settingPage;
//     RankingPage* rankingPage;
//     MiddlePage* middlePage;
//     QStackedWidget* stackedWidget;

//     // QMediaPlayer* mediaPlayer;

//     int FPS = 100;

//     void initUI();
//     void initConnections();
//     void applyTheme(QString theme);
//     // void initMediaPlayer();
// };
// #endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>

#include "page/StartPage.h"
#include "page/SettingPage.h"
#include "page/RankingPage.h"
#include "page/GamePage.h"
#include "page/MiddlePage.h"
#include "page/DifficultyPage.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:  // 添加这个部分
    void returnToMainPage();  // 添加这个槽函数

private:
    void setupConnections();
    void setupAudio();
    void applyTheme(QString theme);

    // 页面指针
    StartPage *startPage;
    SettingPage *settingPage;
    RankingPage *rankingPage;
    GamePage *gamePage;
    MiddlePage *middlePage;
    DifficultyPage*difficultyPage;
    // 音频播放相关成员
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;
};

#endif // MAINWINDOW_H
=======
// #ifndef MAINWINDOW_H
// #define MAINWINDOW_H
// #include "page/MiddlePage.h"
// #include "page/RankingPage.h"
// #pragma once


// #include <QMainWindow>
// #include "page/StartPage.h"
// #include "page/GamePage.h"
// #include "page/MiddlePage.h"
// #include "page/SettingPage.h"
// #include "page/RankingPage.h"
// #include <QStackedWidget>
// #include <QFile>
// #include <QUrl>
// #include <QMediaPlayer>

// // #include <QMediaPlaylist>

// class MainWindow : public QMainWindow
// {
//     Q_OBJECT

// public:
//     MainWindow(QWidget *parent = nullptr);
//     ~MainWindow();

// private:
//     StartPage* startPage;
//     GamePage* gamePage;
//     SettingPage* settingPage;
//     RankingPage* rankingPage;
//     MiddlePage* middlePage;
//     QStackedWidget* stackedWidget;

//     // QMediaPlayer* mediaPlayer;

//     int FPS = 100;

//     void initUI();
//     void initConnections();
//     void applyTheme(QString theme);
//     // void initMediaPlayer();
// };
// #endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>

#include "page/StartPage.h"
#include "page/SettingPage.h"
#include "page/RankingPage.h"
#include "page/GamePage.h"
#include "page/MiddlePage.h"
#include "page/DifficultyPage.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:  // 添加这个部分
    void returnToMainPage();  // 添加这个槽函数

private:
    void setupConnections();
    void setupAudio();
    void applyTheme(QString theme);

    // 页面指针
    StartPage *startPage;
    SettingPage *settingPage;
    RankingPage *rankingPage;
    GamePage *gamePage;
    MiddlePage *middlePage;
    DifficultyPage*difficultyPage;
    // 音频播放相关成员
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;
};

#endif // MAINWINDOW_H
>>>>>>> 74d44026d6f82ef9737241204da208c96f924eda
