#pragma once

// #include <State/State.hpp>
#include <State/LinkedListState.hpp>


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