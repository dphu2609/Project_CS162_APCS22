#include <State/State.hpp>

State::State(sf::RenderWindow &window) : mWindow(window) {}

void State::draw() {
    mWindow.draw(mSceneGraph);
}

void State::update(sf::Time dt) {
    mSceneGraph.update(dt);
} 

void State::handleEvent(sf::Event &event) {
    mSceneGraph.handleEvent(event);
}