#include <SceneGraph/SpriteNode.hpp>

SpriteNode::SpriteNode(sf::Texture &texture, sf::Vector2f size, sf::Vector2f pos, double rotation) {
    this->mSprite.setTexture(texture);
    sf::Vector2f scale(size.x / this->mSprite.getLocalBounds().width, size.y / this->mSprite.getLocalBounds().height);
    this->mSprite.setScale(scale);
    this->mSprite.setPosition(pos);
    this->mSprite.setRotation(rotation);
}

void SpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->mSprite);
}   

void SpriteNode::updateCurrent(sf::Time dt) {
    if (this->mAnimationType["move"]) {
        sf::Vector2f newPos(
            this->mStartPos.x + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::cos(this->mAngleMovement*std::atan(1)*4/180),
            this->mStartPos.y + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::sin(this->mAngleMovement*std::atan(1)*4/180)
        );
        this->mSprite.setPosition(newPos);
        if (this->mCurrentPos > 0) this->mCurrentPos -= this->mMovingStep;
        else {
            this->mAnimationType["move"] = 0;
            this->mIsMoving = 0;
        }
    }
    if (this->mAnimationType["rotate"]) {
        double newAngle = this->mStartAngle - std::pow(this->mCurrentAngle, 4) + this->mRotatingDistance;
        this->mSprite.setRotation(newAngle);
        if (this->mCurrentAngle > 0) this->mCurrentAngle -= this->mRotatingStep;
        else {
            this->mAnimationType["rotate"] = 0;
            this->mIsRotating = 0;
        }
    }
    if (this->mAnimationType["scale"]) {
        sf::Vector2f newScale = this->mStartScale + sf::Vector2f(
                (-std::pow(this->mCurrentLengthScale, 4) + this->mScalingLengthDistance) / this->mSprite.getLocalBounds().width, 
                (-std::pow(this->mCurrentWidthScale, 4) + this->mScalingWidthDistance) / this->mSprite.getLocalBounds().height
            );
        this->mSprite.setScale(newScale);
        if (this->mCurrentLengthScale > 0) this->mCurrentLengthScale -= this->mScalingLengthStep;
        if (this->mCurrentWidthScale > 0) this->mCurrentWidthScale -= this->mScalingWidthStep;
        if (this->mCurrentLengthScale <= 0 && this->mCurrentWidthScale <= 0) {
            this->mAnimationType["scale"] = 0;
            this->mIsScaling = 0; 
        }
    }
}

void SpriteNode::triggerMoveAnimation(sf::Time dt, double speed, double moveDistance, double angleMovement) {
    this->mCurrentPos = std::sqrt(std::sqrt(moveDistance));
    this->mMovingStep = this->mCurrentPos*dt.asSeconds()*speed;
    this->mAngleMovement = angleMovement;
    this->mStartPos = this->mSprite.getPosition();
    this->mMovingDistance = moveDistance;
    this->mAnimationType.insert(std::make_pair("move", 1));
    this->mIsMoving = 1;
}

void SpriteNode::triggerRotateAnimation(sf::Time dt, double speed, double rotatingDistance) {
    this->mCurrentAngle = std::sqrt(std::sqrt(rotatingDistance));
    this->mRotatingStep = this->mCurrentAngle*dt.asSeconds()*speed;
    this->mStartAngle = this->mSprite.getRotation();
    this->mRotatingDistance = rotatingDistance;
    this->mAnimationType.insert(std::make_pair("rotate", 1));
    this->mIsRotating = 1;
}

void SpriteNode::triggerScaleAnimation(sf::Time dt, double lengthSpeed, double scalingLengthDistance, double widthSpeed, double scalingWidthDistance) {
    this->mCurrentLengthScale = std::sqrt(std::sqrt(scalingLengthDistance));
    this->mScalingLengthStep = this->mCurrentLengthScale*dt.asSeconds()*lengthSpeed;
    this->mScalingLengthDistance = scalingLengthDistance;

    this->mCurrentWidthScale = std::sqrt(std::sqrt(scalingWidthDistance));
    this->mScalingWidthStep = this->mCurrentWidthScale*dt.asSeconds()*widthSpeed;
    this->mScalingWidthDistance = scalingWidthDistance;

    this->mStartScale = this->mSprite.getScale();
    this->mAnimationType.insert(std::make_pair("scale", 1));
    this->mIsScaling = 1;
}
