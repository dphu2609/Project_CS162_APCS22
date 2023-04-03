#include <State/CLLState.hpp>

void CLLState::createDataStructure(std::vector<int> list) {
    for (int i = 0; i < LayerCount; i++) {
        mSceneLayers[i]->getChildren().clear();
    }
    if (list.size() == 0) return;
    mListData = list;
    for (int i = 0; i < mListData.size(); i++) {
        std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
            mListData[i], mFontsHolder[Fonts::FiraSansRegular], 100, 
            sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + i*250, 250), 
            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
        );
        mSceneLayers[Nodes]->attachChild(std::move(newNode));
    }
    
    for (int i = 0; i < mListData.size(); i++) {
        std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
            mTexturesHolder[Textures::rightArrow], sf::Vector2f(110, 50), 
            sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + i*250 - 120, 285), 0
        );
        mSceneLayers[Arrow]->attachChild(std::move(newArrow));
    }

    std::unique_ptr<ContainerNode> newCLLArrow1st = std::make_unique<ContainerNode>(
        mWindow, sf::Vector2f(110, 5), 0, sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + mListData.size()*250 - 130, 305),
        sf::Color(240, 114, 53, 255), sf::Color::Transparent
    );
    mSceneLayers[CLLArrow]->attachChild(std::move(newCLLArrow1st));

    std::unique_ptr<ContainerNode> newCLLArrow2nd = std::make_unique<ContainerNode>(
        mWindow, sf::Vector2f(5, 175), 0, sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + mListData.size()*250 - 20, 135),
        sf::Color(240, 114, 53, 255), sf::Color::Transparent
    );
    mSceneLayers[CLLArrow]->attachChild(std::move(newCLLArrow2nd));

    std::unique_ptr<ContainerNode> newCLLArrow3rd = std::make_unique<ContainerNode>(
        mWindow, sf::Vector2f(mListData.size()*250 + 100, 5), 0, sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 - 120, 135),
        sf::Color(240, 114, 53, 255), sf::Color::Transparent
    );
    mSceneLayers[CLLArrow]->attachChild(std::move(newCLLArrow3rd));

    std::unique_ptr<ContainerNode> newCLLArrow4th = std::make_unique<ContainerNode>(
        mWindow, sf::Vector2f(5, 175), 0, sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 - 120, 135),
        sf::Color(240, 114, 53, 255), sf::Color::Transparent
    );
    mSceneLayers[CLLArrow]->attachChild(std::move(newCLLArrow4th));
}

