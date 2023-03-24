#pragma once

#include <State/State.hpp>

class LinkedListState : public State {
public:
    explicit LinkedListState(sf::RenderWindow &window);
    // void activateAnimation(sf::Time dt, double speed);
    void insertAnimation(sf::Time dt, double speed, int insertIndex, int insertData);
    void deleteAnimation(sf::Time dt, double speed, int deleteIndex);
    void createList(std::vector<int> &list);
    void handleClick(sf::Event &event);
    bool mInsertActivated = 0;
    bool mDeleteActivated = 0;
    int mAnimationOrder = 0;
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
    int mColorIndex = 0;
private:
    virtual void loadTextures();
    virtual void loadFonts();
    virtual void buildScence();
};
