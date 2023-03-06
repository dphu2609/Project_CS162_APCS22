#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Animation.h"

struct AnimationVar {
    double initialVar;
    bool isTriggered;
};

class GraphicalNode {
public:
    sf::Text number;
    sf::RectangleShape box;
    void set(std::string string, sf::Font &font, int posX, int posY, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor);
};
