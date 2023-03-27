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
                if (mSettings.mActionActivated[Action::Play]) {
                    int index = 0;
                    for (int i = 0; i < Action::ActionCount; i++) {
                        if (mSettings.mActionActivated[i]) {
                            index = i;
                            break;
                        }
                    }
                    switch(index) {
                        case Action::Create : {
                            mSinglyLinkedList.createList(mSettings.mInputArr);
                            break;
                        }
                        case Action::Insert : {
                            mSettings.mIsEndAnimation.first = 0;
                            mSinglyLinkedList.createList(mSettings.mInputArr);
                            mSinglyLinkedList.mInsertActivated = 1;
                            mSinglyLinkedList.mColorIndex = 0;
                            mSinglyLinkedList.mAnimationOrder = 1;
                            break;
                        }
                        case Action::Delete : {
                            mSinglyLinkedList.resetNodeState(); 
                            mSinglyLinkedList.mDeleteActivated = 1;
                            mSinglyLinkedList.mColorIndex = 0;
                            mSinglyLinkedList.mAnimationOrder = 1;
                            break;
                        }
                    }
                    mSettings.mActionActivated[Action::Play] = 0;
                }
                if (mSettings.mActionActivated[Action::Insert]) {
                    if (mSettings.mIsNext) {
                        if (mSettings.mPrevNext != mSettings.mIsNext && !mSinglyLinkedList.isProcessing() && mSettings.mAnimationOrder != 7) {
                            mSettings.mPrevPrev = 0;
                            mSettings.mPrevNext = 1;
                            mSettings.mPrevPlay = 1;
                            mSettings.mPrevAnimationOrder = mSettings.mAnimationOrder - 1;
                            mSettings.mPrevColorIndex = mSettings.mColorIndex - 1;
                            mSinglyLinkedList.resetNodeState();
                            std::cout << 1;
                        }
                        mSinglyLinkedList.insertAnimation(dt, 1, mSettings.mActionIndex, mSettings.mInsertValue);
                    }
                    else if (mSettings.mIsPrev) {  
                        if (mSettings.mPrevPrev != mSettings.mIsPrev && !mSinglyLinkedList.isProcessing() && mSettings.mAnimationOrder != 7) {
                            mSettings.mPrevAnimationOrder = mSettings.mAnimationOrder + 1;
                            mSettings.mPrevColorIndex = mSettings.mColorIndex + 1;
                            mSinglyLinkedList.resetNodeState();
                            mSettings.mPrevPrev = 1;
                            mSettings.mPrevNext = 0;
                            mSettings.mPrevPlay = 0;
                            std::cout << 2;
                        }
                        mSinglyLinkedList.insertAnimationReversed(dt, 1, mSettings.mActionIndex, mSettings.mInsertValue);
                    } 
                    else {
                        if (mSettings.mPrevPlay != mSettings.mIsPlay && !mSinglyLinkedList.isProcessing()) {
                            mSettings.mPrevPlay = 1;
                            mSinglyLinkedList.resetNodeState();
                            mSettings.mPrevPrev = 0;
                            mSettings.mPrevNext = 1;
                            std::cout << 3;
                        }
                        mSinglyLinkedList.insertAnimation(dt, 1, mSettings.mActionIndex, mSettings.mInsertValue);
                    }
                }
                if (mSinglyLinkedList.mDeleteActivated) mSinglyLinkedList.deleteAnimation(dt, 1, mSettings.mActionIndex);
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
