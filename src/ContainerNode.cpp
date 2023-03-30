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
    if (this->mAnimationType["scale"]) {
        sf::Vector2f newSize;
        if (this->mScalingLengthDistance >= 0) {
            newSize.x = this->mStartScale.x + -std::pow(this->mCurrentLengthScale, 4) + this->mScalingLengthDistance;
        } else {
            newSize.x = this->mStartScale.x + std::pow(this->mCurrentLengthScale, 4) + this->mScalingLengthDistance;
        }
        if (this->mScalingWidthDistance >= 0) {
            newSize.y = this->mStartScale.y + -std::pow(this->mCurrentWidthScale, 4) + this->mScalingWidthDistance;
        } else {
            newSize.y = this->mStartScale.y + std::pow(this->mCurrentWidthScale, 4) + this->mScalingWidthDistance;
        }
        this->mBox.setSize(newSize);
        if (this->mCurrentLengthScale > 0) this->mCurrentLengthScale -= this->mScalingLengthStep;
        if (this->mCurrentWidthScale > 0) this->mCurrentWidthScale -= this->mScalingWidthStep;
        if (this->mCurrentLengthScale <= 0 && this->mCurrentWidthScale <= 0) {
            this->mAnimationType["scale"] = 0;
            this->mIsScaling = 0; 
            this->mIsDoneScaling = 1;
        }
    }
    if (this->mAnimationType["color"]) {
        mStartTime += mClock.restart().asSeconds();
        if (mStartTime > mTimeChange) {
            this->mBox.setFillColor(mBoxColorAfterChange);
            this->mBox.setOutlineColor(mOutlineColorAfterChange);
            this->mIsColoring = 0;
            this->mIsDoneColoring = 1;
            this->mStartTime = 0;
            this->mAnimationType["color"] = 0;
        }
    } else {
        mClock.restart();
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

void ContainerNode::triggerScaleAnimation(sf::Time dt, double lengthSpeed, double scalingLengthDistance, double widthSpeed, double scalingWidthDistance) {
    this->mCurrentLengthScale = std::sqrt(std::sqrt(std::abs(scalingLengthDistance)));
    this->mScalingLengthStep = this->mCurrentLengthScale*dt.asSeconds()*lengthSpeed;
    this->mScalingLengthDistance = scalingLengthDistance;

    this->mCurrentWidthScale = std::sqrt(std::sqrt(std::abs(scalingWidthDistance)));
    this->mScalingWidthStep = this->mCurrentWidthScale*dt.asSeconds()*widthSpeed;
    this->mScalingWidthDistance = scalingWidthDistance;

    this->mStartScale = this->mBox.getSize();
    this->mAnimationType["scale"] = 1;
    this->mIsScaling = 1;
    this->mIsDoneScaling = 0;
}

void ContainerNode::triggerColorAnimation(
    sf::Time dt, double speed, 
    sf::Color textColorWhenChange, sf::Color boxColorWhenChange, sf::Color outlineColorWhenChange, 
    sf::Color textColorAfterChange, sf::Color boxColorAfterChange, sf::Color outlineColorAfterChange
) {
    this->mBoxColorWhenChange = boxColorWhenChange;
    this->mBoxColorAfterChange = boxColorAfterChange;
    this->mOutlineColorWhenChange = outlineColorWhenChange;
    this->mOutlineColorAfterChange = outlineColorAfterChange;
    this->mTimeChange = 0.75/speed;
    this->mIsColoring = 1;
    this->mIsDoneColoring = 0;
    this->mAnimationType["color"] = 1;
    this->mBox.setFillColor(boxColorWhenChange);
    this->mBox.setOutlineColor(outlineColorAfterChange);
}