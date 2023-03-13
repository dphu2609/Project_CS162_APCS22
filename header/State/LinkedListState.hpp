#pragma once

#include <State/State.hpp>

class LinkedListState : public State {
public:
    explicit LinkedListState(sf::RenderWindow &window);
    void activateAnimation(sf::Time dt, double speed);
    void addAnimation(sf::Time dt, double speed);
    virtual void handleEvent();
    bool isAdd;
private:
    int animationOrder;
    std::vector<int> arr;
    int addIndex;
    enum Layers {
        Button,
        Nodes,
        newNode,
        Arrow,
        tempArrow,
        LayerCount
    };
private:
    virtual void loadTextures();
    virtual void loadFonts();
    virtual void buildScence();
};
