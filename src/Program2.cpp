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
                singlyLinkedListHandle(dt);
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

void Program2::singlyLinkedListHandle(sf::Time dt) {
    if (mSettings.mActionActivated[Action::Play]) {
        int index = 0;
        for (int i = 0; i < Action::ActionCount; i++) {
            if (mSettings.mActionActivated[i]) {
                index = i;
                break;
            }
        }
        mSinglyLinkedList.mInsertActivated = 0;
        mSinglyLinkedList.mDeleteActivated = 0;
        switch(index) {
            case Action::Create : {
                mSinglyLinkedList.createList(mSettings.mInputArr);
                break;
            }
            case Action::Insert : {
                mSinglyLinkedList.mInsertActivated = 1;
                break;
            }
            case Action::Delete : {
                mSinglyLinkedList.mDeleteActivated = 1;
                break;
            }
        }
        mSettings.mIsEndAnimation.first = 0;
        mSinglyLinkedList.createList(mSettings.mInputArr);
        mSinglyLinkedList.mColorIndex = 0;
        mSinglyLinkedList.mAnimationOrder = 1;
        mSettings.mActionActivated[Action::Play] = 0;
        mSinglyLinkedList.mIsEndAnimation = 0;
        mSettings.mIsPrev = 0;
        mSettings.mIsNext = 0;
    }
    if (mSinglyLinkedList.mInsertActivated) {
        if (mSettings.mIsNext) {
            if (mSettings.mPrevNext != mSettings.mIsNext && !mSinglyLinkedList.isProcessing()) {
                mSettings.mPrevPrev = 0;
                mSettings.mPrevNext = 1;
                mSettings.mPrevPlay = 1;
                mSettings.mPrevAnimationOrder = mSettings.mAnimationOrder - 1;
                mSettings.mPrevColorIndex = mSettings.mColorIndex - 1;
                mSinglyLinkedList.resetNodeState();
            }
            mSinglyLinkedList.insertAnimation(dt, 1, mSettings.mActionIndex, mSettings.mInsertValue);
        }
        else if (mSettings.mIsPrev) {  
            if (mSettings.mPrevPrev != mSettings.mIsPrev && !mSinglyLinkedList.isProcessing()) {
                mSettings.mPrevPrev = 1;
                mSettings.mPrevNext = 0;
                mSettings.mPrevPlay = 0;
                mSettings.mPrevAnimationOrder = mSettings.mAnimationOrder + 1;
                mSettings.mPrevColorIndex = mSettings.mColorIndex + 1;
                mSinglyLinkedList.resetNodeState();
            }
            mSinglyLinkedList.insertAnimationReversed(dt, 1, mSettings.mActionIndex, mSettings.mInsertValue);
        } 
        else {
            if (mSettings.mPrevPlay != mSettings.mIsPlay && !mSinglyLinkedList.isProcessing()) {
                mSettings.mPrevPlay = 1;
                mSettings.mPrevPrev = 0;
                mSettings.mPrevNext = 1;
                mSinglyLinkedList.resetNodeState();
            }
            mSinglyLinkedList.insertAnimation(dt, 1, mSettings.mActionIndex, mSettings.mInsertValue);
        }
    } else if (mSinglyLinkedList.mDeleteActivated) {
        if (mSettings.mIsNext) {
            if (mSettings.mPrevNext != mSettings.mIsNext && !mSinglyLinkedList.isProcessing()) {
                mSettings.mPrevPrev = 0;
                mSettings.mPrevNext = 1;
                mSettings.mPrevPlay = 1;
                mSettings.mPrevAnimationOrder = mSettings.mAnimationOrder - 1;
                mSettings.mPrevColorIndex = mSettings.mColorIndex - 1;
                mSinglyLinkedList.resetNodeState();
            }
            mSinglyLinkedList.deleteAnimation(dt, 1, mSettings.mActionIndex);
        }
        else if (mSettings.mIsPrev) {  
            if (mSettings.mPrevPrev != mSettings.mIsPrev && !mSinglyLinkedList.isProcessing()) {
                mSettings.mPrevPrev = 1;
                mSettings.mPrevNext = 0;
                mSettings.mPrevPlay = 0;
                mSettings.mPrevAnimationOrder = mSettings.mAnimationOrder + 1;
                mSettings.mPrevColorIndex = mSettings.mColorIndex + 1;
                mSinglyLinkedList.resetNodeState();
            }
            mSinglyLinkedList.deleteAnimationReversed(dt, 1, mSettings.mActionIndex, mSettings.mDeleteValue);
        } 
        else {
            if (mSettings.mPrevPlay != mSettings.mIsPlay && !mSinglyLinkedList.isProcessing()) {
                mSettings.mPrevPlay = 1;
                mSettings.mPrevPrev = 0;
                mSettings.mPrevNext = 1;
                mSinglyLinkedList.resetNodeState();
            }
            mSinglyLinkedList.deleteAnimation(dt, 1, mSettings.mActionIndex);
        }
    }
    mSettings.mAnimationOrder = mSinglyLinkedList.mAnimationOrder;
    mSettings.mColorIndex = mSinglyLinkedList.mColorIndex;
    mSettings.mIsActionActivating = mSinglyLinkedList.mInsertActivated;
    mSinglyLinkedList.mIsActionPaused = mSettings.mIsActionPaused;
    mSettings.mIsEndAnimation.first = mSinglyLinkedList.mIsEndAnimation;
    mSettings.mInputArr = mSinglyLinkedList.mListData;
    if ((mSettings.mPrevAnimationOrder != mSettings.mAnimationOrder || mSettings.mColorIndex != mSettings.mPrevColorIndex) && (mSettings.mIsPrev || mSettings.mIsNext)) {
        mSettings.mPrevAnimationOrder = mSettings.mAnimationOrder;
        mSettings.mPrevColorIndex = mSettings.mColorIndex;
        mSettings.mIsActionPaused = 1;
    }
    mSinglyLinkedList.update(dt);
}
