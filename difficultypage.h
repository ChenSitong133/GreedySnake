// #ifndef DIFFICULTYPAGE_H
// #define DIFFICULTYPAGE_H

// class DifficultyPage
// {
// public:
//     DifficultyPage();
// };

// #endif // DIFFICULTYPAGE_H
#ifndef DIFFICULTYPAGE_H
#define DIFFICULTYPAGE_H

#include <QWidget>

class DifficultyPage : public QWidget
{
    Q_OBJECT
public:
    DifficultyPage(QWidget *parent = nullptr);  // 不要 explicit

signals:
    void difficultySelected(int level);
    void backButtonClicked();
};

#endif // DIFFICULTYPAGE_H
