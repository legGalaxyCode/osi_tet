//
// Created by alexe on 01.04.2021.
//

#ifndef TETRIS_CREDITS_H
#define TETRIS_CREDITS_H
#include <SFML/Graphics.hpp>

class World;

namespace gui {
    class Credits : public sf::Drawable
    {
    public:
        Credits() = default;
        ~Credits() override = default;
    void Init();
    void setFont(const sf::Font& f_) {
        developerText.setFont(f_);
    }
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::RectangleShape recShape;
        sf::Text developerText;
    };
}
#endif //TETRIS_CREDITS_H
