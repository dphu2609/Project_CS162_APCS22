#include "../header/Animation.h"

bool anm::isHover(sf::Text text, sf::Vector2i pos) {
    sf::FloatRect textBounds = text.getGlobalBounds();
    sf::Vector2f startPoint(textBounds.left, textBounds.top);
    sf::Vector2f endPoint(textBounds.left + textBounds.width, textBounds.top + textBounds.height);
    return pos.x >= textBounds.left && pos.x <= textBounds.left + textBounds.width && pos.y >= textBounds.top && pos.y <= textBounds.top + textBounds.height;
}

void anm::setText(sf::Text &text, sf::Font &font, std::string string, int size, int posX, int posY, sf::Color color) {
    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(size);
    text.setPosition(posX, posY);
    text.setFillColor(color);
}

void anm::hoverText(sf::Text &text, sf::Vector2i pos, sf::Color newColor, sf::Color orginalColor) {
    if (anm::isHover(text, pos)) {
        text.setFillColor(newColor);
    } else text.setFillColor(orginalColor);
}