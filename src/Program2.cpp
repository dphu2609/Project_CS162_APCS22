#include <Program2.hpp>

Program2::Program2() : mWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Data Visual", sf::Style::Default), mSinglyLinkedList(mWindow), mSettings(mWindow) {
    mSinglyLinkedList.mInsertActivated = 0;
}

void Program2::run() {
    const sf::Time dt = sf::seconds(1.0f / 120.0f);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    bool isAnimationTriggered = 0;
    while (mWindow.isOpen()) {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > dt) {
            timeSinceLastUpdate -= dt;
            mSettings.activeSettings(dt);
            if (mSettings.mStateActivated[States::SinglyLinkedList]) {
                linkedListHandle(dt, mSinglyLinkedList);
            }
            mSettings.update(dt);
            mSettings.controlBoxUpdate();
        }
        mWindow.clear(sf::Color(18, 18, 18, 255));
        if (mSettings.mStateActivated[States::SinglyLinkedList]) mSinglyLinkedList.draw();
        mSettings.draw();
        mWindow.display();
    }
}

void Program2::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        mSettings.handleEvent(event);
        mSettings.controlEvent(event);
        mSinglyLinkedList.handleClick(event);
        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Program2::linkedListHandle(sf::Time dt, LinkedListState &linkedList) {
    linkedList.mIsReplay = mSettings.mIsReplay;
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
        linkedList.mInsertActivated = 0;
        linkedList.mDeleteActivated = 0;
        linkedList.mUpdateActivated = 0;
        linkedList.mSearchActivated = 0;
        switch(index) {
            case Action::Create : {
                linkedList.mListData.clear();
                linkedList.mTempListData.clear();
                break;
            }
            case Action::Insert : {
                linkedList.mInsertActivated = 1;
                break;
            }
            case Action::Delete : {
                linkedList.mDeleteActivated = 1;
            }
            case Action::Update : {
                linkedList.mUpdateActivated = 1;
                break;
            }
            case Action::Search : {
                linkedList.mSearchActivated = 1;
                break;
            }
        }
        linkedList.createDLL(mSettings.mInputArr);
        linkedList.mAnimationOrder = 1;
        linkedList.mColorIndex = 0;
        linkedList.mIsEndAnimation = 0;
        mSettings.mIsEndAnimation.first = 0;
        mSettings.mIsPrev = 0;
        mSettings.mIsNext = 0;
        mSettings.mActionActivated[Action::Play] = 0;
    }
    if (linkedList.mInsertActivated || linkedList.mDeleteActivated || linkedList.mUpdateActivated || linkedList.mSearchActivated) {
        if (mSettings.mIsNext) {
            if (mSettings.mPrevNext != mSettings.mIsNext && !linkedList.isProcessing()) {
                mSettings.mPrevPrev = 0;
                mSettings.mPrevNext = 1;
                mSettings.mPrevPlay = 1;
                mSettings.mPrevAnimationOrder = mSettings.mAnimationOrder - 1;
                mSettings.mPrevColorIndex = mSettings.mColorIndex - 1;
                linkedList.resetNodeState();
            }
            if (linkedList.mInsertActivated) linkedList.DLLInsertAnimation(dt, 1, mSettings.mActionIndex, mSettings.mActionValue); 
            else if (linkedList.mDeleteActivated) linkedList.dynamicArrayDeleteAnimation(dt, 1, mSettings.mActionIndex);
            else if (linkedList.mUpdateActivated) linkedList.dynamicArrayUpdateAnimation(dt, 1, mSettings.mActionIndex, mSettings.mActionValue);
            else if (linkedList.mSearchActivated) linkedList.dynamicArraySearchAnimation(dt, 1, mSettings.mActionValue);
        }
        else if (mSettings.mIsPrev) {  
            if (mSettings.mPrevPrev != mSettings.mIsPrev && !linkedList.isProcessing()) {
                mSettings.mPrevPrev = 1;
                mSettings.mPrevNext = 0;
                mSettings.mPrevPlay = 0;
                mSettings.mPrevAnimationOrder = mSettings.mAnimationOrder + 1;
                mSettings.mPrevColorIndex = mSettings.mColorIndex + 1;
                linkedList.resetNodeState();
            }
            if (linkedList.mInsertActivated) linkedList.DLLInsertAnimationReversed(dt, 1, mSettings.mActionIndex, mSettings.mActionValue); 
            else if (linkedList.mDeleteActivated) linkedList.dynamicArrayDeleteAnimationReversed(dt, 1, mSettings.mActionIndex, mSettings.mActionValue);
            else if (linkedList.mUpdateActivated) linkedList.dynamicArrayUpdateAnimationReversed(dt, 1, mSettings.mActionIndex, mSettings.mPrevActionValue);
            else if (linkedList.mSearchActivated) linkedList.dynamicArraySearchAnimationReversed(dt, 1, mSettings.mActionValue);
        } 
        else {
            if (mSettings.mPrevPlay != mSettings.mIsPlay && !linkedList.isProcessing()) {
                mSettings.mPrevPlay = 1;
                mSettings.mPrevPrev = 0;
                mSettings.mPrevNext = 1;
                linkedList.resetNodeState();
                std::cout << 1;
            }
            if (linkedList.mInsertActivated) linkedList.DLLInsertAnimation(dt, 1, mSettings.mActionIndex, mSettings.mActionValue); 
            else if (linkedList.mDeleteActivated) linkedList.dynamicArrayDeleteAnimation(dt, 1, mSettings.mActionIndex);
            else if (linkedList.mUpdateActivated) linkedList.dynamicArrayUpdateAnimation(dt, 1, mSettings.mActionIndex, mSettings.mActionValue);
            else if (linkedList.mSearchActivated) linkedList.dynamicArraySearchAnimation(dt, 1, mSettings.mActionValue);
        }
    }
    mSettings.mAnimationOrder = linkedList.mAnimationOrder;
    mSettings.mColorIndex = linkedList.mColorIndex;
    linkedList.mIsActionPaused = mSettings.mIsActionPaused;
    mSettings.mIsEndAnimation.first = linkedList.mIsEndAnimation;
    mSettings.mInputArr = linkedList.mListData;
    linkedList.mIsReplay = mSettings.mIsReplay;
    linkedList.mActionIndex = mSettings.mActionIndex;
    linkedList.mActionValue = mSettings.mActionValue;
    if ((mSettings.mPrevAnimationOrder != mSettings.mAnimationOrder || mSettings.mColorIndex != mSettings.mPrevColorIndex) && (mSettings.mIsPrev || mSettings.mIsNext)) {
        mSettings.mPrevAnimationOrder = mSettings.mAnimationOrder;
        mSettings.mPrevColorIndex = mSettings.mColorIndex;
        mSettings.mIsActionPaused = 1;
    }
    linkedList.update(dt);
}
