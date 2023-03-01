#pragma once

#include <SFML/Graphics.hpp>

namespace anm {
    bool isHover(sf::Text text, sf::Vector2i pos);
    void setText(sf::Text &text, sf::Font &font, std::string string, int size, int posX, int posY, sf::Color color);
    void hoverText(sf::Text &text, sf::Vector2i pos, sf::Color newColor, sf::Color orginalColor);
};