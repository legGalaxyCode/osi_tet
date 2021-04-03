//
// Created by alexe on 01.04.2021.
//

#ifndef TETRIS_TEXT_BLOCK_H
#define TETRIS_TEXT_BLOCK_H
#include <SFML/Graphics.hpp>

namespace gui {
    namespace blockState {
        enum {
            normal = 0,
            selected = 1,
        };
    }

    class TextBlock : public sf::Drawable {
    public:
        TextBlock() = default;
        ~TextBlock() override = default;

        void setOptString(const std::string& _opt);

        void setKeyString(const std::string& key_);

        void setFont(sf::Font& _f);

        void setCharSize(unsigned _size);

        void setFillColor(sf::Color& _c);

        void setTextStyle(sf::Text::Style _style);

        void setLetterSpacing(float _space);

        void setWordSpacing(float space_);

        void setPosition(float x_, float y_);

        void setState(sf::Uint32 state_);

        void setOptions(const std::string&, const std::string&, sf::Font&, sf::Uint32,
                        float, sf::Color, unsigned int, float,
                        float, sf::Text::Style, float);

        sf::Uint32 getState() const;

        void update(sf::Event& e, sf::RenderWindow& window);

    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        sf::Text opt;
        sf::Text key;
        sf::Font font;
        sf::Color color;

        float wordSpace = 20; // in px
        sf::Uint32 state;
    };

}

#endif //TETRIS_TEXT_BLOCK_H
