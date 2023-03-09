#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Animation.h"

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
    void set(std::string string, sf::Font &font, int posX, int posY, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor);
};

class Pointer {
public:
    sf::Text text;
    sf::RectangleShape box;
    void set(std::string string, sf::Font &font, int posX, int posY, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor);
};

class Button {
public:
    virtual void activate(sf::RenderWindow &window) = 0;
    virtual bool isClicked(sf::RenderWindow &window) = 0;
};

class ImageButton : public Button {
private:
    sf::Texture originalButtonTexture;
    sf::Texture hoverredButtonTexture;
    sf::Sprite originalButton;
    sf::Sprite hoverredButton;
public:
    ImageButton(std::string originalButtonImagePath, std::string hoverredButtonImagePath, double width, double height, sf::Vector2f pos);
    void activate(sf::RenderWindow &window) override;
    bool isClicked(sf::RenderWindow &window) override;
};

// class TextButton : public Button {
// public:
//     void trigger(void (*func)()) override;
// };
