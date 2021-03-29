//
// Created by alexe on 27.03.2021.
//

#include "button.h"

gui::Button::Button(std::string _s, sf::Font &_f, sf::Vector2f _pos, sf::Uint32 _style) {
    m_pos = _pos;
    m_state = gui::state::normal;
    m_style = _style;

    switch (m_style) {
        case gui::style::none:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(255,255,255,100);
            m_bgHover = sf::Color(200,200,200,100);
            m_bgClicked = sf::Color(150,150,150);
            m_border = sf::Color(255,255,255,100);
        }
            break;
        case gui::style::save:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(0,255,0,100);
            m_bgHover = sf::Color(0,200,0,100);
            m_bgClicked = sf::Color(0,150,0);
            m_border = sf::Color(0,0,0,100);
        }
            break;
        case gui::style::cancel:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(255,0,0,100);
            m_bgHover = sf::Color(200,0,0,100);
            m_bgClicked = sf::Color(150,0,0);
            m_border = sf::Color(255,255,255,100);
        }
            break;
        case gui::style::clean:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(0,255,255,100);
            m_bgHover = sf::Color(0,200,200,100);
            m_bgClicked = sf::Color(0,150,150);
            m_border = sf::Color(255,255,255,100);
        }
            break;
        default:
            break;
    }

    m_text.setString(_s);
    m_text.setFont(_f);
    m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
    m_text.setFillColor(m_textNormal);

    m_borderRadius = 5.f;
    m_borderThickness = 0.f;
    m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.5f);
    // possible errors
    b_rec_shape = sf::RectangleShape(m_size);
    b_rec_shape.setFillColor(m_bgNormal);
    b_rec_shape.setOutlineThickness(m_borderThickness);
    b_rec_shape.setOutlineColor(m_border);

    sf::Vector2f textPosition = sf::Vector2f(b_rec_shape.getPosition().x,
                                             b_rec_shape.getPosition().y - b_rec_shape.getGlobalBounds().height/4);

    m_text.setPosition(textPosition);

    m_shadow.setFont(font);
    m_shadow = m_text;
    m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
    m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
}

void gui::Button::setSize(unsigned _size)
{
    m_font_size = _size;
    m_text.setCharacterSize(m_font_size);
    m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
    m_shadow.setCharacterSize(m_font_size);
    m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
    m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, (m_text.getGlobalBounds().height + m_text.getGlobalBounds().height) * 1.5f);
    b_rec_shape = sf::RectangleShape(m_size);
    b_rec_shape.setFillColor(m_bgNormal);
    b_rec_shape.setOutlineThickness(m_borderThickness);
    b_rec_shape.setOutlineColor(m_border);
}

void gui::Button::setStyle(sf::Uint32 style)
{
    //set button style
    m_style = style;

    switch(m_style)
    {
        case gui::style::none:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(255,255,255,100);
            m_bgHover = sf::Color(200,200,200,100);
            m_bgClicked = sf::Color(150,150,150);
            m_border = sf::Color(255,255,255,100);
        }
            break;

        case gui::style::save:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(0,255,0,100);
            m_bgHover = sf::Color(0,200,0,100);
            m_bgClicked = sf::Color(0,150,0);
            m_border = sf::Color(0,0,0,100);
        }
            break;

        case gui::style::cancel:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(255,0,0,100);
            m_bgHover = sf::Color(200,0,0,100);
            m_bgClicked = sf::Color(150,0,0);
            m_border = sf::Color(255,255,255,100);
        }
            break;

        case gui::style::clean:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(0,255,255,100);
            m_bgHover = sf::Color(0,200,200,100);
            m_bgClicked = sf::Color(0,150,150);
            m_border = sf::Color(255,255,255,100);
        }
            break;

        default:
            break;
    }
}

void gui::Button::setFont(sf::Font& font)
{
    m_text.setFont(font);
    m_shadow.setFont(font);
}

