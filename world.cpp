//
// Created by alexe on 29.03.2021.
//

#include "world.h"

World::World(): winWidth(771), winHeight(675), winTitle("The Tetris"), frameLimit(60),
         window(sf::VideoMode(winWidth, winHeight), winTitle) {
    window.setFramerateLimit(frameLimit);

    tetrisFont.loadFromFile("fonts/tetris-block-regular.ttf");
    backgTexture.loadFromFile("img/TypeA300.png");
    backgTexture.setSmooth(true);
    backgSprite.setTexture(backgTexture);
    mainMusic.openFromFile("snd/tetris-gameboy-02.wav");

    Init();
};

World::World(uint _w, uint _h, std::string _t, uint _f): winWidth(_w), winHeight(_h), winTitle(std::move(_t)),
frameLimit(_f), window(sf::VideoMode(_w, _h), _t) {
    window.setFramerateLimit(_f);

    tetrisFont.loadFromFile("fonts/tetris-block-regular.ttf");
    backgTexture.loadFromFile("img/TypeA300.png");
    backgTexture.setSmooth(true);
    backgSprite.setTexture(backgTexture);
    mainMusic.openFromFile("snd/tetris-gameboy-02.wav");

    Init();
};

void World::drawMap(std::array<std::array<int, constant::W>, constant::H> &_wrld, sf::Sprite &_spr,
                    unsigned int _color) {
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

void World::drawBlock(std::array<Point, constant::SQUARE> _a, sf::Sprite &_spr, unsigned int _color) {
    for (auto & i : _a) {
        _spr.setTextureRect(sf::IntRect(16, 8 * _color, 8, 8));
        _spr.setScale(2, 2);
        _spr.setPosition(constant::TETRA_SIZE * i.x, constant::TETRA_SIZE * i.y);
        _spr.move(constant::MAP_LEFT_EDGE, constant::MAP_UP_EDGE);
        window.draw(_spr);
    }
};

void World::setAllTextSettings(sf::Text &_text, const std::string &_str, sf::Font &_f, sf::Color _c,
                               unsigned int _charSize, float _x, float _y, const sf::Text::Style _style,
                               float _letterSpace) {
    _text.setString(_str);
    _text.setFont(_f);
    _text.setFillColor(_c);
    _text.setCharacterSize(_charSize);
    _text.setPosition(_x, _y); // TETRA_SIZE * 29, TETRA_SIZE * 3.5
    _text.setStyle(_style);
    _text.setLetterSpacing(_letterSpace);
};

void World::setAllTextSettingsV(sf::Text &_text, const std::string &_str, sf::Font &_f, sf::Color _c,
                                unsigned int _charSize, const sf::Vector2f _pos, const sf::Text::Style _style,
                                float _letterSpace) {
    _text.setString(_str);
    _text.setFont(_f);
    _text.setFillColor(_c);
    _text.setCharacterSize(_charSize);
    _text.setPosition(_pos.x, _pos.y); // TETRA_SIZE * 29, TETRA_SIZE * 3.5
    _text.setStyle(_style);
    _text.setLetterSpacing(_letterSpace);
};

void World::Init() {
    sf::Clock clock{};
    sf::Clock rotate_timer{};
    tlModeTimer = sf::seconds(120.f);

    // start game pre-settings block
    setAllTextSettings(mainMenuText, "Main Menu", tetrisFont,
                       sf::Color::White, 16, window.getSize().x / 2 - 100, 140,
                       sf::Text::Style::Bold, 2);

    setAllTextSettings(endGameText, "Game Over!", tetrisFont,
                       sf::Color::White, 16, window.getSize().x / 2 - 100, 140,
                       sf::Text::Style::Bold, 2); // - out  openof

    setAllTextSettings(mainMenuTip, "Use Space to choose", tetrisFont,
                       sf::Color::White, 8, mainMenuText.getPosition().x - 20, mainMenuText.getPosition().y + 40,
                       sf::Text::Style::Bold);

    setAllTextSettings(endGameScoreText, "Your score: " + std::to_string(tetris.getScore()), tetrisFont,
                       sf::Color::White, 14, endGameText.getPosition().x - 20, endGameText.getPosition().y + 40,
                       sf::Text::Style::Bold);

    setAllTextSettings(endGameReplayText, "Replay", tetrisFont,
                       sf::Color::White, 16, endGameText.getPosition().x - 20, endGameText.getPosition().y + 90,
                       sf::Text::Style::Bold, 2); // - out  openof

    playBlock.setOptions("Play TM", "Enter", tetrisFont, gui::blockState::normal, 10, sf::Color::White, 16,
                         mainMenuText.getPosition().x - 90, mainMenuText.getPosition().y + 100, sf::Text::Style::Bold, 2);

    playSecondModeBlock.setOptions("Play TLM", "F2", tetrisFont, gui::blockState::normal, -35, sf::Color::White, 16,
                                   mainMenuText.getPosition().x - 90, mainMenuText.getPosition().y + 150, sf::Text::Style::Bold, 2);

    exitBlock.setOptions("Exit", "Escape", tetrisFont, gui::blockState::normal, 122, sf::Color::White, 16,
                         mainMenuText.getPosition().x - 90, mainMenuText.getPosition().y + 200, sf::Text::Style::Bold, 2);

    creditsBlock.setOptions("Credits", "F1", tetrisFont, gui::blockState::selected, 19, sf::Color::White, 16,
                            mainMenuText.getPosition().x - 90, mainMenuText.getPosition().y + 250, sf::Text::Style::Bold, 2);

    replayThisModeBlock.setOptions("Replay", "Enter", tetrisFont, gui::blockState::selected, 29, sf::Color::White, 16,
                                   endGameText.getPosition().x - 60, endGameText.getPosition().y + 100, sf::Text::Style::Bold, 2);

    goMainMenuBlock.setOptions("Main menu", "F2", tetrisFont, gui::blockState::normal, -68, sf::Color::White, 16,
                               endGameText.getPosition().x - 60, endGameText.getPosition().y + 150, sf::Text::Style::Bold, 2);

    menuOptions[0] = playBlock;
    menuOptions[1] = playSecondModeBlock;
    menuOptions[2] = exitBlock;
    menuOptions[3] = creditsBlock;

    endGameOptions[0] = replayThisModeBlock;
    endGameOptions[1] = goMainMenuBlock;
    endGameOptions[2] = exitBlock;

    // game over pre-settings block
    restartBtn.setPosition(window.getSize().x / 2 - 100, 340);
    restartBtn.setFont(tetrisFont);
    restartBtn.setString("Restart");
    restartBtn.setSize(100, 50);
    restartBtn.setFillColor(sf::Color::White);

    tetris.generateColor();
    while (window.isOpen()) {
        // in this block I try to realize states aka start, play or game over
        if (isStart) { // firstly we check if game is new
            // start game drawing
            clock.restart();

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        for (int i = 0; i < constant::MENU_OPT_C; ++i) {
                            if (i == 0)
                                continue;
                            else if (menuOptions[i].getState() == gui::blockState::selected) {

                                menuOptions[i].setState(gui::blockState::normal);
                                menuOptions[i - 1].setState(gui::blockState::selected);
                                // debug
                                //std::cout << "Up" <<", i = " << i << ",state: " << menuOptions[i].getState() <<
                                //"; i - 1 = " << i - 1 << " state = " << menuOptions[i - 1].getState() << '\n';
                                break;
                            }
                        }
                    } else if (event.key.code == sf::Keyboard::Down) {
                        for (int i = 0; i < constant::MENU_OPT_C; ++i) {
                            if (i == constant::MENU_OPT_C - 1)
                                continue;
                            else if (menuOptions[i].getState() == gui::blockState::selected) {

                                menuOptions[i].setState(gui::blockState::normal);
                                menuOptions[i + 1].setState(gui::blockState::selected);
                                // debug
                                //std::cout << "Down" << ", i = " << i << ",state: " << menuOptions[i].getState() <<
                                //"; i + 1 = " << i + 1 << " state = " << menuOptions[i + 1].getState() << '\n';
                                break;
                            }
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Enter)
                        isStart = false;
                    else if (event.key.code == sf::Keyboard::Escape)
                        Close();
                    else if (event.key.code == sf::Keyboard::F1)
                        continue;
                    else if (event.key.code == sf::Keyboard::F2) {
                        isTLMode = true;
                        isStart = false;
                    }
                    else if (event.key.code == sf::Keyboard::Space)
                        for (int i = 0; i < constant::MENU_OPT_C; ++i) {
                            if (menuOptions[i].getState() == gui::blockState::selected) {
                                switch (i) {
                                    case (0): {
                                        isStart = false;
                                    };
                                        break;
                                    case (1): {
                                        isTLMode = true;
                                        isStart = false;
                                    };
                                        break;
                                    case (2): {
                                        Close();
                                    };
                                        break;
                                    case (3): {
                                    };
                                    default:
                                        break;
                                }
                            }
                        }
                    // Credits();
                }
                else if (event.type == sf::Event::Closed)
                    Close();
            }

            window.clear(sf::Color::Black);
            window.draw(mainMenuText);
            window.draw(mainMenuTip);
            for(auto & el : menuOptions)
                window.draw(el);
            window.display();

        } else if (tetris.checkGameOver()) {
            // game over drawing
            clock.restart();

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        for (int i = 0; i < constant::MENU_OPT_C - 1; ++i) {
                            if (i == 0)
                                continue;
                            else if (endGameOptions[i].getState() == gui::blockState::selected) {

                                endGameOptions[i].setState(gui::blockState::normal);
                                endGameOptions[i - 1].setState(gui::blockState::selected);
                                // debug
                                //std::cout << "Up" <<", i = " << i << ",state: " << endGameOptions[i].getState() <<
                                //"; i - 1 = " << i - 1 << " state = " << endGameOptions[i - 1].getState() << '\n';
                                break;
                            }
                        }
                    } else if (event.key.code == sf::Keyboard::Down) {
                        for (int i = 0; i < constant::MENU_OPT_C - 1; ++i) {
                            if (i == constant::MENU_OPT_C - 2)
                                continue;
                            else if (endGameOptions[i].getState() == gui::blockState::selected) {

                                endGameOptions[i].setState(gui::blockState::normal);
                                endGameOptions[i + 1].setState(gui::blockState::selected);
                                // debug
                                //std::cout << "Down" << ", i = " << i << ",state: " << endGameOptions[i].getState() <<
                                //"; i + 1 = " << i + 1 << " state = " << endGameOptions[i + 1].getState() << '\n';
                                break;
                            }
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Enter) {
                        isStart = false;
                        tetris.setGameOver(false);
                        tetris.Restart();
                    }
                    else if (event.key.code == sf::Keyboard::Escape)
                        Close();
                    else if (event.key.code == sf::Keyboard::F2) {
                        isTLMode = false;
                        isStart = true;
                        tetris.setGameOver(false);
                        tetris.Restart();
                    }
                    else if (event.key.code == sf::Keyboard::Space)
                        for (int i = 0; i < constant::MENU_OPT_C - 1; ++i) {
                            if (endGameOptions[i].getState() == gui::blockState::selected) {
                                switch (i) {
                                    case (0): {
                                        isStart = false;
                                        tetris.setGameOver(false);
                                        tetris.Restart();
                                    };
                                        break;
                                    case (1): {
                                        isTLMode = false;
                                        isStart = true;
                                        tetris.setGameOver(false);
                                        tetris.Restart();
                                    };
                                        break;
                                    case (2): {
                                        Close();
                                    };
                                        break;
                                    default:
                                        break;
                                }
                            }
                        }
                    // Credits();
                }
                else if (event.type == sf::Event::Closed)
                    Close();
            }

            endGameOptions[2].setWordSpacing(158);
            endGameOptions[2].setPosition(endGameText.getPosition().x - 60, endGameText.getPosition().y + 200);
            endGameScoreText.setString("Your score: " + std::to_string(tetris.getScore()));
            window.clear(sf::Color::Black);
            window.draw(endGameText);
            window.draw(endGameScoreText);
            for (auto & el : endGameOptions)
                window.draw(el);
            window.display();
        } else { // playing
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
            if (isTLMode) {
                setAllTextSettings(curTime, std::to_string(tlModeTimer.asSeconds() - clock.getElapsedTime().asSeconds()), tetrisFont,
                                   sf::Color::White, 13, constant::TETRA_SIZE * 36.4, constant::TETRA_SIZE * 3.5,
                                   sf::Text::Style::Bold);
                if (tlModeTimer.asSeconds() - clock.getElapsedTime().asSeconds() <= 0)
                    tetris.setGameOver(true);
            } else {
                setAllTextSettings(curTime, std::to_string(clock.getElapsedTime().asSeconds()), tetrisFont,
                                   sf::Color::White, 13, constant::TETRA_SIZE * 36.4, constant::TETRA_SIZE * 3.5,
                                   sf::Text::Style::Bold);
            }

            for (int i = 0; i < constant::TETRA_TYPES; ++i) {
                setAllTextSettings(statistic[i], std::to_string(tetris.getTetrStat(i)), tetrisFont,
                                   sf::Color::White, 14, constant::TETRA_SIZE * 9.4,
                                   constant::TETRA_SIZE * (17 + 3 * i),
                                   sf::Text::Style::Bold, 3);
            }

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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                tetris.setDelay(0.05f);
                tetris.incBonusScore(1);
                if (tetris.getBonusScore() == 10) {
                    tetris.incCurScoreByDown(1);
                    tetris.setBonusScore(0);
                }
            }

            tetris.LevelUp();
            tetris.Init();
//                if (tetris.checkGameOver()) {
//                    tetris.Restart();
//                    clock.restart();
//                }

            window.clear(sf::Color::White);

            window.draw(backgSprite);
            window.draw(topScoreTxt);
            window.draw(curScoreTxt);
            window.draw(allLines);
            window.draw(curLevel);
            window.draw(curTime);
            for (auto &txt : statistic)
                window.draw(txt);

            // Tetris draw here
            drawMap(tetris.getWrld(), tetris.getCubeSpr(), tetris.getCurColor());
            drawBlock(tetris.getCurCrd(), tetris.getCubeSpr(), tetris.getCurColor());
            window.display();
        }
    }
};

void World::Close() {
    window.close();
}