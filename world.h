//
// Created by alexe on 29.03.2021.
//

#ifndef SFML_TEST_WORLD_H
#define SFML_TEST_WORLD_H
#include <SFML/Audio.hpp>
#include <utility>
#include "tetris.h"
#include "button.h"

typedef unsigned uint;

class World {
public:
    World(): winWidth(771), winHeight(675), winTitle("The Tetris"), frameLimit(60),
    window(sf::VideoMode(winWidth, winHeight), winTitle) {
        window.setFramerateLimit(frameLimit);

        tetrisFont.loadFromFile("fonts/tetris-block-regular.ttf");
        backgTexture.loadFromFile("img/TypeA300.png");
        backgTexture.setSmooth(true);
        backgSprite.setTexture(backgTexture);
        mainMusic.openFromFile("snd/tetris-gameboy-02.wav");

        Init();
    };
    World(uint _w, uint _h, std::string _t, uint _f = 60): winWidth(_w), winHeight(_h), winTitle(std::move(_t)),
    frameLimit(_f), window(sf::VideoMode(_w, _h), _t) {
        window.setFramerateLimit(_f);
        Init();
    }
    ~World() = default;

    void drawMap(std::array<std::array<int ,constant::W>, constant::H>& _wrld, sf::Sprite& _spr, unsigned _color) {
        for (int i = 0; i < constant::H; ++i) {
            for (int j = 0; j < constant::W; ++j) {
                if (_wrld[i][j] == 0)
                    continue;
                _spr.setTextureRect(sf::IntRect(16, 8 * _color, 8, 8));
                _spr.setScale(2, 2);
                _spr.setPosition(constant::TETRA_SIZE * j, constant::TETRA_SIZE * i);
                _spr.move(constant::MAP_LEFT_EDGE, constant::MAP_UP_EDGE);
                window.draw(_spr);
            }
        }
    };
    void drawBlock(std::array<Point, constant::SQUARE> _a, sf::Sprite& _spr, unsigned _color) {
        for (auto & i : _a) {
            _spr.setTextureRect(sf::IntRect(16, 8 * _color, 8, 8));
            _spr.setScale(2, 2);
            _spr.setPosition(constant::TETRA_SIZE * i.x, constant::TETRA_SIZE * i.y);
            _spr.move(constant::MAP_LEFT_EDGE, constant::MAP_UP_EDGE);
            window.draw(_spr);
        }
    };

    static void setAllTextSettings(sf::Text& _text, const std::string& _str, sf::Font& _f,
                            sf::Color _c = sf::Color::Black, unsigned _charSize = 10, float _x = 0,
                            float _y = 0, const sf::Text::Style _style = sf::Text::Style::Regular, float _letterSpace = 1.f) {
        _text.setString(_str);
        _text.setFont(_f);
        _text.setFillColor(_c);
        _text.setCharacterSize(_charSize);
        _text.setPosition(_x, _y); // TETRA_SIZE * 29, TETRA_SIZE * 3.5
        _text.setStyle(_style);
        _text.setLetterSpacing(_letterSpace);
    }

    static void setAllTextSettingsV(sf::Text& _text, const std::string& _str, sf::Font& _f,
                            sf::Color _c = sf::Color::Black, unsigned _charSize = 10, const sf::Vector2f _pos = {0, 0},
                            const sf::Text::Style _style = sf::Text::Style::Regular, float _letterSpace = 1.f) {
        _text.setString(_str);
        _text.setFont(_f);
        _text.setFillColor(_c);
        _text.setCharacterSize(_charSize);
        _text.setPosition(_pos.x, _pos.y); // TETRA_SIZE * 29, TETRA_SIZE * 3.5
        _text.setStyle(_style);
        _text.setLetterSpacing(_letterSpace);
    }

    void Init() {
        sf::Clock clock{};
        sf::Clock rotate_timer{};

        tetris.generateColor();
        while (window.isOpen()) {
            // setting text
            setAllTextSettings(topScoreTxt, std::to_string(tetris.getTopScore()), tetrisFont,
                               sf::Color::White, 14, constant::TETRA_SIZE * 36.8, constant::TETRA_SIZE * 6.5,
                               sf::Text::Style::Bold, 3);
            setAllTextSettings(curScoreTxt, std::to_string(tetris.getScore()), tetrisFont,
                               sf::Color::White, 14, constant::TETRA_SIZE * 36.4, constant::TETRA_SIZE * 11,
                               sf::Text::Style::Bold, 3);
            setAllTextSettings(allLines, std::to_string(tetris.getLines()), tetrisFont,
                               sf::Color::White, 14, constant::TETRA_SIZE * 29, constant::TETRA_SIZE * 3.5,
                               sf::Text::Style::Bold, 4);
            setAllTextSettings(curLevel, std::to_string(tetris.getLevel()), tetrisFont,
                               sf::Color::White, 14, constant::TETRA_SIZE * 39.6, constant::TETRA_SIZE * 30.5,
                               sf::Text::Style::Bold, 4);
            setAllTextSettings(curTime, std::to_string(clock.getElapsedTime().asSeconds()), tetrisFont,
                               sf::Color::White, 13, constant::TETRA_SIZE * 36.4, constant::TETRA_SIZE * 3.5,
                               sf::Text::Style::Bold);

            // time to rotate tetramino
            float time = rotate_timer.getElapsedTime().asSeconds();
            rotate_timer.restart();
            tetris.incTimer(time);

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    Close();
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up)
                        tetris.setRotate(true);
                    else if (event.key.code == sf::Keyboard::Left)
                        tetris.setDx(int(-1));
                    else if (event.key.code == sf::Keyboard::Right)
                        tetris.setDx(int(1));
                }
            }

            // speed up tetramino
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                tetris.setDelay(0.05f);

            tetris.LevelUp();
            tetris.Init();
            if (tetris.checkGameOver())
                Close();

            window.clear(sf::Color::White);

            window.draw(backgSprite);
            window.draw(topScoreTxt);
            window.draw(curScoreTxt);
            window.draw(allLines);
            window.draw(curLevel);
            window.draw(curTime);

            // Tetris draw here
            drawMap(tetris.getWrld(), tetris.getCubeSpr(), tetris.getCurColor());
            drawBlock(tetris.getCurCrd(), tetris.getCubeSpr(), tetris.getCurColor());
            window.display();
        }
    };
    void Close() {
        window.close();
    };
private:
    // window set block
    uint winWidth;
    uint winHeight;
    uint frameLimit;
    std::string winTitle;

    // SFML block
    sf::RenderWindow window{};
    sf::Event event{};
    sf::Texture backgTexture;
    sf::Sprite backgSprite;
    sf::Music mainMusic;
    sf::Font tetrisFont;
    sf::Text topScoreTxt;
    sf::Text curScoreTxt;
    sf::Text allLines;
    sf::Text curLevel;
    sf::Text curTime;
    Tetris tetris{};

    // gui block
    gui::Button button{};
};

#endif //SFML_TEST_WORLD_H