void gui::Button::update(sf::Event& e, sf::RenderWindow& window)
{
    //perform updates for settings from user
    switch(m_style)
    {
        case gui::style::none:
        {
            m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
            b_rec_shape = sf::RectangleShape(m_size);
            b_rec_shape.setFillColor(m_bgNormal);
            b_rec_shape.setOutlineThickness(m_borderThickness);
            b_rec_shape.setOutlineColor(m_border);
            b_rec_shape.setOrigin(b_rec_shape.getGlobalBounds().width/2, b_rec_shape.getGlobalBounds().height/2);
            b_rec_shape.setPosition(m_pos);
            m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
            sf::Vector2f textPosition = sf::Vector2f(b_rec_shape.getPosition().x, b_rec_shape.getPosition().y - b_rec_shape.getGlobalBounds().height/4);
            m_text.setPosition(textPosition);
            m_text.setFillColor(m_textNormal);
            m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
            m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
            m_shadow.setFillColor(sf::Color(0,0,0));
        }
            break;

        case gui::style::save:
        {
            m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
            b_rec_shape = sf::RectangleShape(m_size);
            b_rec_shape.setFillColor(m_bgNormal);
            b_rec_shape.setOutlineThickness(m_borderThickness);
            b_rec_shape.setOutlineColor(m_border);
            b_rec_shape.setOrigin(b_rec_shape.getGlobalBounds().width/2, b_rec_shape.getGlobalBounds().height/2);
            b_rec_shape.setPosition(m_pos);
            m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
            sf::Vector2f textPosition = sf::Vector2f(b_rec_shape.getPosition().x, b_rec_shape.getPosition().y - b_rec_shape.getGlobalBounds().height/4);
            m_text.setPosition(textPosition);
            m_text.setFillColor(m_textNormal);
            m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
            m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
            m_shadow.setFillColor(sf::Color(0,0,0));
        }
            break;

        case gui::style::cancel:
        {
            m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
            b_rec_shape = sf::RectangleShape(m_size);
            b_rec_shape.setFillColor(m_bgNormal);
            b_rec_shape.setOutlineThickness(m_borderThickness);
            b_rec_shape.setOutlineColor(m_border);
            b_rec_shape.setOrigin(b_rec_shape.getGlobalBounds().width/2, b_rec_shape.getGlobalBounds().height/2);
            b_rec_shape.setPosition(m_pos);
            m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
            sf::Vector2f textPosition = sf::Vector2f(b_rec_shape.getPosition().x, b_rec_shape.getPosition().y - b_rec_shape.getGlobalBounds().height/4);
            m_text.setPosition(textPosition);
            m_text.setFillColor(m_textNormal);
            m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
            m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
            m_shadow.setFillColor(sf::Color(0,0,0));
        }
            break;

        case gui::style::clean:
        {
            m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
            b_rec_shape = sf::RectangleShape(m_size);
            b_rec_shape.setFillColor(m_bgNormal);
            b_rec_shape.setOutlineThickness(m_borderThickness);
            b_rec_shape.setOutlineColor(m_border);
            b_rec_shape.setOrigin(b_rec_shape.getGlobalBounds().width/2, b_rec_shape.getGlobalBounds().height/2);
            b_rec_shape.setPosition(m_pos);
            m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
            sf::Vector2f textPosition = sf::Vector2f(b_rec_shape.getPosition().x, b_rec_shape.getPosition().y - b_rec_shape.getGlobalBounds().height/4);
            m_text.setPosition(textPosition);
            m_text.setFillColor(m_textNormal);
            m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
            m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
            m_shadow.setFillColor(sf::Color(0,0,0));
        }
            break;

        default:
            break;
    }

    //perform updates for user mouse interactions
    sf::Vector2i m_mousePosition = sf::Mouse::getPosition(window);

    bool mouseInButton =    m_mousePosition.x >= b_rec_shape.getPosition().x - b_rec_shape.getGlobalBounds().width/2
                            && m_mousePosition.x <= b_rec_shape.getPosition().x + b_rec_shape.getGlobalBounds().width/2
                            && m_mousePosition.y >= b_rec_shape.getPosition().y - b_rec_shape.getGlobalBounds().height/2
                            && m_mousePosition.y <= b_rec_shape.getPosition().y + b_rec_shape.getGlobalBounds().height/2;

    if(e.type == sf::Event::MouseMoved)
    {
        if(mouseInButton)
        {
            m_state = gui::state::hovered;
        }

        else
        {
            m_state = gui::state::normal;
        }
    }

    if (e.type == sf::Event::MouseButtonPressed)
    {
        switch(e.mouseButton.button)
        {
            case sf::Mouse::Left:
            {
                if(mouseInButton)
                {
                    m_state = gui::state::clicked;
                }

                else
                {
                    m_state = gui::state::normal;
                }
            }
                break;
        }
    }

    if (e.type == sf::Event::MouseButtonReleased)
    {
        switch(e.mouseButton.button)
        {
            case sf::Mouse::Left:
            {
                if(mouseInButton)
                {
                    m_state = gui::state::hovered;
                }

                else
                {
                    m_state = gui::state::normal;
                }
            }
        }
    }

    switch(m_state)
    {
        case gui::state::normal:
        {
            b_rec_shape.setFillColor(m_bgNormal);
            m_text.setFillColor(m_textNormal);
        }
            break;

        case gui::state::hovered:
        {
            b_rec_shape.setFillColor(m_bgHover);
            m_text.setFillColor(m_textHover);
        }
            break;

        case gui::state::clicked:
        {
            b_rec_shape.setFillColor(m_bgClicked);
            m_text.setFillColor(m_textClicked);
        }
            break;
    }
}

void gui::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    switch(m_style)
    {
        case gui::style::none:
        {
            target.draw(b_rec_shape, states);
            target.draw(m_shadow, states);
            target.draw(m_text, states);
        }
            break;

        case gui::style::save:
        {
            target.draw(b_rec_shape, states);
            target.draw(m_shadow, states);
            target.draw(m_text, states);
        }
            break;

        case gui::style::cancel:
        {
            target.draw(b_rec_shape, states);
            target.draw(m_shadow, states);
            target.draw(m_text, states);
        }
            break;

        case gui::style::clean:
        {
            target.draw(b_rec_shape, states);
            target.draw(m_shadow, states);
            target.draw(m_text, states);
        }
            break;

        default:
            break;
    }
}

