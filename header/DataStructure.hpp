#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

class GraphicalNode {
public:
    sf::Text number;
    sf::RectangleShape box;
    void set(
        std::string string, sf::Font &font, double size, sf::Vector2f pos, 
        sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor
    );
    void setPos(sf::Vector2f pos);
    void setColor(sf::Color textColor, sf::Color boxColor, sf::Color outlineColor);
    void setSize(double size);
    void setString(std::string string);
};

