#include <SceneGraph/DisplayNode.hpp>

DisplayNode::DisplayNode(int val, sf::Font &font, sf::Vector2f pos, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor) {
    std::string string = std::to_string(val);
    this->mNode.set(string, font, pos.x, pos.y, numColor, boxColor, boxOutlineColor);
}

void DisplayNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mNode.box);
    target.draw(mNode.number);
}

void DisplayNode::updateCurrent(sf::Time dt) {
    if (this->mAnimationType["move"]) {
        sf::Vector2f newPos(
            this->mStartPos.x + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::cos(this->mAngleMovement*std::atan(1)*4/180),
            this->mStartPos.y + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::sin(this->mAngleMovement*std::atan(1)*4/180)
        );
        this->mNode.setPos(newPos);
        if (this->mCurrentPos > 0) this->mCurrentPos -= this->mMovingStep;
        else {
            this->mAnimationType["move"] = 0;
            this->mIsMoving = 0;
            this->mIsDoneMoving = 1;
        }
    }
}

void DisplayNode::triggerMoveAnimation(sf::Time dt, double speed, double moveDistance, double angleMovement) {
    this->mCurrentPos = std::sqrt(std::sqrt(moveDistance));
    this->mMovingStep = this->mCurrentPos*dt.asSeconds()*speed;
    this->mAngleMovement = angleMovement;
    this->mStartPos = this->mNode.box.getPosition();
    this->mMovingDistance = moveDistance;
    this->mAnimationType["move"] = 1;
    this->mIsMoving = 1;
    this->mIsDoneMoving = 0;
}