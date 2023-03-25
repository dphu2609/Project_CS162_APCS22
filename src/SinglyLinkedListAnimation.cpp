#include <State/SinglyLinkedListState.hpp>

void LinkedListState::insertAnimation(sf::Time dt, double speed, int insertIndex, int insertData) {
    switch (mAnimationOrder) {
        case 1: {
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsColoring && !child->mIsDoneColoring) {
                    child->triggerColorAnimation(
                        dt, 100, 
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255),
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                    );
                } else if (!child->mIsColoring && child->mIsDoneColoring) {
                    child->mIsDoneColoring = 0;
                    mAnimationOrder = 2;
                }
            }
            break;
        }
        case 2: {
            if (mListData.size() == 0 || insertData == 0) {
                mAnimationOrder = 3;
                break;
            }
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == this->mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex++;
                        if (this->mColorIndex >= insertIndex) {
                            this->mColorIndex = 0;
                            mAnimationOrder = 3;
                        }
                    }
                }
                index++;
            }
            break;
        }
        case 3: {
            if (mSceneLayers[newNode]->getChildren().size() == 0) {
                if (mListData.size() > 0) {
                    std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                        insertData, mFontsHolder[Fonts::FiraSansRegular], 100,
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250, 750), 
                        sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
                    );
                    mSceneLayers[newNode]->attachChild(std::move(addedNode));
                } else {
                    std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                        insertData, mFontsHolder[Fonts::FiraSansRegular], 100,
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250, 500), 
                        sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
                    );
                    mSceneLayers[newNode]->attachChild(std::move(addedNode));
                }
            }
            for (auto &child : this->mSceneLayers[newNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250, -90);
                } else if (!child->mIsMoving && child->mIsDoneMoving) {
                    child->mIsDoneMoving = 0;
                    if (mListData.size() == 0) mAnimationOrder = 7;
                    else if (insertIndex != mListData.size()) mAnimationOrder = 4;
                    else mAnimationOrder = 5;
                }
            }
            break;
        }
        case 4: {
            if (mSceneLayers[tempArrow]->getChildren().size() == 0) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 50), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250 + 35, 490), -90
                );
                mSceneLayers[tempArrow]->attachChild(std::move(newArrow));
            }
            for (auto &child : this->mSceneLayers[tempArrow]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed, 110, 0, 0);
                } else if (!child->mIsScaling && child->mIsDoneScaling) {
                    child->mIsDoneScaling = 0;
                    if(insertIndex != 0) mAnimationOrder = 5;
                    else mAnimationOrder = 6;
                }
            }
            break;
        }
        case 5: {
            int index = 0;
            if (insertIndex == mListData.size() && this->mSceneLayers[Arrow]->getChildren().size() == mListData.size() - 1) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 50), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex - 1)*250 + 130, 285), 66.8
                );
                mSceneLayers[Arrow]->attachChild(std::move(newArrow));
            }
            for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                if (index == insertIndex - 1) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        if (insertIndex != mListData.size()) {
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
                        mAnimationOrder = 6;
                    }
                    break;
                }
                index++;
            }
            break;
        }

        case 6: {
            int index = 0;
            if (insertIndex != 0) {
                for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                    if (index == insertIndex - 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerRotateAnimation(dt, speed, -66.8);
                            child->triggerScaleAnimation(dt, speed*0.99, -(110/std::cos(66.8*std::atan(1)*4/180)) + 110, 0, 0);
                            child->triggerMoveAnimation(dt, speed*2, 25, -150);
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
                if (index >= insertIndex) {
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
                if (index >= insertIndex) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            for (auto &child : this->mSceneLayers[newNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250, -90);
                } else if (!child->mIsMoving && child->mIsDoneMoving) {
                    child->mIsDoneMoving = 0;
                    mAnimationOrder = 7;
                }
            }
            for (auto &child : this->mSceneLayers[tempArrow]->getChildren()) {
                if (!child->mIsRotating && !child->mIsDoneRotating) {
                    child->triggerRotateAnimation(dt, speed, 90);
                    child->triggerMoveAnimation(dt, speed, 225.05318547, -66.16125981683);
                } else if (!child->mIsRotating && child->mIsDoneRotating) {
                    child->mIsDoneRotating = 0;
                }
            }
            break;
        }
        case 7: {
            std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                insertData, mFontsHolder[Fonts::FiraSansRegular], 100,
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250, 250), 
                sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
            );

            mSceneLayers[Nodes]->getChildren().insert(mSceneLayers[Nodes]->getChildren().begin() + insertIndex, std::move(addedNode));
            if (mListData.size() > 0) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(110, 50), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + insertIndex*250 + 130, 285), 0
                );
                if (insertIndex != mListData.size()) mSceneLayers[Arrow]->getChildren().insert(mSceneLayers[Arrow]->getChildren().begin() + insertIndex, std::move(newArrow)); 
            }

            mListData.insert(mListData.begin() + insertIndex, insertData);

            mSceneLayers[tempArrow]->getChildren().clear();
            mSceneLayers[newNode]->getChildren().clear();

            if (mListData.size()%2 == 0) mAnimationOrder = 8;
            else {
                mInsertActivated = 0;
                mAnimationOrder = 0;
            }
            break;
        }

        case 8: {
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
                    mAnimationOrder = 0;
                    mInsertActivated = 0;
                }
            }
        }

        default:
            break;
    }
}

