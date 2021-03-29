//
// Created by alexe on 27.03.2021.
//

#ifndef SFML_TEST_BUTTON_H
#define SFML_TEST_BUTTON_H
#include <SFML/Graphics.hpp>

namespace gui {
    namespace style {
        enum {
            none = 0,
            save = 1,
            cancel = 2,
            clean = 3,};
    };

    namespace state {
        enum {
            normal = 0,
            hovered = 1,
            clicked = 2,
        };
    }

    class Button : public sf::Drawable
    {
    public:
        Button() = default;
        Button(std::string _s, sf::Font& _f, sf::Vector2f _pos, sf::Uint32 _style);
        ~Button() override = default;

        void setColorTextNormal(sf::Color _c) {m_textNormal = _c;};
        void setColorTextHover(sf::Color _c) {m_textHover = _c;};
        void setColorTextClicked(sf::Color _c) {m_textClicked = _c;};
        void setColorNormal(sf::Color bgNormal) {m_bgNormal = bgNormal;};
        void setColorHover(sf::Color bgHover) {m_bgHover = bgHover;};
        void setColorClicked(sf::Color bgClicked) {m_bgClicked = bgClicked;};
        void setBorderColor(sf::Color _c) {m_border = _c;};
        void setBorderThickness(float t) {m_borderThickness = t;};
        void setBorderRadius(float r) {m_borderRadius = r;};
        void setString(const std::string& _s) {b_text = _s; m_text.setString(b_text); m_shadow = m_text;};
        void setPosition(const sf::Vector2f &_v) { m_pos = _v;};
        void setPosition(const float x, const float y) { m_pos.x = x; m_pos.y = y;};
        void setSize(const sf::Vector2f &_v) { m_size = _v;};
        void setSize(const float x, const float y) { m_size.x = x; m_size.y = y;};
        void setSize(unsigned _size);
        void setTexture(const sf::Texture *_t) {b_txt = _t;};
        void setFillColor(const sf::Color &_c) {b_rec_shape.setFillColor(_c);};
        void setOutlineColor(const sf::Color &_c) {b_rec_shape.setOutlineColor(_c);};
        void setStyle(sf::Uint32 _style);
        void setFont(sf::Font& _f);

        sf::Vector2f getPosition() {return m_pos;};
        sf::Vector2f getDimensions() {return sf::Vector2f(b_rec_shape.getGlobalBounds().width,
                                                          b_rec_shape.getGlobalBounds().height);};
        sf::Uint32 getState() {return m_state;};

        void update(sf::Event& e, sf::RenderWindow& window);
    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        sf::Color m_bgNormal;
        sf::Color m_bgHover;
        sf::Color m_bgClicked;
        sf::Color m_textNormal;
        sf::Color m_textHover;
        sf::Color m_textClicked;
        sf::Color m_border;

        std::string b_text;
        sf::Vector2f m_pos;
        sf::Vector2f m_size;
        float m_borderThickness;
        float m_borderRadius;
        sf::Uint32 m_style;
        sf::Uint32 m_state;

        const sf::Texture* b_txt;
        sf::RectangleShape b_rec_shape;
        sf::Font font;
        unsigned m_font_size;
        sf::Text m_text;
        sf::Text m_shadow;
    };
}

#endif //SFML_TEST_BUTTON_H
