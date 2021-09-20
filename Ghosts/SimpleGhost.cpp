#include "SimpleGhost.h"

SimpleGhost::SimpleGhost() {
    ghostTextureLeft.load("../images/blinkyLeft.png");
    ghostTextureRight.load("../images/blinkyRight.png");
    ghostTextureTop.load("../images/blinkyTop.png");
    ghostTextureBottom.load("../images/blinkyBottom.png");
    direction = 0;
    prevDirection = 0;
}

QRectF SimpleGhost::boundingRect() const {
    return {0, 0, 20, 20};
}

void SimpleGhost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (direction == 1) {
        painter->drawImage(0, 0, ghostTextureLeft);
    } else if (direction == 2) {
        painter->drawImage(0, 0, ghostTextureRight);
    } else if (direction == 3) {
        painter->drawImage(0, 0, ghostTextureTop);
    } else {
        painter->drawImage(0, 0, ghostTextureBottom);
    }
}

QPoint SimpleGhost::move(vector<vector<int>> &map, QPoint pacmanPos) {
    double x = (pos().x() + 10) / 20;
    double y = (pos().y() + 10) / 20;

    int speed = 5;

    // tunnel for main map
//    if ((int) x == -1 and (int) y == 14 and direction == 1) {
//        setPos(28 * 20, 14 * 20);
//    }
//    if ((int) x == 28 and (int) y == 14 and direction == 2) {
//        setPos(-1 * 20, 14 * 20);
//    }

    // tunnel
    if ((int) x == -1 and (int) y == 15 and direction == 1) {
        setPos(28 * 20, 15 * 20);
    }
    if ((int) x == 28 and (int) y == 15 and direction == 2) {
        setPos(-1 * 20, 15 * 20);
    }

    Movement::moveItem(this, x, y, direction, map, speed, true);

    x = (pos().x() + 10) / 20;
    y = (pos().y() + 10) / 20;

    if (x - (int) x == 0.5 && y - (int) y == 0.5) {
//        if (direction == 0) {
//            if (prevDirection != 0) {
//                vector<int> dirs = {1, 2, 3, 4};
//                if (prevDirection == 1) {
//                    dirs.erase(remove(dirs.begin(), dirs.end(), 2), dirs.end());
//                    dirs.erase(remove(dirs.begin(), dirs.end(), 1), dirs.end());
//                } else if (prevDirection == 2) {
//                    dirs.erase(remove(dirs.begin(), dirs.end(), 2), dirs.end());
//                    dirs.erase(remove(dirs.begin(), dirs.end(), 1), dirs.end());
//                } else if (prevDirection == 3) {
//                    dirs.erase(remove(dirs.begin(), dirs.end(), 4), dirs.end());
//                    dirs.erase(remove(dirs.begin(), dirs.end(), 3), dirs.end());
//                } else if (prevDirection == 4) {
//                    dirs.erase(remove(dirs.begin(), dirs.end(), 4), dirs.end());
//                    dirs.erase(remove(dirs.begin(), dirs.end(), 3), dirs.end());
//                }
//                for (int dir: dirs) {
//                    if (dir == 1) {
//                        if (Movement::checkLeftBlock(x, y, map, 0.6, true)) {
//                            dirs.erase(remove(dirs.begin(), dirs.end(), 1), dirs.end());
//                        }
//                    } else if (dir == 2) {
//                        if (Movement::checkRightBlock(x, y, map, 0.6, true)) {
//                            dirs.erase(remove(dirs.begin(), dirs.end(), 2), dirs.end());
//                        }
//                    } else if (dir == 3) {
//                        if (Movement::checkTopBlock(x, y, map, 0.6, true)) {
//                            dirs.erase(remove(dirs.begin(), dirs.end(), 3), dirs.end());
//                        }
//                    } else if (dir == 4) {
//                        if (Movement::checkBottomBlock(x, y, map, 0.6, true)) {
//                            dirs.erase(remove(dirs.begin(), dirs.end(), 4), dirs.end());
//                        }
//                    }
//                }
//                auto rd = std::random_device{};
//                auto rng = default_random_engine{rd()};
//                shuffle(dirs.begin(), dirs.end(), rng);
//                direction = dirs[0];
//            }
//        } else if (direction == 1) {
//            vector<int> dirs = {1};
//            if (!Movement::checkTopBlock(x, y, map, 0.6, true)) {
//                dirs.push_back(3);
//            }
//            if (!Movement::checkBottomBlock(x, y, map, 0.6, true)) {
//                dirs.push_back(4);
//            }
//            auto rd = std::random_device{};
//            auto rng = default_random_engine{rd()};
//            shuffle(dirs.begin(), dirs.end(), rng);
//            direction = dirs[0];
//        } else if (direction == 2) {
//            vector<int> dirs = {2};
//            if (!Movement::checkTopBlock(x, y, map, 0.6, true)) {
//                dirs.push_back(3);
//            }
//            if (!Movement::checkBottomBlock(x, y, map, 0.6, true)) {
//                dirs.push_back(4);
//            }
//            auto rd = std::random_device{};
//            auto rng = default_random_engine{rd()};
//            shuffle(dirs.begin(), dirs.end(), rng);
//            direction = dirs[0];
//        } else if (direction == 3) {
//            vector<int> dirs = {3};
//            if (!Movement::checkLeftBlock(x, y, map, 0.6, true)) {
//                dirs.push_back(1);
//            }
//            if (!Movement::checkRightBlock(x, y, map, 0.6, true)) {
//                dirs.push_back(2);
//            }
//            auto rd = std::random_device{};
//            auto rng = default_random_engine{rd()};
//            shuffle(dirs.begin(), dirs.end(), rng);
//            direction = dirs[0];
//        } else if (direction == 4) {
//            vector<int> dirs = {4};
//            if (!Movement::checkLeftBlock(x, y, map, 0.6, true)) {
//                dirs.push_back(1);
//            }
//            if (!Movement::checkRightBlock(x, y, map, 0.6, true)) {
//                dirs.push_back(2);
//            }
//            auto rd = std::random_device{};
//            auto rng = default_random_engine{rd()};
//            shuffle(dirs.begin(), dirs.end(), rng);
//            direction = dirs[0];
//        }
        if (!(direction == 0 && prevDirection == 0)) {
            Algorithms alg;
            vector<pair<int, int>> path;
            path = alg.bfsForGhosts((int) x, (int) y, pacmanPos.x(), pacmanPos.y(), map, direction);
            if (!path.empty()) {
                if ((int) x - path[path.size() - 1].first == -1) {
                    direction = 2;
                } else if ((int) x - path[path.size() - 1].first == 1) {
                    direction = 1;
                } else if ((int) y - path[path.size() - 1].second == -1) {
                    direction = 4;
                } else if ((int) y - path[path.size() - 1].second == 1) {
                    direction = 3;
                }
            }
        }
    }
    if (direction != 0) {
        prevDirection = direction;
    }

    return {(int) x, (int) y};
}

void SimpleGhost::setDirection(int newDirection) {
    direction = newDirection;
}

SimpleGhost::~SimpleGhost() = default;
