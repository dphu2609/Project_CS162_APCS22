#include <SceneGraph/SceneNode.hpp>

SceneNode::SceneNode() {
    this->mParent = nullptr;
}

void SceneNode::attachChild(Ptr child) {
    child->mParent = this;
    mChildren.emplace_back(std::move(child));
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    drawCurrent(target, states);
    for (const auto& child : mChildren) {
        if (child) 
            child->draw(target, states);
    }
}

void SceneNode::update(sf::Time dt) {
    updateCurrent(dt);
    for (const auto& child : mChildren) child->update(dt);
}

void SceneNode::handleEvent(sf::Event &event) {
    handleCurrentEvent(event);
    for (const auto& child : mChildren) child->handleEvent(event);
}



