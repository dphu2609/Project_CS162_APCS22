#include <SceneGraph/ContainerNode.hpp>

ContainerNode :: ContainerNode(sf::RenderWindow &window, sf::Vector2f size, double outlineSize, sf::Vector2f pos, sf::Color boxColor, sf::Color boxOutlineColor) : mWindow(window) {
    this->mBox.setSize(size);
    this->mBox.setPosition(pos);
    this->mBox.setFillColor(boxColor);
    this->mBox.setOutlineThickness(outlineSize);
    this->mBox.setOutlineColor(boxOutlineColor);
}

void ContainerNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->mBox);
}

void ContainerNode::updateCurrent(sf::Time dt) {
    if (this->mAnimationType["move"]) {
        sf::Vector2f newPos(
            this->mStartPos.x + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::cos(this->mAngleMovement*std::atan(1)*4/180),
            this->mStartPos.y + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::sin(this->mAngleMovement*std::atan(1)*4/180)
        );
        this->mBox.setPosition(newPos);
        if (this->mCurrentPos > 0) this->mCurrentPos -= this->mMovingStep;
        else {
            this->mAnimationType["move"] = 0;
            this->mIsMoving = 0;
            this->mIsDoneMoving = 1;
        }
    }
}

void ContainerNode::triggerMoveAnimation(sf::Time dt, double speed, double moveDistance, double angleMovement) {
    this->mCurrentPos = std::sqrt(std::sqrt(moveDistance));
    this->mMovingStep = this->mCurrentPos*dt.asSeconds()*speed;
    this->mAngleMovement = angleMovement;
    this->mStartPos = this->mBox.getPosition();
    this->mMovingDistance = moveDistance;
    this->mAnimationType["move"] = 1;
    this->mIsMoving = 1;
    this->mIsDoneMoving = 0;
}