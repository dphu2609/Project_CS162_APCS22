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
    bool mIsActionPaused = 0;
    int mAnimationStep = 0;
    int mColorIndex = 0;
    bool mIsEndAnimation = 0;
    std::vector<int> mListData;
private:
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
