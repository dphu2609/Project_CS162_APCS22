#include <SceneGraph/SceneNode.hpp>

SceneNode::SceneNode() {
    this->mParent = nullptr;
}

void SceneNode::attachChild(Ptr child) {
    child->mParent = this;
    mChildren.emplace_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node) {
    auto found = std::find_if(mChildren.begin(), mChildren.end(),
        [&] (Ptr& p) -> bool { return p.get() == &node; });

    assert(found != mChildren.end());

    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;
}


void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    drawCurrent(target, states);
    for (const auto& child : mChildren) {
        if (child) 
            child->draw(target, states);
    }
}
void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {}

void SceneNode::update(sf::Time dt) {
    updateCurrent(dt);
    for (const auto& child : mChildren) child->update(dt);
}

void SceneNode::handleEvent(sf::Event &event) {
    handleCurrentEvent(event);
    for (const auto& child : mChildren) child->handleEvent(event);
}

void SceneNode::updateCurrent(sf::Time dt) {}

void SceneNode::handleCurrentEvent(sf::Event &event) {}

void SceneNode::triggerMoveAnimation(sf::Time dt, double speed, double moveDistance, double angleMovement) {}

void SceneNode::triggerRotateAnimation(sf::Time dt, double speed, double rotatingDistance) {}

void SceneNode::triggerScaleAnimation(sf::Time dt, double lengthSpeed, double scalingLengthDistance, double widthSpeed, double scalingWidthDistance) {}



