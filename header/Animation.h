#pragma once

#include <SFML/Graphics.hpp>

namespace anm {
    bool isHover(sf::Vector2i pos, int right, int top, int left, int bottom);
    void setText(sf::Text &text, sf::Font &font, std::string string, int size, int posX, int posY, int red, int green, int blue, int alpha);
};