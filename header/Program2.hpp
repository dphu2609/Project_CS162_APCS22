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
private:
    LinkedListState mMenu;
    sf::RenderWindow mWindow;
};