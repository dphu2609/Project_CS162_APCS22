#include <Program2.hpp>

Program2::Program2() : mWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width - 35, sf::VideoMode::getDesktopMode().height - 70), "Data Visual", sf::Style::Default), 
mMenu(mWindow), mSettings(mWindow), mSLL(mWindow), mDLL(mWindow), mCLL(mWindow), mStack(mWindow), mQueue(mWindow), mStaticArray(mWindow), mDynamicArray(mWindow) {
    mWindow.setPosition(sf::Vector2i(0, 0));
}

void Program2::run() {
    const sf::Time dt = sf::seconds(1.0f / 144.0f);
    sf::Clock clock;    
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        processEvents();
        if (mMenu.mIsProgramStarted) {
            timeSinceLastUpdate += clock.restart();
            while (timeSinceLastUpdate > dt) {
                timeSinceLastUpdate -= dt;
                mSettings.activeSettings(dt);
                if (mSettings.mStateActivated[States::StaticArray]) {
                    dataStructureDisplay(dt, mStaticArray);
                } else if (mSettings.mStateActivated[States::DynamicArray]) {
                    dataStructureDisplay(dt, mDynamicArray);
                } else if (mSettings.mStateActivated[States::SinglyLinkedList]) {
                    dataStructureDisplay(dt, mSLL);
                } else if (mSettings.mStateActivated[States::DoublyLinkedList]) {
                    dataStructureDisplay(dt, mDLL);
                } else if (mSettings.mStateActivated[States::CircularLinkedList]) {
                    dataStructureDisplay(dt, mCLL);
                } else if (mSettings.mStateActivated[States::Stack]) {
                    dataStructureDisplay(dt, mStack);
                } else if (mSettings.mStateActivated[States::Queue]) {
                    dataStructureDisplay(dt, mQueue);
                }
                mSettings.update(dt);
                mSettings.controlBoxUpdate();
            }
        }
        mWindow.clear(sf::Color(18, 18, 18, 255));
        if (mMenu.mIsProgramStarted) {
            if (mSettings.mStateActivated[States::StaticArray]) mStaticArray.draw();
            else if (mSettings.mStateActivated[States::DynamicArray]) mDynamicArray.draw();
            else if (mSettings.mStateActivated[States::SinglyLinkedList]) mSLL.draw();
            else if (mSettings.mStateActivated[States::DoublyLinkedList]) mDLL.draw();
            else if (mSettings.mStateActivated[States::CircularLinkedList]) mCLL.draw();
            else if (mSettings.mStateActivated[States::Stack]) mStack.draw();
            else if (mSettings.mStateActivated[States::Queue]) mQueue.draw();
            mSettings.draw();
        }
        else mMenu.draw();
        mWindow.display();
    }
}

