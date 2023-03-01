#include "../header/Animation.h"

bool anm::isHover(sf::Vector2i pos, int right, int top, int left, int bottom) {
    return pos.x >= right && pos.x <= left && pos.y >= top && pos.y <= bottom;
}

void anm::setText(sf::Text &text, sf::Font &font, std::string string, int size, int posX, int posY, int red, int green, int blue, int alpha) {
    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(size);
    text.setPosition(posX, posY);
    text.setFillColor(sf::Color(red, green, blue, alpha));
}