#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Animation.h"
#include "LinkedList.h"

class Menu {
private: 
    sf::RenderWindow window;
    sf::Font TiltWarp;
    sf::Font GreatVibes;
    sf::Font ComfortaaRegular;
public: 
    const int maxWidth = sf::VideoMode::getDesktopMode().width;
    const int maxHeight = sf::VideoMode::getDesktopMode().height;
    Menu();
    void nextPage();
};