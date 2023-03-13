#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "ResourceHolder.hpp"
#include "SceneGraph.hpp"
#include "Event.hpp"

class State : private sf::NonCopyable {
public:
    explicit State(sf::RenderWindow &window);
    void update(sf::Time dt);
    void draw();
public:
    sf::RenderWindow &mWindow;
    std::array<SceneNode*, 20> mSceneLayers;
    SceneNode mSceneGraph;
    ResourceHolder<sf::Texture, Textures::ID> mTexturesHolder;
    ResourceHolder<sf::Font, Fonts::ID> mFontsHolder;
private:
    virtual void loadTextures() = 0;
    virtual void loadFonts() = 0;
    virtual void buildScence() = 0;
};

class LinkedListState : public State {
public:
    explicit LinkedListState(sf::RenderWindow &window);
    void activateAnimation(sf::Time dt, double speed);
    void addAnimation(sf::Time dt, double speed);
private:
    int animationOrder;
    bool isAdd;
    std::vector<int> arr;
    int addIndex;
    enum Layers {
        Button,
        Nodes,
        newNode,
        LayerCount
    };
private:
    virtual void loadTextures();
    virtual void loadFonts();
    virtual void buildScence();
};