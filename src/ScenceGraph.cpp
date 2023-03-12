#include "../header/SceneGraph.hpp"

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

// std::vector<std::unique_ptr<SceneNode>>& SceneNode::accessChildren() {
//     return mChildren;
// }

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
    updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time) {}

void SceneNode::updateChildren(sf::Time dt) {
    for (const auto& child : mChildren)
        child->update(dt);
}

void SceneNode::triggerMoveAnimation(sf::Time dt, double speed, double distance, double angleMovement) {
    this->mCurrentPos = std::sqrt(std::sqrt(distance));
    this->mMovingAnimationStep = this->mCurrentPos*dt.asSeconds()*speed;
    this->mAngleMovement = angleMovement;
    this->mAnimationType.insert(std::make_pair("move", 1));
}

LinkedListNode::LinkedListNode(int val, sf::Font &font, sf::Vector2f pos, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor) {
    std::string string = std::to_string(val);
    this->mNode.set(string, font, pos.x, pos.y, numColor, boxColor, boxOutlineColor);
}

void LinkedListNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mNode.box);
    target.draw(mNode.number);
}

void LinkedListNode::updateCurrent(sf::Time dt) {
    if (this->mAnimationType["move"]) {
        sf::Vector2f newPos(
            this->mStartPos.x + (-std::pow(this->mCurrentPos, 4) + this->mEndPos.y)*std::cos(this->mAngleMovement*std::atan(1)*4/180),
            this->mStartPos.y + (-std::pow(this->mCurrentPos, 4) + this->mEndPos.y)*std::sin(this->mAngleMovement*std::atan(1)*4/180)
        );
        this->mNode.setPos(newPos);
        if (this->mCurrentPos > 0) this->mCurrentPos -= this->mMovingAnimationStep;
        else this->mAnimationType["move"] = 0;
    }
}

void LinkedListNode::triggerMoveAnimation(sf::Time dt, double speed, double distance, double angleMovement) {
    this->mCurrentPos = std::sqrt(std::sqrt(distance));
    this->mMovingAnimationStep = this->mCurrentPos*dt.asSeconds()*speed;
    this->mAngleMovement = angleMovement;
    this->mStartPos = this->mNode.box.getPosition();
    this->mEndPos = this->mNode.box.getPosition() + sf::Vector2f(distance*std::cos(angleMovement*std::atan(1)*4/180), distance*std::sin(angleMovement*std::atan(1)*4/180));
    this->mAnimationType.insert(std::make_pair("move", 1));
}

