#pragma once
#include <State/State.hpp>
#include <ResourceHolder.hpp>
#include <SceneGraph/SceneNode.hpp>
#include <SceneGraph/DisplayNode.hpp>
#include <SceneGraph/SpriteNode.hpp>
#include <SceneGraph/ButtonNode.hpp>
#include <State/State.hpp>
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