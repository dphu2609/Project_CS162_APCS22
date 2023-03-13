#pragma once

#include "SFML/Graphics.hpp"

class Button {
public:
    virtual void activate(sf::RenderWindow &window) = 0;
    virtual bool isClicked(sf::RenderWindow &window) = 0;
};

class ImageButton : public Button {
public:
    sf::Sprite originalButton;
    sf::Sprite hoverredButton;
public:
    void set(sf::Texture &originalButtonTexture, sf::Texture &hoverredButtonTexture, double width, double height, sf::Vector2f pos);
    void activate(sf::RenderWindow &window) override;
    bool isClicked(sf::RenderWindow &window) override;
};