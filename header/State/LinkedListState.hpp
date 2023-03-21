#pragma once

#include <State/State.hpp>

class LinkedListState : public State {
public:
    explicit LinkedListState(sf::RenderWindow &window);
    // void activateAnimation(sf::Time dt, double speed);
    void addAnimation(sf::Time dt, double speed);
    void handleClick(sf::Event &event);
    bool isAdd;
private:
    int animationOrder;
    std::vector<int> arr;
    int addIndex;
    int addValue;
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
