//
// Created by alexe on 29.03.2021.
//

#ifndef SFML_TEST_WORLD_H
#define SFML_TEST_WORLD_H
#include <SFML/Audio.hpp>
#include <iostream>
#include <utility>
#include "tetris.h"
#include "button.h"
#include "text_block.h"
#include "credits.h"

typedef unsigned uint;

class World {
public:
    World();
    World(uint _w, uint _h, std::string _t, uint _f = 60);
    ~World() = default;

    void drawMap(std::array<std::array<int ,constant::W>, constant::H>& _wrld, sf::Sprite& _spr, unsigned _color);
    void drawBlock(std::array<Point, constant::SQUARE> _a, sf::Sprite& _spr, unsigned _color);

    static void setAllTextSettings(sf::Text& _text, const std::string& _str, sf::Font& _f,
                            sf::Color _c = sf::Color::Black, unsigned _charSize = 10, float _x = 0,
                            float _y = 0, const sf::Text::Style _style = sf::Text::Style::Regular, float _letterSpace = 1.f);

    static void setAllTextSettingsV(sf::Text& _text, const std::string& _str, sf::Font& _f,
                            sf::Color _c = sf::Color::Black, unsigned _charSize = 10, const sf::Vector2f _pos = {0, 0},
                            const sf::Text::Style _style = sf::Text::Style::Regular, float _letterSpace = 1.f);

    void Init();
    void Close();
private:
    // window set block
    uint winWidth;
    uint winHeight;
    uint frameLimit;
    std::string winTitle;
    bool isStart = true; // state of world, not tetris
    bool isTLMode = false; // game mode controlled by world
    bool isCredits = false;

    // SFML block
    sf::RenderWindow window{};
    sf::Event event{};
    sf::Texture backgTexture;
    sf::Texture endGameBckTexture;
    sf::Sprite backgSprite;
    sf::Sprite endGameBckSprite;
    sf::Music mainMusic;
    sf::Music endGameMusic;
    sf::Font tetrisFont;
    sf::Text topScoreTxt;
    sf::Text curScoreTxt;
    sf::Text allLines;
    sf::Text curLevel;
    sf::Text curTime;
    sf::Text endGameText;
    sf::Text endGameScoreText;
    sf::Text endGameReplayText;
    sf::Text mainMenuText;
    sf::Text mainMenuTip;
    sf::Time tlModeTimer;
    std::array<sf::Text, constant::TETRA_TYPES> statistic;
    std::array<gui::TextBlock, constant::MENU_OPT_C> menuOptions;
    std::array<gui::TextBlock, constant::MENU_OPT_C - 1> endGameOptions;
    Tetris tetris{};

    // gui block
    gui::Button restartBtn{};
    gui::Button quitBtn{};
    gui::Credits credits{};
    gui::TextBlock playBlock{};
    gui::TextBlock creditsBlock{};
    gui::TextBlock exitBlock{};
    gui::TextBlock playSecondModeBlock{};
    gui::TextBlock goMainMenuBlock{};
    gui::TextBlock replayThisModeBlock{};
};

#endif //SFML_TEST_WORLD_H
