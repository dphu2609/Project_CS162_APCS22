#pragma once

// #include <State/State.hpp>
#include <State/State.hpp>


class Program2 {
public:
    Program2();
    void run();
private:
    void processEvents();
    void linkedListHandle(sf::Time dt, LinkedListState &linkedList);
private:
    SettingsState mSettings;
    LinkedListState mSinglyLinkedList;
    sf::RenderWindow mWindow;
};