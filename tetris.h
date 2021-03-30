//
// Created by alexe on 29.03.2021.
//

#ifndef SFML_TEST_TETRIS_H
#define SFML_TEST_TETRIS_H
#include <array>
#include <random>
#include "button.h"

namespace constant {
    const int TETRA_SIZE = 16; // in px
    const int SQUARE = 4; // sizeof 1 tetramino in blocks
    const int H = 30; // height in blocks
    const int W = 15; // width in blocks
    const int MAP_LEFT_EDGE = 288; // in px
    const int MAP_UP_EDGE = 120; // in px
    const int TEXT_OFFSET = 272; // in px
    const int LINE_SCORE = 1000;
}

struct Point {
    Point(): x{0}, y{0} {};
    int x;
    int y;
};

class Tetris {
public:
    Tetris();
    ~Tetris() = default;

    bool checkWrld(std::array<Point, constant::SQUARE>& _a);
    bool checkGameOver();
    void checkLine();
    void setScore(int);
    int getScore() const;
    int getTopScore() const;
    unsigned getLevel() const;
    unsigned getLines() const;
    void setDelay(float);
    void setDuration(float);
    void incDuration(float);
    void incTimer(float);
    void setDx(int);
    void setDy(int);
    void setRotate(bool);
    void generateColor();

    std::array<std::array<int ,constant::W>, constant::H>& getWrld() {
        return worldMap;
    }

    std::array<Point, constant::SQUARE>& getCurCrd() {
        return curCrd;
    }

    unsigned getCurColor() const {
        return curColor;
    }

    sf::Sprite& getCubeSpr() {
        return sprite;
    }

    void Init();
    void Move();
    void firstMove();
    void Rotate();
    void Generate();
    void LevelUp();
    void Pause();
    void Unpause();
    void Restart();
    void Close();
private:
    sf::Texture texture;
    sf::Sprite sprite;

    std::array<std::array<int ,constant::W>, constant::H> worldMap = {0};
    std::array<std::array<const int, constant::SQUARE>, 7> tetramino = {
            1, 3, 5, 7, // I
            2, 4, 5, 7, // Z
            3, 5, 4, 6, // S
            3, 5, 4, 7, // T
            2, 3, 5, 7, // L
            3, 5, 7, 6, // J
            2, 3, 4, 5, // O
    };
    std::array<int, 7> tetrCounter = {0};
    std::array<Point, constant::SQUARE> curCrd;
    std::array<Point, constant::SQUARE> oldCrd;
    std::random_device rd;
    int dx = 0;
    int dy = 0;
    int topScore = 10000;
    int curScore = 0;
    int oldScore = 0;
    unsigned linesCounter = 0;
    unsigned curLevel = 1;
    unsigned curType = 1;
    unsigned curColor = 1;
    float timer = 0; // = 0
    float delay = 0.5f; // = 0.3f;
    float duration = 0;
    double multiplier = 0.2; // = 0.2;
    bool rotate = false; // = false;
    bool isFirst = true; // = true;
};

#endif //SFML_TEST_TETRIS_H
