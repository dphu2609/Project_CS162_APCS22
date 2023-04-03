#pragma once

#include <State/State.hpp>


class Program2 {
public:
    Program2();
    void run();
private:
    void processEvents();
    void dataStructureDisplay(sf::Time dt, DataStructureState &dataStructure);
private:
    SettingsState mSettings;
    SLLState mSLL;
    DLLState mDLL;
    CLLState mCLL;
    StackState mStack;
    QueueState mQueue;
    StaticArrayState mStaticArray;
    DynamicArrayState mDynamicArray;
    sf::RenderWindow mWindow;
};