void Program2::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (!mMenu.mIsProgramStarted) mMenu.handleMenuEvent(event);
        else {
            mSettings.handleEvent(event);
            mSettings.controlEvent(event);
        }
        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Program2::dataStructureDisplay(sf::Time dt, DataStructureState &dataStructure) {
    dataStructure.mIsReplay = mSettings.mIsReplay;
    if (mSettings.mActionActivated[Action::ResetAction]) {
        mSettings.mActionActivated[Action::ResetAction] = 0;
    }
    if (mSettings.mActionActivated[Action::Play]) {
        int index = 0;
        for (int i = 0; i < Action::ActionCount; i++) {
            if (mSettings.mActionActivated[i]) {
                index = i;
                break;
            }
        }
        dataStructure.mInsertActivated = 0;
        dataStructure.mDeleteActivated = 0;
        dataStructure.mUpdateActivated = 0;
        dataStructure.mSearchActivated = 0;
        switch(index) {
            case Action::Create : {
                dataStructure.mListData.clear();
                dataStructure.mTempListData.clear();
                break;
            }
            case Action::Insert : {
                dataStructure.mInsertActivated = 1;
                break;
            }
            case Action::Delete : {
                dataStructure.mDeleteActivated = 1;
            }
            case Action::Update : {
                dataStructure.mUpdateActivated = 1;
                break;
            }
            case Action::Search : {
                dataStructure.mSearchActivated = 1;
                break;
            }
        }
        dataStructure.createDataStructure(mSettings.mInputArr);
        dataStructure.mAnimationOrder = 1;
        dataStructure.mColorIndex = 0;
        dataStructure.mIsEndAnimation = 0;
        mSettings.mIsEndAnimation.first = 0;
        mSettings.mIsPrev = 0;
        mSettings.mIsNext = 0;
        mSettings.mActionActivated[Action::Play] = 0;
    }
    if (dataStructure.mInsertActivated || dataStructure.mDeleteActivated || dataStructure.mUpdateActivated || dataStructure.mSearchActivated) {
        if (mSettings.mIsNext) {
            if (mSettings.mPrevNext != mSettings.mIsNext && !dataStructure.isProcessing()) {
                mSettings.mPrevPrev = 0;
                mSettings.mPrevNext = 1;
                mSettings.mPrevPlay = 1;
                mSettings.mPrevAnimationOrder = mSettings.mAnimationOrder - 1;
                mSettings.mPrevColorIndex = mSettings.mColorIndex - 1;
                dataStructure.resetNodeState();
            }
            if (dataStructure.mInsertActivated) dataStructure.insertAnimation(dt, mSettings.mSpeed, mSettings.mActionIndex, mSettings.mActionValue); 
            else if (dataStructure.mDeleteActivated) dataStructure.deleteAnimation(dt, mSettings.mSpeed, mSettings.mActionIndex);
            else if (dataStructure.mUpdateActivated) dataStructure.updateAnimation(dt, mSettings.mSpeed, mSettings.mActionIndex, mSettings.mActionValue);
            else if (dataStructure.mSearchActivated) dataStructure.searchAnimation(dt, mSettings.mSpeed, mSettings.mActionValue);
        }
        else if (mSettings.mIsPrev) {  
            if (mSettings.mPrevPrev != mSettings.mIsPrev && !dataStructure.isProcessing()) {
                mSettings.mPrevPrev = 1;
                mSettings.mPrevNext = 0;
                mSettings.mPrevPlay = 0;
                mSettings.mPrevAnimationOrder = mSettings.mAnimationOrder + 1;
                mSettings.mPrevColorIndex = mSettings.mColorIndex + 1;
                dataStructure.resetNodeState();
            }
            if (dataStructure.mInsertActivated) dataStructure.insertAnimationReversed(dt, mSettings.mSpeed, mSettings.mActionIndex, mSettings.mActionValue); 
            else if (dataStructure.mDeleteActivated) dataStructure.deleteAnimationReversed(dt, mSettings.mSpeed, mSettings.mActionIndex, mSettings.mActionValue);
            else if (dataStructure.mUpdateActivated) dataStructure.updateAnimationReversed(dt, mSettings.mSpeed, mSettings.mActionIndex, mSettings.mPrevActionValue);
            else if (dataStructure.mSearchActivated) dataStructure.searchAnimationReversed(dt, mSettings.mSpeed, mSettings.mActionValue);
        } 
        else {
            if (mSettings.mPrevPlay != mSettings.mIsPlay && !dataStructure.isProcessing()) {
                mSettings.mPrevPlay = 1;
                mSettings.mPrevPrev = 0;
                mSettings.mPrevNext = 1;
                dataStructure.resetNodeState();
            }
            if (dataStructure.mInsertActivated) dataStructure.insertAnimation(dt, mSettings.mSpeed, mSettings.mActionIndex, mSettings.mActionValue); 
            else if (dataStructure.mDeleteActivated) dataStructure.deleteAnimation(dt, mSettings.mSpeed, mSettings.mActionIndex);
            else if (dataStructure.mUpdateActivated) dataStructure.updateAnimation(dt, mSettings.mSpeed, mSettings.mActionIndex, mSettings.mActionValue);
            else if (dataStructure.mSearchActivated) dataStructure.searchAnimation(dt, mSettings.mSpeed, mSettings.mActionValue);
        }
    }
    mSettings.mAnimationOrder = dataStructure.mAnimationOrder;
    mSettings.mColorIndex = dataStructure.mColorIndex;
    dataStructure.mIsActionPaused = mSettings.mIsActionPaused;
    mSettings.mIsEndAnimation.first = dataStructure.mIsEndAnimation;
    mSettings.mInputArr = dataStructure.mListData;
    dataStructure.mIsReplay = mSettings.mIsReplay;
    dataStructure.mActionIndex = mSettings.mActionIndex;
    dataStructure.mActionValue = mSettings.mActionValue;
    if ((mSettings.mPrevAnimationOrder != mSettings.mAnimationOrder || mSettings.mColorIndex != mSettings.mPrevColorIndex) && (mSettings.mIsPrev || mSettings.mIsNext)) {
        mSettings.mPrevAnimationOrder = mSettings.mAnimationOrder;
        mSettings.mPrevColorIndex = mSettings.mColorIndex;
        mSettings.mIsActionPaused = 1;
    }
    dataStructure.update(dt);
}
