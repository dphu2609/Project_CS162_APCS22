#include <SceneGraph/DisplayNode.hpp>

DisplayNode::DisplayNode(int val, sf::Font &font, double size, sf::Vector2f pos, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor) {
    std::string string = std::to_string(val);
    this->mNode.set(string, font, size, pos, numColor, boxColor, boxOutlineColor);
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
    if (this->mAnimationType["color"]) {
        mStartTime += mClock.restart().asSeconds();
        if (mStartTime > mTimeChange) {
            this->mNode.setColor(mTextColorAfterChange, mBoxColorAfterChange, mOutlineColorAfterChange);
            this->mIsColoring = 0;
            this->mIsDoneColoring = 1;
            this->mStartTime = 0;
            this->mAnimationType["color"] = 0;
        }
    } else {
        mClock.restart();
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

void DisplayNode::triggerColorAnimation(
    sf::Time dt, double speed, 
    sf::Color textColorWhenChange, sf::Color boxColorWhenChange, sf::Color outlineColorWhenChange, 
    sf::Color textColorAfterChange, sf::Color boxColorAfterChange, sf::Color outlineColorAfterChange
) {
    this->mTextColorWhenChange = textColorWhenChange;
    this->mTextColorAfterChange = textColorAfterChange;
    this->mBoxColorWhenChange = boxColorWhenChange;
    this->mBoxColorAfterChange = boxColorAfterChange;
    this->mOutlineColorWhenChange = outlineColorWhenChange;
    this->mOutlineColorAfterChange = outlineColorAfterChange;
    this->mTimeChange = 0.5/speed;
    this->mIsColoring = 1;
    this->mIsDoneColoring = 0;
    this->mAnimationType["color"] = 1;
    this->mNode.setColor(textColorWhenChange, boxColorWhenChange, outlineColorWhenChange);
}