#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>

namespace anm {

bool isHover(sf::Text text, sf::Vector2i pos);
void setText(sf::Text &text, sf::Font &font, std::string string, int size, int posX, int posY, sf::Color color);
void hoverText(sf::Text &text, sf::Vector2i pos, sf::Color newColor, sf::Color orginalColor);


class InputBox {
public:
    std::string content;
    sf::Text inputText;
    sf::RectangleShape inputBox;
    InputBox(sf::Font &font, int size, sf::Color textColor, float posX, float posY, float boxLength, sf::Color boxColor, sf::Color boxOutlineColor, int outLineThickness);
    void type(sf::Event &event);
};

};