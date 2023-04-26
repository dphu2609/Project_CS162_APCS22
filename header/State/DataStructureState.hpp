#pragma once

#include <State/State.hpp>

class DataStructureState : public State { 
public:
    DataStructureState(sf::RenderWindow &window);

    virtual void createDataStructure(SinglyLinkedList<int> &list) = 0;
    virtual void insertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue) {}
    virtual void insertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue) {}
    virtual void deleteAnimation(sf::Time dt, double speed, int deleteIndex) {}
    virtual void deleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue) {}
    virtual void updateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue) {}
    virtual void updateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue) {}
    virtual void searchAnimation(sf::Time dt, double speed, int searchValue) {}
    virtual void searchAnimationReversed(sf::Time dt, double speed, int searchValue) {}

    bool mInsertActivated = 0;
    bool mDeleteActivated = 0;
    bool mUpdateActivated = 0;
    bool mSearchActivated = 0;
    bool mAccessActivated = 0;
    int mAnimationOrder = 0;
    bool mIsActionPaused = 0;
    int mAnimationStep = 0;
    int mColorIndex = 0;
    bool mIsEndAnimation = 0;
    int mActionIndex;
    int mActionValue;
    bool mIsInsertOnce = 0;
    SinglyLinkedList<int> mListData;
    SinglyLinkedList<int> mTempListData;    
    void resetNodeState();
    bool isProcessing();
    bool mIsReplay = 0;
    bool mIsReplayOnce = 0;
    enum Layers {
        NewNode,
        Arrow,
        DLLArrow,
        CLLArrow,
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

#include <State/SLLState.hpp>
#include <State/DLLState.hpp>
#include <State/CLLState.hpp>
#include <State/StackState.hpp>
#include <State/QueueState.hpp>
#include <State/StaticArrayState.hpp>
#include <State/DynamicArrayState.hpp>
