#include <State/LinkedListState.hpp>

void LinkedListState::addAnimation(sf::Time dt, double speed) {
    switch (animationOrder) {
        case 1: {
            for (auto &child : this->mSceneLayers[newNode]->getChildren()) {
                if (!child->mIsMoving) {
                    child->mIsDoneMoving = 0;
                    if (addIndex != arr.size()) animationOrder = 2;
                    else animationOrder = 3;
                }
                return;
            }
            std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                addValue, mFontsHolder[Fonts::FiraSansRegular], 100,
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (arr.size()/2)*250 + (addIndex)*250, 750), 
                sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
            );
            addedNode->triggerMoveAnimation(dt, speed, 250, -90);
            mSceneLayers[newNode]->attachChild(std::move(addedNode));
            break;
        }
        case 2: {
            for (auto &child : this->mSceneLayers[tempArrow]->getChildren()) {
                if (child->mIsDoneScaling) {
                    child->mIsDoneScaling = 0;
                    if(addIndex != 0) animationOrder = 3;
                    else animationOrder = 4;
                }
                return;
            }
            std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 50), 
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (arr.size()/2)*250 + (addIndex)*250 + 35, 500), -90
            );
            newArrow->triggerScaleAnimation(dt, speed, 110, 0, 0);
            mSceneLayers[tempArrow]->attachChild(std::move(newArrow));
            break;
        }
        case 3: {
            int index = 0;
            if (addIndex == arr.size()) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 50), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (arr.size()/2)*250 + (addIndex - 1)*250 + 130, 285), 66.8
                );
                mSceneLayers[Arrow]->attachChild(std::move(newArrow));
            }
            for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                if (index == addIndex - 1) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        if (addIndex != arr.size()) {
                            child->triggerRotateAnimation(dt, speed, 66.8);
                            child->triggerScaleAnimation(dt, speed*0.8, (110/std::cos(66.8*std::atan(1)*4/180)) - 110, 0, 0);
                        }
                        else {
                            child->triggerScaleAnimation(dt, speed*0.8, (110/std::cos(66.8*std::atan(1)*4/180)), 0, 0);
                        }
                        child->triggerMoveAnimation(dt, speed*2, 25, 30);
                    } 
                    else if (!child->mIsScaling && child->mIsDoneScaling) {
                        child->mIsDoneScaling = 0;
                        child->mIsDoneRotating = 0;
                        animationOrder = 4;
                    }
                    return;
                }
                index++;
            }
            break;
        }

        case 4: {
            int index = 0;
            if (addIndex != 0) {
                for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                    if (index == addIndex - 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerRotateAnimation(dt, speed, -66.8);
                            child->triggerScaleAnimation(dt, speed*0.99, -(110/std::cos(66.8*std::atan(1)*4/180)) + 110, 0, 0);
                            child->triggerMoveAnimation(dt, speed*2, 25, -150);
                            std::cout << 1;
                        } else if (!child->mIsScaling && child->mIsDoneScaling) {
                            child->mIsDoneMoving = 0;
                            child->mIsDoneScaling = 0;
                            child->mIsDoneRotating = 0;
                        }
                        break;
                    }
                    index++;
                }
            }
            index = 0;
            for (auto &child : this->mSceneLayers[Nodes]->getChildren()) {
                if (index >= addIndex) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                if (index >= addIndex && index < arr.size() - 1) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving) {
                        child->mIsDoneMoving = 0;
                        animationOrder = 5;
                    }
                }
                index++;
            }
            for (auto &child : this->mSceneLayers[newNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250, -90);
                }
            }
            for (auto &child : this->mSceneLayers[tempArrow]->getChildren()) {
                if (!child->mIsRotating && !child->mIsDoneRotating) {
                    child->triggerRotateAnimation(dt, speed, 90);
                    child->triggerMoveAnimation(dt, speed, std::sqrt(215*215 + 95*95), -std::atan(215.0/95)*180/(std::atan(1)*4));
                } 
            }
            break;
        }
        case 5: {
            std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                addValue, mFontsHolder[Fonts::FiraSansRegular], 100,
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (arr.size()/2)*250 + (addIndex)*250, 250), 
                sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
            );

            mSceneLayers[Nodes]->getChildren().insert(mSceneLayers[Nodes]->getChildren().begin() + addIndex, std::move(addedNode));
            std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                mTexturesHolder[Textures::rightArrow], sf::Vector2f(110, 50), 
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (arr.size()/2)*250 + addIndex*250 + 130, 285), 0
            );
            if (addIndex != arr.size()) mSceneLayers[Arrow]->getChildren().insert(mSceneLayers[Arrow]->getChildren().begin() + addIndex, std::move(newArrow));

            arr.insert(arr.begin() + addIndex, addValue);

            mSceneLayers[tempArrow]->getChildren().clear();
            mSceneLayers[newNode]->getChildren().clear();

            if (arr.size()%2 == 0) animationOrder = 6;
            else isAdd = 0;
            break;
        }

        case 6: {
            for (auto &child : this->mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250, 180);
                } else if (!child->mIsMoving && child->mIsDoneMoving) {
                    child->mIsDoneMoving = 0;
                }
            }
            for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250, 180);
                } else if (!child->mIsMoving && child->mIsDoneMoving) {
                    child->mIsDoneMoving = 0;
                    isAdd = 0;
                }
            }
        }
    }
}