//
// Created by alexe on 29.03.2021.
//

#include "tetris.h"

Tetris::Tetris() {
    texture.loadFromFile("img/titles.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(16, 8 * curColor, 8, 8));
    sprite.setScale(2, 2);

    //Init();
}

bool Tetris::checkWrld(std::array<Point, constant::SQUARE> &_a) {
    for (int i = 0; i < constant::SQUARE; ++i) {
        if (_a[i].x < 0 || _a[i].x >= constant::W || _a[i].y >= constant::H || worldMap[_a[i].y][_a[i].x])  {
            return false;
        }
    }
    return true;
//    return std::all_of(_a.cbegin(), _a.cend(), [this](Point i){
//        return !(i.x < 0 || i.x > constant::W || i.y > constant::H || worldMap[i.y][i.x]);
//    });
};

bool Tetris::checkGameOver() {
    for (int i = 0; i < constant::W; ++i) {
        if (worldMap[1][i])
            return true;
    }
    return false;
}

void Tetris::checkLine() {
    int k = constant::H - 1;
    int lines_in_row_counter = 0;
    for (int i = k; i > 0; --i) {
        int count = 0;
        for (int j = 0; j < constant::W; ++j) {
            if (worldMap[i][j])
                ++count;
            worldMap[k][j] = worldMap[i][j];
        }
        if (count < constant::W)
            --k;
        else
            ++lines_in_row_counter;
    }
    setScore(lines_in_row_counter);
}

void Tetris::setScore(int _lc) { // pass count of lines
    oldScore = curScore;
    if (_lc > 1)
        curScore += (_lc + (multiplier * _lc)) * constant::LINE_SCORE;
    else if (_lc == 1)
        curScore += constant::LINE_SCORE;
    linesCounter += _lc;
    curScore > topScore ? topScore = curScore : topScore;
}

int Tetris::getScore() const {
    return curScore;
}

int Tetris::getTopScore() const {
    return topScore;
}

unsigned int Tetris::getLevel() const {
    return curLevel;
}

unsigned int Tetris::getLines() const {
    return linesCounter;
}

void Tetris::setDelay(float _d) {
    delay = _d;
}

void Tetris::setDuration(float _d) {
    duration = _d;
}

void Tetris::incDuration(float _d) {
    duration += _d;
}

void Tetris::incTimer(float _t) {
    timer += _t;
}

void Tetris::setDx(int _dx) {
    dx = _dx;
}

void Tetris::setDy(int _dy) {
    dy = _dy;
}

void Tetris::setRotate(bool _r) {
    rotate = _r;
}

void Tetris::firstMove() {
    isFirst = false;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> typeDist(0, 6);
    curType = typeDist(mt);
    ++tetrCounter[curType];
    for (int i = 0; i < constant::SQUARE; ++i) {
        curCrd[i].x = tetramino[curType][i] % 2;
        curCrd[i].y = tetramino[curType][i] / 2;
    }
}

void Tetris::Move() {
    for (int i = 0; i < constant::SQUARE; ++i) {
        oldCrd[i] = curCrd[i];
        curCrd[i].x += dx;
    }
}

void Tetris::Rotate() {
    // 1 - is a rotation center
    Point p = curCrd[1];
    for (auto & i : curCrd) {
        int x = i.y - p.y;
        int y = i.x - p.x;
        i.x = p.x - x;
        i.y = p.y + y;
    }
    if (!checkWrld(curCrd)) {
        for (int i = 0; i < constant::SQUARE; ++i)
            curCrd[i] = oldCrd[i];
    }
}

void Tetris::Generate() {
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> typeDist(0, 6);
    //std::uniform_int_distribution<int> colorDist(0, 6);
    curType = typeDist(mt);
    //curColor = colorDist(mt);
}

void Tetris::LevelUp() {
    if (curScore / 1000 > oldScore / 1000) {
        delay -= 0.05f;
        ++curLevel;
        generateColor();
    }
}

void Tetris::generateColor() {
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> colorDist(1, 5);
    curColor = colorDist(mt);
}

void Tetris::Init() {
    // movement
    Move();

    // check on edges
    if (!checkWrld(curCrd)) {
        for (int i = 0; i < constant::SQUARE; ++i)
            curCrd[i] = oldCrd[i];
    }

    // rotation
    if (rotate)
        Rotate();

    // generate type of cur tetramino and cur color
    Generate();

    // not clear code
    if (timer > delay) {
        //++tetramino_counter[n];
        for (int i = 0; i < constant::SQUARE; ++i) {
            oldCrd[i] = curCrd[i];
            curCrd[i].y += 1;
        }
        if (!checkWrld(curCrd)) {
            //++tetramino_counter[n];
            for (auto & i : oldCrd)
                worldMap[i.y][i.x] = curColor;
            //generateColor();
            for (int i = 0; i < constant::SQUARE; ++i) {
                curCrd[i].x = tetramino[curType][i] % 2;
                curCrd[i].y = tetramino[curType][i] / 2;
            }
        }
        timer = 0;
    }

    // check for full line and set score if destroy
    checkLine();

    // if firstMove and then zero
    if (isFirst)
        firstMove();

    dx = 0;
    rotate = false;
    delay = 0.3;

}
