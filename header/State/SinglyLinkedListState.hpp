#pragma once

#include <State/State.hpp>

class LinkedListState : public State {
public:
    explicit LinkedListState(sf::RenderWindow &window);
    // void activateAnimation(sf::Time dt, double speed);
    void insertAnimation(sf::Time dt, double speed, int insertIndex, int insertData);
    void createList(std::vector<int> &list);
    void handleClick(sf::Event &event);
    bool mInsertActivated;
    int animationOrder;
private:
    std::vector<int> mListData;
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
