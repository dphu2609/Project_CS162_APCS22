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
                            if (mSinglyLinkedList.mAnimationOrder == 0) {
                                mSinglyLinkedList.mInsertActivated = 1;
                                mSinglyLinkedList.mAnimationOrder = 1;
                            }
                            break;
                        }
                        case Action::Delete : {
                            if (mSinglyLinkedList.mAnimationOrder == 0) {
                                mSinglyLinkedList.mDeleteActivated = 1;
                                mSinglyLinkedList.mAnimationOrder = 1;
                            }
                        }
                    }
                    // mSettings.activeSettings(dt);
                    mSettings.mActionActivated[Action::Play] = 0;
                }
                if (mSinglyLinkedList.mInsertActivated) mSinglyLinkedList.insertAnimation(dt, 1, mSettings.mActionIndex, mSettings.mInsertValue);
                if (mSinglyLinkedList.mDeleteActivated) mSinglyLinkedList.deleteAnimation(dt, 1, mSettings.mActionIndex);
                mSettings.mIsActionActivating = mSinglyLinkedList.mInsertActivated;
                mSinglyLinkedList.update(dt);
            }
            mSettings.update(dt);
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