void LinkedListState::deleteAnimation(sf::Time dt, double speed, int deleteIndex) {
    switch (mAnimationOrder) {
        case 1: {
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsColoring && !child->mIsDoneColoring) {
                    child->triggerColorAnimation(
                        dt, 100, 
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255),
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                    );
                } else if (!child->mIsColoring && child->mIsDoneColoring) {
                    child->mIsDoneColoring = 0;
                    mAnimationOrder = 2;
                }
            }
            break;
        }
        case 2: {
            if (mListData.size() == 0 || deleteIndex == 0) {
                mAnimationOrder = 3;
                break;
            }
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == this->mColorIndex && index < deleteIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex++;
                    }
                } else if (index == this->mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, 100, 
                            sf::Color::White, sf::Color(31, 224, 205, 255), sf::Color(31, 224, 205, 255),
                            sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex++;
                        if (this->mColorIndex > deleteIndex) {
                            this->mColorIndex = 0;
                            if (deleteIndex == 0) mAnimationOrder = 4;
                            else if (deleteIndex == mListData.size()) mAnimationOrder = 4;
                            else mAnimationOrder = 3;
                        }
                    }  
                }
                index++;
            }
            break;
        }
        case 3: {
            int index = 0;
            for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                if (index == deleteIndex - 1) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed, 250, 0, 0);
                    } else if (!child->mIsScaling && child->mIsDoneScaling) {
                        child->mIsDoneScaling = 0;
                    }
                }
                if (index == deleteIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerRotateAnimation(dt, speed, -66.8);
                        child->triggerScaleAnimation(dt, speed, (110/std::cos(66.8*std::atan(1)*4/180)) - 110, 0, 0);
                        child->triggerMoveAnimation(dt, speed, 270, 94.5);
                    } else if (!child->mIsScaling && child->mIsDoneScaling) {
                        child->mIsDoneScaling = 0;
                        child->mIsDoneMoving = 0;
                        child->mIsDoneRotating = 0;
                        mAnimationOrder = 4;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == deleteIndex) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 90);
                    } else if (!child->mIsMoving && child->mIsDoneMoving) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            break;
        }

        case 4: {
            int index = 0;
            for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                if (index == deleteIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*2, -(110/std::cos(66.8*std::atan(1)*4/180)), speed, -50);
                    } else if (!child->mIsScaling && child->mIsDoneScaling) {
                        mAnimationOrder = 5;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == deleteIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*1.5, -100, 0, 0);
                    }
                }
                index++;
            }
            break;
        }

        default:
            break;
    }
}