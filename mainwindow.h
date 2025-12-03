#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "page/MiddlePage.h"
#pragma once


#include <QMainWindow>
#include "page/StartPage.h"
#include "page/GamePage.h"
#include "page/MiddlePage.h"
#include <QStackedWidget>
#include <QFile>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    StartPage* startPage;
    GamePage* gamePage;
    MiddlePage* middlePage;

    QStackedWidget* stackedWidget;

    int FPS = 100;

    void initUI();
    void initConnections();
    void applyTheme(QString theme);

};
#endif // MAINWINDOW_H
