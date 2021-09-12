#ifndef PACMAN_GAMEWIDGET_H
#define PACMAN_GAMEWIDGET_H


#include <QWidget>
#include <QtGui>
#include <QLabel>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QGraphicsRectItem>
#include <vector>
#include <QPushButton>

#include "pacman/PacmanItem.h"
#include "Ghosts/SimpleGhost.h"
#include "MapGenerator.h"
#include "Timer.h"
#include "Algorithms.h"

using namespace std;

class GameWidget : public QWidget {
Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);

    void drawMap();

    ~GameWidget();

protected:

    void keyPressEvent(QKeyEvent *event) override;

private slots:

    void clock();

    void startNewGame();

private:
    int biscuit;
    int wall;
    int empty;
    int block;
    int pill;
    int score;
    int lives;
    QLabel *scoreText;
    QLabel *result;
    QLabel *livesText;
    QTimer timer;

    vector<vector<int>> map;
    vector<QGraphicsItem *> biscuitTextures;

    vector<QGraphicsItem *> dfsPath;

    QGraphicsScene *scene;
    QGraphicsView *view;
    QVBoxLayout *mainLayout;
    QPushButton *newGameBut;

    PacmanItem *pacmanTexture;
    SimpleGhost *blinky;
    SimpleGhost *pinky;
    SimpleGhost *inky;
    SimpleGhost *clyde;

};


#endif //PACMAN_GAMEWIDGET_H
