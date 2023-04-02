#pragma once

#include <State/State.hpp>

class LinkedListState : public State { //after creating all the data structures, we can create a state for each of them,
public:                                 //i should create a base class a derived class for each data structure
    explicit LinkedListState(sf::RenderWindow &window);

    void createSLL(std::vector<int> list);
    void SLLInsertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue);
    void SLLInsertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue);
    void SLLDeleteAnimation(sf::Time dt, double speed, int deleteIndex);
    void SLLDeleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue);
    void SLLUpdateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue);
    void SLLUpdateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue);
    void SLLSearchAnimation(sf::Time dt, double speed, int searchValue);
    void SLLSearchAnimationReversed(sf::Time dt, double speed, int searchValue);

    void createStaticArray(std::vector<int> list);
    void staticArrayInsertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue);
    void staticArrayInsertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue);
    void staticArrayDeleteAnimation(sf::Time dt, double speed, int deleteIndex);
    void staticArrayDeleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue);
    void staticArrayUpdateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue);
    void staticArrayUpdateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue);
    void staticArraySearchAnimation(sf::Time dt, double speed, int searchValue);
    void staticArraySearchAnimationReversed(sf::Time dt, double speed, int searchValue);

    void createDynamicArray(std::vector<int> list);
    void dynamicArrayInsertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue);
    void dynamicArrayInsertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue);
    void dynamicArrayDeleteAnimation(sf::Time dt, double speed, int deleteIndex);
    void dynamicArrayDeleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue);
    void dynamicArrayUpdateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue);
    void dynamicArrayUpdateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue);
    void dynamicArraySearchAnimation(sf::Time dt, double speed, int searchValue);
    void dynamicArraySearchAnimationReversed(sf::Time dt, double speed, int searchValue);

    void createDLL(std::vector<int> list);
    void DLLInsertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue);
    void DLLInsertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue);
    void DLLDeleteAnimation(sf::Time dt, double speed, int deleteIndex);
    void DLLDeleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue);
    void DLLUpdateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue);
    void DLLUpdateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue);
    void DLLSearchAnimation(sf::Time dt, double speed, int searchValue);
    void DLLSearchAnimationReversed(sf::Time dt, double speed, int searchValue);

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
    int mActionIndex;
    int mActionValue;
    bool mIsInsertOnce = 0;
    std::vector<int> mListData = {};
    std::vector<int> mTempListData = {};
    void resetNodeState();
    bool isProcessing();
    bool mIsReplay = 0;
    bool mIsReplayOnce = 0;
private:
    enum Layers {
        NewNode,
        Arrow,
        DLLArrow,
        NewArrow,
        NewDLLArrow,
        BlankNode,
        Nodes,
        NewArray,
        ArrayBoder,
        CodeBox,
        LayerCount
    };
private:
    virtual void loadTextures();
    virtual void loadFonts();
    virtual void loadCode();
    virtual void buildScence();
};
