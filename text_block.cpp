//
// Created by alexe on 01.04.2021.
//

#include "text_block.h"

void gui::TextBlock::setOptString(const std::string& _opt) {
    opt.setString(_opt);
}

void gui::TextBlock::setKeyString(const std::string& key_) {
    key.setString(key_);
}

void gui::TextBlock::setFont(sf::Font& _f) {
    opt.setFont(_f);
    key.setFont(_f);
}

void gui::TextBlock::setCharSize(unsigned _size) {
    opt.setCharacterSize(_size);
    key.setCharacterSize(_size);
}

void gui::TextBlock::setFillColor(sf::Color& _c) {
    opt.setFillColor(_c);
    key.setFillColor(_c);
}

void gui::TextBlock::setTextStyle(sf::Text::Style _style) {
    opt.setStyle(_style);
    key.setStyle(_style);
}

void gui::TextBlock::setLetterSpacing(float _space) {
    opt.setLetterSpacing(_space);
    key.setLetterSpacing(_space);
}

void gui::TextBlock::setWordSpacing(float space_) {
    wordSpace = space_;
    key.setPosition(opt.getGlobalBounds().width + wordSpace, opt.getPosition().y);
}

void gui::TextBlock::setPosition(float x_, float y_) {
    opt.setPosition(x_, y_);
    key.setPosition(opt.getGlobalBounds().width + x_ + wordSpace, y_);
}

void gui::TextBlock::setState(sf::Uint32 state_) {
    state = state_;
    switch (state) {
        case (gui::blockState::normal): {
            color = sf::Color(255, 255, 255);
        }
            break;
        case (gui::blockState::selected): {
            color = sf::Color(149, 149, 149);
        }
            break;
    }
    opt.setFillColor(color);
    key.setFillColor(color);
}

void gui::TextBlock::setOptions(const std::string& opt_, const std::string& key_, sf::Font& f_, sf::Uint32 state_,
                float wordSpacing_ = 10, sf::Color c_ = sf::Color::White, unsigned charSize_ = 10, float x_ = 0,
                float y_ = 0, const sf::Text::Style style_ = sf::Text::Style::Regular, float letterSpace_ = 1.f) {
    this->setOptString(opt_);
    this->setKeyString(key_);
    this->setFont(f_);
    this->setWordSpacing(wordSpacing_);
    this->setPosition(x_, y_);
    this->setFillColor(c_);
    this->setState(state_);
    this->setCharSize(charSize_);
    this->setLetterSpacing(letterSpace_);
    this->setTextStyle(style_);
}

sf::Uint32 gui::TextBlock::getState() const {
    return state;
}

void gui::TextBlock::update(sf::Event& e, sf::RenderWindow& window) {
    switch (state) {
        case (gui::blockState::normal): {
            //this->setState(gui::blockState::selected);
            this->setState(gui::blockState::normal);
        }
            break;
        case (gui::blockState::selected): {
            //this->setState(gui::blockState::normal);
            this->setState(gui::blockState::selected);
        }
            break;
        default:
            break;
    }
}

void gui::TextBlock::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    switch (state) {
        case (gui::blockState::normal): {
            target.draw(opt, states);
            target.draw(key, states);
        }
            break;
        case (gui::blockState::selected): {
            target.draw(opt, states);
            target.draw(key, states);
        }
            break;
        default:
            break;
    };
}