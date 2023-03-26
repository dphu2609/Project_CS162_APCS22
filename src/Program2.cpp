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
                            mSinglyLinkedList.mInsertActivated = 1;
                            mSinglyLinkedList.mAnimationOrder = 1;
                            break;
                        }
                        case Action::Delete : {
                            mSinglyLinkedList.mDeleteActivated = 1;
                            mSinglyLinkedList.mAnimationOrder = 1;
                            break;
                        }
                    }
                    if (mSettings.mIsReplayAction) {
                        mSinglyLinkedList.createList(mSettings.mInputArr);
                        mSettings.mIsReplayAction = 0;
                    }
                    mSettings.mActionActivated[Action::Play] = 0;
                }
                if (mSinglyLinkedList.mInsertActivated) mSinglyLinkedList.insertAnimation(dt, 1, mSettings.mActionIndex, mSettings.mInsertValue);
                if (mSinglyLinkedList.mDeleteActivated) mSinglyLinkedList.deleteAnimation(dt, 1, mSettings.mActionIndex);
                mSettings.mAnimationOrder = mSinglyLinkedList.mAnimationOrder;
                mSettings.mIsActionActivating = mSinglyLinkedList.mInsertActivated;
                mSinglyLinkedList.mIsActionPaused = mSettings.mIsActionPaused;
                mSettings.mColorIndex = mSinglyLinkedList.mColorIndex;
                mSettings.mIsEndAnimation.first = mSinglyLinkedList.mIsEndAnimation;
                mSettings.mInputArr = mSinglyLinkedList.mListData;
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
