#pragma once

// #include <State/State.hpp>
#include <State/State.hpp>


class Program2 {
public:
    Program2();
    void run();
private:
    void processEvents();
private:
    SettingsState mSettings;
    LinkedListState mSinglyLinkedList;
    sf::RenderWindow mWindow;
};