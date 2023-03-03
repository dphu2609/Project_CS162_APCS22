#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Animation.h"

class Menu {
private: 
    sf::RenderWindow window;
    sf::Font TiltWarp;
    sf::Font GreatVibes;
    sf::Font ComfortaaRegular;
    sf::Color lightBlue;
    sf::Color whiteBlue;
public: 
    const int maxWidth = sf::VideoMode::getDesktopMode().width;
    const int maxHeight = sf::VideoMode::getDesktopMode().height;
    Menu();
    void nextPage();
};