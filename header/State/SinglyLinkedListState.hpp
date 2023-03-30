#pragma once

#include <State/State.hpp>

class LinkedListState : public State {
public:
    explicit LinkedListState(sf::RenderWindow &window);
    // void activateAnimation(sf::Time dt, double speed);
    void SLLInsertAnimation(sf::Time dt, double speed, int insertIndex, int insertData);
    void SLLInsertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertData);
    void SLLDeleteAnimation(sf::Time dt, double speed, int deleteIndex);
    void SLLDeleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue);
    void SLLUpdateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue);
    void SLLUpdateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue);
    void SLLSearchAnimation(sf::Time dt, double speed, int searchValue);
    void SLLSearchAnimationReversed(sf::Time dt, double speed, int searchValue);
    void createSLL(std::vector<int> list);
    void createStaticArray(std::vector<int> list);
    void createDynamicArray(std::vector<int> list);
    void createDLL(std::vector<int> list);
    void createCLL(std::vector<int> list);
    void createStack(std::vector<int> list);
    void createQueue(std::vector<int> list);
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
    std::vector<int> mListData = {};
    void resetNodeState();
    bool isProcessing();
private:
    enum Layers {
        Button,
        Nodes,
        newNode,
        Arrow,
        tempArrow,
        CodeBox,
        LayerCount
    };
private:
    virtual void loadTextures();
    virtual void loadFonts();
    virtual void loadCode();
    virtual void buildScence();
};