void CLLState::insertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::SinglyLinkedListInsert])) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::CircularLinkedListInsert], mFontsHolder[Fonts::FiraMonoRegular], 25,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::CircularLinkedListInsert] = 1;
    }
    switch (mAnimationOrder) {
        case 1: {
            if (mListData.size() == 0) {
                mAnimationOrder = 3;
                break;
            }
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsColoring && !child->mIsDoneColoring) {
                    child->triggerColorAnimation(
                        dt, 1, 
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255),
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                    );
                    // mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    // mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({7});
                } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                    child->mIsDoneColoring = 0;
                    mAnimationOrder = 2;
                }
            }
            break;
        }
        case 2: {
            if (mListData.size() == 0) {
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
                        // mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        // mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({8, 9, 10});
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex++;
                        if (insertIndex != 0 && this->mColorIndex >= insertIndex) {
                            this->mColorIndex--;
                            mAnimationOrder = 3;
                            break;
                        } else if (this->mColorIndex >= mListData.size() && insertIndex == 0) {
                            this->mColorIndex--;
                            mAnimationOrder = 3;
                            break;
                        }
                    }
                }
                index++;
            }
            break;
        }
        case 3: {
            if (mSceneLayers[NewNode]->getChildren().size() == 0) {
                if (mListData.size() > 0) {
                    std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                        insertValue, mFontsHolder[Fonts::FiraSansRegular], 100,
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250, 750), 
                        sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
                    );
                    mSceneLayers[NewNode]->attachChild(std::move(addedNode));
                } else {
                    std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                        insertValue, mFontsHolder[Fonts::FiraSansRegular], 100,
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250, 500), 
                        sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
                    );
                    mSceneLayers[NewNode]->attachChild(std::move(addedNode));
                    mAnimationOrder = 6;
                    break;
                }
            }
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250, -90);
                    // mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    // mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({11});

                } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                    child->mIsDoneMoving = 0;
                    if (insertIndex != mListData.size()) mAnimationOrder = 4;
                    else mAnimationOrder = 7;
                }
            }
            break;
        }
        case 4: {
            if (mSceneLayers[NewArrow]->getChildren().size() == 0) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 50), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250 + 35, 490), -90
                );
                mSceneLayers[NewArrow]->attachChild(std::move(newArrow));
            }
            for (auto &child : this->mSceneLayers[NewArrow]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed, 110, 0, 0);
                    // mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    // mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({12});
                } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                    child->mIsDoneScaling = 0;
                    mAnimationOrder = 5;
                }
            }
            break;
        }
        case 5: {
            int index = 0;
            for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                if (index == insertIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerRotateAnimation(dt, speed, 66.8);
                        child->triggerScaleAnimation(dt, speed*0.8, (110/std::cos(66.8*std::atan(1)*4/180)) - 110, 0, 0);
                        child->triggerMoveAnimation(dt, speed*2, 25, 30);
                        // mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        // mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({13});
                    } 
                    else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        child->mIsDoneRotating = 0;
                        child->mIsDoneMoving = 0;
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
            if (insertIndex != mListData.size()) {
                for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                    if (index == insertIndex) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerRotateAnimation(dt, speed, -66.8);
                            child->triggerScaleAnimation(dt, speed*0.99, -(110/std::cos(66.8*std::atan(1)*4/180)) + 110, 0, 0);
                            child->triggerMoveAnimation(dt, speed*2, 25, -150);
                            // mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            // mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({14});
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
                if (index >= insertIndex + 1) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250, -90);
                } else if (!child->mIsMoving && child->mIsDoneMoving) {
                    child->mIsDoneMoving = 0;
                    mAnimationOrder = 9;
                }
            }
            for (auto &child : this->mSceneLayers[NewArrow]->getChildren()) {
                if (!child->mIsRotating && !child->mIsDoneRotating) {
                    child->triggerRotateAnimation(dt, speed, 90);
                    child->triggerMoveAnimation(dt, speed, 225.05318547, -66.16125981683);
                } else if (!child->mIsRotating && child->mIsDoneRotating) {
                    child->mIsDoneRotating = 0;
                }
            }
            index = 0;
            for (auto &child : mSceneLayers[CLLArrow]->getChildren()) {
                if (index == 0 || index == 1) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving) {
                        child->mIsDoneMoving = 0;
                    }
                } else if (index == 2) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed, 250, 0, 0);
                    }
                }
                index++;
            }
            break;
        }
        case 7: {
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250, -90);
                } else if (!child->mIsMoving && child->mIsDoneMoving) {
                    child->mIsDoneMoving = 0;
                    mAnimationOrder = 8;
                }
            }
            int index = 0;
            for (auto &child : mSceneLayers[CLLArrow]->getChildren()) {
                if (index == 0 || index == 1) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving) {
                        child->mIsDoneMoving = 0;
                    }
                } else if (index == 2) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed, 250, 0, 0);
                    }
                }
                index++;
            }
            break;
        }
        case 8: {
            if (mSceneLayers[Arrow]->getChildren().size() == mListData.size()) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 50), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + mListData.size()*250 - 120, 285), 0
                );
                mSceneLayers[Arrow]->attachChild(std::move(newArrow));
            }
            int index = 0;
            for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                if (index == mListData.size()) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed, 110, 0, 0);
                        std::cout << 1;
                    } else if (!child->mIsScaling && child->mIsDoneScaling) {
                        child->mIsDoneMoving = 0;
                        mAnimationOrder = 9;
                    }
                }
                index++;
            }
            break;
        }
        case 9: {
            std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                insertValue, mFontsHolder[Fonts::FiraSansRegular], 100,
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250, 250), 
                sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
            );

            mSceneLayers[Nodes]->getChildren().insert(mSceneLayers[Nodes]->getChildren().begin() + insertIndex, std::move(addedNode));
            if (insertIndex != mListData.size()) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(110, 50), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex + 1)*250 - 120, 285), 0
                );
                mSceneLayers[Arrow]->getChildren().insert(mSceneLayers[Arrow]->getChildren().begin() + insertIndex + 1, std::move(newArrow)); 
            }

            mListData.insert(mListData.begin() + insertIndex, insertValue);

            if (mListData.size() == 1) {
                std::unique_ptr<ContainerNode> newCLLArrow1st = std::make_unique<ContainerNode>(
                    mWindow, sf::Vector2f(110, 5), 0, sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + mListData.size()*250 - 130, 305),
                    sf::Color(240, 114, 53, 255), sf::Color::Transparent
                );
                mSceneLayers[CLLArrow]->attachChild(std::move(newCLLArrow1st));

                std::unique_ptr<ContainerNode> newCLLArrow2nd = std::make_unique<ContainerNode>(
                    mWindow, sf::Vector2f(5, 175), 0, sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + mListData.size()*250 - 20, 135),
                    sf::Color(240, 114, 53, 255), sf::Color::Transparent
                );
                mSceneLayers[CLLArrow]->attachChild(std::move(newCLLArrow2nd));

                std::unique_ptr<ContainerNode> newCLLArrow3rd = std::make_unique<ContainerNode>(
                    mWindow, sf::Vector2f(mListData.size()*250 + 100, 5), 0, sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 - 120, 135),
                    sf::Color(240, 114, 53, 255), sf::Color::Transparent
                );
                mSceneLayers[CLLArrow]->attachChild(std::move(newCLLArrow3rd));

                std::unique_ptr<ContainerNode> newCLLArrow4th = std::make_unique<ContainerNode>(
                    mWindow, sf::Vector2f(5, 175), 0, sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 - 120, 135),
                    sf::Color(240, 114, 53, 255), sf::Color::Transparent
                );
                mSceneLayers[CLLArrow]->attachChild(std::move(newCLLArrow4th));
            }

            mSceneLayers[NewArrow]->getChildren().clear();
            mSceneLayers[NewNode]->getChildren().clear();

            mAnimationOrder = 10;
            break;
        }
        case 10: {
            if (mListData.size()%2 == 0) {
                for (auto &child : this->mSceneLayers[Nodes]->getChildren()) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 180);
                    }
                }
                for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving) {
                        mIsEndAnimation = 1;
                    }
                }
                for (auto &child : this->mSceneLayers[CLLArrow]->getChildren()) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 180);
                    }
                }
            }
            else {
                mIsEndAnimation = 1;
            }
        }
    }
}
void CLLState::insertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue) {}
void CLLState::deleteAnimation(sf::Time dt, double speed, int deleteIndex) {}
void CLLState::deleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue) {}
void CLLState::updateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue) {}
void CLLState::updateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue) {}
void CLLState::searchAnimation(sf::Time dt, double speed, int searchValue) {}
void CLLState::searchAnimationReversed(sf::Time dt, double speed, int searchValue) {}