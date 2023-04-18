#include <SceneGraph/ImageButtonNode.hpp>

ImageButtonNode::ImageButtonNode(sf::RenderWindow &window, sf::Texture &originalButtonTexture, sf::Texture &hoveredButtonTexture, sf::Vector2f size, sf::Vector2f pos) : mWindow(window) {
    this->mButton.set(originalButtonTexture, hoveredButtonTexture, size.x, size.y, pos);
}

void ImageButtonNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    if (evn::isHovered(this->mWindow, this->mButton.originalButton)) {
        target.draw(this->mButton.hoveredButton);
    }
    else target.draw(this->mButton.originalButton);
}

void ImageButtonNode::updateCurrent(sf::Time dt) {
    if (this->mAnimationType["move"]) {
        sf::Vector2f newPos(
            this->mStartPos.x + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::cos(this->mAngleMovement*std::atan(1)*4/180),
            this->mStartPos.y + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::sin(this->mAngleMovement*std::atan(1)*4/180)
        );
        this->mButton.originalButton.setPosition(newPos);
        this->mButton.hoveredButton.setPosition(newPos);
        if (this->mCurrentPos > 0) this->mCurrentPos -= this->mMovingStep;
        else {
            this->mAnimationType["move"] = 0;
            this->mIsMoving = 0;
            this->mIsDoneMoving = 1;
        }
    }
}

int ImageButtonNode::getClickedIndex(sf::Event &event) {
    if (evn::isLeftClicked(mWindow, event, this->mButton.originalButton)) {
        return 0;
    }
    return -1;
}

void ImageButtonNode::triggerMoveAnimation(sf::Time dt, double speed, double moveDistance, double angleMovement) {
    this->mCurrentPos = std::sqrt(std::sqrt(moveDistance));
    this->mMovingStep = this->mCurrentPos*dt.asSeconds()*speed;
    this->mAngleMovement = angleMovement;
    this->mStartPos = this->mButton.originalButton.getPosition();
    this->mMovingDistance = moveDistance;
    this->mAnimationType["move"] = 1;
    this->mIsMoving = 1;
    this->mIsDoneMoving = 0;
}