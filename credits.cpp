//
// Created by alexe on 01.04.2021.
//

#include "credits.h"

void gui::Credits::Init() {
    recShape.setSize(sf::Vector2f{200, 300});
    recShape.setOutlineColor(sf::Color::White);
    recShape.setOutlineThickness(3);
    recShape.setPosition(200, 100);
    recShape.setFillColor(sf::Color::Black);

    developerText.setString("Alexey \"legGalaxyCode\" Zhavoronkov");
    developerText.setFillColor(sf::Color::White);
    developerText.setCharacterSize(13);
    developerText.setStyle(sf::Text::Style::Bold);
    developerText.setLetterSpacing(2);
    developerText.setPosition(250, 150);
}

void gui::Credits::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    //target.draw(recShape);
    target.draw(developerText);
}