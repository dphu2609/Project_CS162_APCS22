#pragma once

#include <State/State.hpp>

class LinkedListState : public State {
public:
    explicit LinkedListState(sf::RenderWindow &window);
    // void activateAnimation(sf::Time dt, double speed);
    void insertAnimation(sf::Time dt, double speed, int insertIndex, int insertData);
    void insertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertData);
    void deleteAnimation(sf::Time dt, double speed, int deleteIndex);
    void deleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue);
    void updateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue);
    void updateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue);
    void searchAnimation(sf::Time dt, double speed, int searchValue);
    void searchAnimationReversed(sf::Time dt, double speed, int searchValue);
    void createList(std::vector<int> &list);
    void handleClick(sf::Event &event);
    bool mInsertActivated = 0;
    bool mDeleteActivated = 0;
    bool mUpdateActivated = 0;
    bool mSearchActivated = 0;
    int mAnimationOrder = 0;
    bool mIsActionPaused = 0;
    int mAnimationStep = 0;
    int mColorIndex = 0;
    bool mIsEndAnimation = 0;
    std::vector<int> mListData;
    void resetNodeState();
    bool isProcessing();
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
