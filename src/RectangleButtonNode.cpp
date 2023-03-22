#include <SceneGraph/RectangleButtonNode.hpp>

RectangleButtonNode::RectangleButtonNode(sf::RenderWindow &window, const std::string text, const sf::Font &font, sf::Vector2f boxSize, 
        double outlineSize, sf::Vector2f pos, sf::Color textColor, sf::Color boxColor, 
        sf::Color boxOutlineColor, sf::Color textColorHoverred, sf::Color boxColorHoverred, sf::Color boxOutlineColorHoverred
) : mWindow(window) {
    this->mButton.set(text, font, boxSize, outlineSize, pos, textColor, boxColor, boxOutlineColor, textColorHoverred, boxColorHoverred, boxOutlineColorHoverred);
}

void RectangleButtonNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    if (evn::isHoverred(this->mWindow, this->mButton.mBox)) {   
        target.draw(this->mButton.mBoxHoverred);
        target.draw(this->mButton.mTextHoverred);
    }
    else {
        target.draw(this->mButton.mBox);
        target.draw(this->mButton.mText);
    }
}

void RectangleButtonNode::updateCurrent(sf::Time dt) {
    if (this->mAnimationType["move"]) {
        sf::Vector2f newPos(
            this->mStartPos.x + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::cos(this->mAngleMovement*std::atan(1)*4/180),
            this->mStartPos.y + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::sin(this->mAngleMovement*std::atan(1)*4/180)
        );
        this->mButton.setPosition(newPos);
        if (this->mCurrentPos > 0) this->mCurrentPos -= this->mMovingStep;
        else {
            this->mAnimationType["move"] = 0;
            this->mIsMoving = 0;
            this->mIsDoneMoving = 1;
        }
    }
}

void RectangleButtonNode::triggerMoveAnimation(sf::Time dt, double speed, double moveDistance, double angleMovement) {
    this->mCurrentPos = std::sqrt(std::sqrt(moveDistance));
    this->mMovingStep = this->mCurrentPos*dt.asSeconds()*speed;
    this->mAngleMovement = angleMovement;
    this->mStartPos = this->mButton.mBox.getPosition();
    this->mMovingDistance = moveDistance;
    this->mAnimationType["move"] = 1;
    this->mIsMoving = 1;
    this->mIsDoneMoving = 0;
}

int RectangleButtonNode::getClickedIndex(sf::Event &event) {
    if (evn::isLeftClicked(mWindow, event, this->mButton.mBox)) {
        return 0;
    }
    return -1;
}