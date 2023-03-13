#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Animation.h>
#include <DataStructure.h>
#include <LinkedList.h>


class Program {
private: 
    sf::RenderWindow window;
    sf::Font TiltWarp;
    sf::Font GreatVibes;
    sf::Font ComfortaaRegular;
    sf::Vector2i localPosition;
public: 
    const int maxWidth = sf::VideoMode::getDesktopMode().width;
    const int maxHeight = sf::VideoMode::getDesktopMode().height;
    Program();
};
