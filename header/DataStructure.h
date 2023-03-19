#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include <Animation.h>

class AnimationVar {
public:
    double initialVar;
    bool isTriggered;
    double forwardVal(double startPoint ,double endPoint);
    double backwardVal(double startPoint);
    void changeVar(double startPoint, double endPoint, double frame, double speed);
};

class GraphicalNode {
public:
    sf::Text number;
    sf::RectangleShape box;
    void set(std::string string, sf::Font &font, double size, sf::Vector2f pos, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor);
    void setPos(sf::Vector2f pos);
};

