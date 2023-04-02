#pragma once

#include <State/State.hpp>

class DataStructureState : public State { //after creating all the data structures, we can create a state for each of them,
public:                                 //i should create a base class a derived class for each data structure
    explicit DataStructureState(sf::RenderWindow &window);

    virtual void createDataStructure(std::vector<int> list) = 0;
    virtual void insertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue) = 0;
    virtual void insertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue) = 0;
    virtual void deleteAnimation(sf::Time dt, double speed, int deleteIndex) = 0;
    virtual void deleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue) = 0;
    virtual void updateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue) = 0;
    virtual void updateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue) = 0;
    virtual void searchAnimation(sf::Time dt, double speed, int searchValue) = 0;
    virtual void searchAnimationReversed(sf::Time dt, double speed, int searchValue) = 0;

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
