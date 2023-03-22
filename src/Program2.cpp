#include <Program2.hpp>

Program2::Program2() : mWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Data Visual", sf::Style::Default), mMenu(mWindow), mSettings(mWindow) {
    mMenu.isAdd = 0;
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
            if (mSettings.mIsStateActivated[States::SinglyLinkedList]) {
                if (mMenu.isAdd) mMenu.addAnimation(dt, 1);
                mMenu.update(dt);
            }
            mSettings.activeSettings(dt);
            mSettings.update(dt);
        }
        mWindow.clear();
        if (mSettings.mIsStateActivated[States::SinglyLinkedList]) mMenu.draw();
        mSettings.draw();
        mWindow.display();
    }
}

void Program2::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        mSettings.handleEvent(event);
        mSettings.handleInput(event);
        mMenu.handleClick(event);
        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}
