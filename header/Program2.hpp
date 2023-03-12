#pragma once
#include "State.hpp"
#include "ResourceHolder.hpp"
#include "SceneGraph.hpp"

class Program2 {
public:
    Program2();
    void run();
private:
    void processEvents();
    void update();
    void render();
private:
    MenuState mMenu;
    sf::RenderWindow mWindow;
};