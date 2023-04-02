#include <State/SinglyLinkedListState.hpp>

void LinkedListState::createDLL(std::vector<int> list) {
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
    
    for (int i = 0; i < mListData.size() - 1; i++) {
        std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
            mTexturesHolder[Textures::rightArrow], sf::Vector2f(110, 50), 
            sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + i*250 + 130, 275), 0
        );
        mSceneLayers[Arrow]->attachChild(std::move(newArrow));
    }

    for (int i = 0; i < mListData.size() - 1; i++) {
        std::unique_ptr<SpriteNode> newDLLArrow = std::make_unique<SpriteNode>(
            mTexturesHolder[Textures::leftArrow], sf::Vector2f(110, 50), 
            sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + i*250 + 130, 295), 0
        );
        mSceneLayers[DLLArrow]->attachChild(std::move(newDLLArrow));
    }
}

void LinkedListState::DLLInsertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::SinglyLinkedListInsert])) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::DoublyLinkedListInsert], mFontsHolder[Fonts::FiraMonoRegular], 25,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::SinglyLinkedListInsert] = 1;
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
            if (insertIndex == mListData.size()) {
                mColorIndex = insertIndex - 1;
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
                        if (this->mColorIndex >= insertIndex && !mIsActionPaused) {
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
                }
            }
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250, -90);
                    // mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    // mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({11});

                } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                    child->mIsDoneMoving = 0;
                    if (mListData.size() == 0) mAnimationOrder = 7;
                    else if (insertIndex != mListData.size()) mAnimationOrder = 4;
                    else mAnimationOrder = 5;
                }
            }
            break;
        }
        case 4: {
            if (mSceneLayers[NewArrow]->getChildren().size() == 0) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 50), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250 + 25, 490), -90
                );
                mSceneLayers[NewArrow]->attachChild(std::move(newArrow));

                std::unique_ptr<SpriteNode> newDLLArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 50), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250 + 95, 380), 90
                );
                mSceneLayers[NewDLLArrow]->attachChild(std::move(newDLLArrow));
            }
            for (auto &child : this->mSceneLayers[NewArrow]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed, 110, 0, 0);
                    // mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    // mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({12});
                } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                    child->mIsDoneScaling = 0;
                    if(insertIndex != 0) mAnimationOrder = 5;
                    else mAnimationOrder = 6;
                }
            }
            for (auto &child : this->mSceneLayers[NewDLLArrow]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed, 110, 0, 0);
                } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                    child->mIsDoneScaling = 0;
                    mSceneLayers[NewDLLArrow]->getChildren().clear();
                    std::unique_ptr<SpriteNode> newDLLArrow = std::make_unique<SpriteNode>(
                        mTexturesHolder[Textures::leftArrow], sf::Vector2f(110, 50), 
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250 + 45, 490), -90
                    );
                    mSceneLayers[NewDLLArrow]->attachChild(std::move(newDLLArrow));
                    break;
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
                            // mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            // mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({13});
                        }
                        else {
                            child->triggerScaleAnimation(dt, speed*0.8, (110/std::cos(66.8*std::atan(1)*4/180)), 0, 0);
                        }
                        child->triggerMoveAnimation(dt, speed*2, 25, 30);
                    } 
                    else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        child->mIsDoneRotating = 0;
                        mAnimationOrder = 6;
                    }
                    break;
                }
                index++;
            }
            index = 0;
            for (auto &child : this->mSceneLayers[DLLArrow]->getChildren()) {
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
                    else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        child->mIsDoneRotating = 0;
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
                index = 0;
                for (auto &child : this->mSceneLayers[DLLArrow]->getChildren()) {
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
            index = 0;
            for (auto &child : this->mSceneLayers[DLLArrow]->getChildren()) {
                if (index >= insertIndex) {
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
                    mAnimationOrder = 7;
                }
            }
            for (auto &child : this->mSceneLayers[NewArrow]->getChildren()) {
                if (!child->mIsRotating && !child->mIsDoneRotating) {
                    child->triggerRotateAnimation(dt, speed, 90);
                    child->triggerMoveAnimation(dt, speed, 239.26972228011, -63.97040780849);
                } else if (!child->mIsRotating && child->mIsDoneRotating) {
                    child->mIsDoneRotating = 0;
                }
            }
            for (auto &child : this->mSceneLayers[NewDLLArrow]->getChildren()) {
                if (!child->mIsRotating && !child->mIsDoneRotating) {
                    child->triggerRotateAnimation(dt, speed, 90);
                    child->triggerMoveAnimation(dt, speed, 212.72047386183, -66.44773632711);
                } else if (!child->mIsRotating && child->mIsDoneRotating) {
                    child->mIsDoneRotating = 0;
                }
            }
            break;
        }
        case 7: {
            std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                insertValue, mFontsHolder[Fonts::FiraSansRegular], 100,
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250, 250), 
                sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
            );

            mSceneLayers[Nodes]->getChildren().insert(mSceneLayers[Nodes]->getChildren().begin() + insertIndex, std::move(addedNode));
            if (mListData.size() > 0 && insertIndex != mListData.size()) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(110, 50), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + insertIndex*250 + 130, 275), 0
                );
                mSceneLayers[Arrow]->getChildren().insert(mSceneLayers[Arrow]->getChildren().begin() + insertIndex, std::move(newArrow)); 
                std::unique_ptr<SpriteNode> newDLLArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::leftArrow], sf::Vector2f(110, 50), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + insertIndex*250 + 130, 295), 0
                );
                mSceneLayers[DLLArrow]->getChildren().insert(mSceneLayers[DLLArrow]->getChildren().begin() + insertIndex, std::move(newDLLArrow)); 
            }

            mListData.insert(mListData.begin() + insertIndex, insertValue);

            mSceneLayers[NewArrow]->getChildren().clear();
            mSceneLayers[NewDLLArrow]->getChildren().clear();
            mSceneLayers[NewNode]->getChildren().clear();

            mAnimationOrder = 8;
            break;
        }

        case 8: {
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
                for (auto &child : this->mSceneLayers[DLLArrow]->getChildren()) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving) {
                        mIsEndAnimation = 1;
                    }
                }
            }
            else {
                mIsEndAnimation = 1;
            }
        }

        default:
            break;
    }
}

void LinkedListState::DLLInsertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue) {
    mIsEndAnimation = 0;
    switch (mAnimationOrder) {
        case 8: {
            if (mListData.size()%2 == 0) {
                for (auto &child : this->mSceneLayers[Nodes]->getChildren()) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving) {
                        child->mIsDoneMoving = 0;
                    }
                }
                for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving) {
                        child->mIsDoneMoving = 0;
                        mAnimationOrder = 7;
                    }
                }
            }
            else mAnimationOrder = 7;
            break;
        }

        case 7: {
            mSceneLayers[Nodes]->getChildren().erase(mSceneLayers[Nodes]->getChildren().begin() + insertIndex);
            if (mListData.size() > 1 && insertIndex != mListData.size() - 1) 
                mSceneLayers[Arrow]->getChildren().erase(mSceneLayers[Arrow]->getChildren().begin() + insertIndex); 

            mListData.erase(mListData.begin() + insertIndex);

            std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                insertValue, mFontsHolder[Fonts::FiraSansRegular], 100,
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250, 250), 
                sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
            );
            mSceneLayers[NewNode]->attachChild(std::move(addedNode));

            if (insertIndex != mListData.size() && mListData.size() != 0) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(110, 50), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + insertIndex*250 + 130, 285), 0
                );
                mSceneLayers[NewArrow]->attachChild(std::move(newArrow));
            }
            if (mListData.size() == 0) mAnimationOrder = 3;
            else mAnimationOrder = 6;
            break;
        }
        case 6: {
            int index = 0;
            if (insertIndex != 0) {
                for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                    if (index == insertIndex - 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerRotateAnimation(dt, speed, 66.8);
                            child->triggerScaleAnimation(dt, speed*0.99, (110/std::cos(66.8*std::atan(1)*4/180)) - 110, 0, 0);
                            child->triggerMoveAnimation(dt, speed*2, 25, 30);
                            // mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            // mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({13});
                        } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
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
                        child->triggerMoveAnimation(dt, speed, 250, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                if (index >= insertIndex) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250, 90);
                } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                    child->mIsDoneMoving = 0;
                    if (insertIndex != 0) mAnimationOrder = 5;
                    else mAnimationOrder = 4;
                }
            }
            for (auto &child : this->mSceneLayers[NewArrow]->getChildren()) {
                if (!child->mIsRotating && !child->mIsDoneRotating) {
                    child->triggerRotateAnimation(dt, speed, -90);
                    child->triggerMoveAnimation(dt, speed, 225.05318547, -66.16125981683 + 180);
                } else if (!child->mIsRotating && child->mIsDoneRotating && !mIsActionPaused) {
                    child->mIsDoneRotating = 0;
                }
            }
            break;
        }

        case 5: {
            int index = 0;  
            for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                if (index == insertIndex - 1) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        if (insertIndex != mListData.size()) {
                            child->triggerRotateAnimation(dt, speed, -66.8);
                            child->triggerScaleAnimation(dt, speed*0.8, -(110/std::cos(66.8*std::atan(1)*4/180)) + 110, 0, 0);
                            child->triggerMoveAnimation(dt, speed*2, 25, 210);
                            // mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            // mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({12});
                        }
                        else {
                            child->triggerScaleAnimation(dt, speed, -(110/std::cos(66.8*std::atan(1)*4/180)), 0, 0);
                        }
                    } 
                    else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        child->mIsDoneRotating = 0;
                        if (insertIndex != mListData.size()) mAnimationOrder = 4;
                        else mAnimationOrder = 3;
                        if (insertIndex == mListData.size()) 
                            mSceneLayers[Arrow]->getChildren().pop_back();
                    }
                    break;
                }
                index++;
            }
            break;
        }

        case 4: {
            for (auto &child : this->mSceneLayers[NewArrow]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed, -110, 0, 0);
                    // mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    // mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({11});
                } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                    child->mIsDoneScaling = 0;
                    mAnimationOrder = 3;
                    this->mSceneLayers[NewArrow]->getChildren().clear();
                    mIsActionPaused = 1;
                }
            }
            break;
        }

        case 3: {
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250, 90);
                    // mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    // mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({8, 9, 10});
                } else if (!child->mIsMoving && child->mIsDoneMoving) {
                    mSceneLayers[NewNode]->getChildren().clear();
                }
            }
            if (!mIsActionPaused && mSceneLayers[NewNode]->getChildren().size() == 0) {
                if (mListData.size() == 0) mAnimationOrder = 1;
                else mAnimationOrder = 2;
            }
            break;
        }

        case 2: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == this->mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                        // mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        // mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({8, 9, 10});
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex--;
                        if (insertIndex == mListData.size()) {
                            this->mColorIndex = 0;
                            mAnimationOrder = 1;
                        }
                        if (this->mColorIndex < 0  && !mIsActionPaused) {
                            this->mColorIndex = 0;
                            mAnimationOrder = 1;
                        }
                    }
                }
                index++;
            }
            break;
        }
    }
}

void LinkedListState::DLLDeleteAnimation(sf::Time dt, double speed, int deleteIndex) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0) {
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::SinglyLinkedListDelete], mFontsHolder[Fonts::FiraMonoRegular], 25,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        mCodeHolder.mStateActivated[Code::SinglyLinkedListInsert] = 1;
    } else if (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::SinglyLinkedListInsert]) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::SinglyLinkedListDelete], mFontsHolder[Fonts::FiraSansRegular], 30,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::SinglyLinkedListInsert] = 1;
    }
    switch (mAnimationOrder) {
        case 1: {
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsColoring && !child->mIsDoneColoring) {
                    child->triggerColorAnimation(
                        dt, 100, 
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255),
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                    );
                } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                    child->mIsDoneColoring = 0;
                    mAnimationOrder = 2;
                }
            }
            break;
        }
        case 2: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == this->mColorIndex && index < deleteIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex++;
                    }
                } else if (index == this->mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, 100, 
                            sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255),
                            sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex++;
                        if (this->mColorIndex > deleteIndex) {
                            this->mColorIndex--;
                            if (deleteIndex == 0  || deleteIndex == mListData.size() - 1) mAnimationOrder = 6;
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
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                    }
                }
                if (index == deleteIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerRotateAnimation(dt, speed, -66.8);
                        child->triggerScaleAnimation(dt, speed, (110/std::cos(66.8*std::atan(1)*4/180)) - 110, 0, 0);
                        child->triggerMoveAnimation(dt, speed, 270, 94.5);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
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
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
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
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
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

        case 5: {
            int index = 0;
            for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                if (index == deleteIndex - 1) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed, -250, 0, 0);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        mAnimationOrder = 8;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index > deleteIndex && mListData.size()%2 != 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                } else if (index < deleteIndex && mListData.size()%2 == 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                if (index > deleteIndex && mListData.size()%2 != 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                } else if (index < deleteIndex && mListData.size()%2 == 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            break;
        }

        case 6: {
            if (deleteIndex == 0) {
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*1.5, -100, 0, 0);
                    }
                    break;
                }
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*2, -110, speed, -50);
                        child->triggerMoveAnimation(dt, speed*2, 30, 45);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        mAnimationOrder = 7;
                    }
                    break;
                }
            } else if (deleteIndex == mListData.size() - 1) {
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index == mListData.size() - 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed*1.5, -100, 0, 0);
                        }
                    }
                    index++;
                }
                index = 0;
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (index == deleteIndex - 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed*2, -110, speed, -50);
                            child->triggerMoveAnimation(dt, speed*2, 30, 45);
                        } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                            mAnimationOrder = 7;
                        }
                    }
                    index++;
                }

            }
            break;
        }

        case 7: {
            if (deleteIndex == 0 && mListData.size()%2 != 0) {
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index > 0) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250, 180);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneMoving = 0;
                            mAnimationOrder = 8;
                        }
                    }
                    index++;
                }
                index = 0;
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (index > 0) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250, 180);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneMoving = 0;
                        }
                    }
                    index++;
                }
            } else if (deleteIndex == mListData.size() - 1 && mListData.size()%2 == 0) {
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index < deleteIndex) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250, 0);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneMoving = 0;
                            mAnimationOrder = 8;
                        }
                    }
                    index++;
                }
                index = 0;
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (index < deleteIndex - 1) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250, 0);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneMoving = 0;
                        }
                    }
                    index++;
                }
            } else {
                mAnimationOrder = 8;
            }
            break;
        }

        case 8: {
            if (!mIsEndAnimation) {
                if (deleteIndex < mListData.size() - 1) {
                    mSceneLayers[Nodes]->getChildren().erase(mSceneLayers[Nodes]->getChildren().begin() + deleteIndex);
                    mSceneLayers[Arrow]->getChildren().erase(mSceneLayers[Arrow]->getChildren().begin() + deleteIndex);
                    mListData.erase(mListData.begin() + deleteIndex);
                } else {
                    mSceneLayers[Nodes]->getChildren().pop_back();
                    mSceneLayers[Arrow]->getChildren().pop_back();
                    mListData.pop_back();
                }
                mIsEndAnimation = 1;
            }
            break;
        }

        default:
            break;
    }
}

void LinkedListState::DLLDeleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue) {
    mIsEndAnimation = 0;
    switch (mAnimationOrder) {
        case 8: {
            mListData.insert(mListData.begin() + deleteIndex, deleteValue);
            if (deleteIndex != 0 && deleteIndex != mListData.size() - 1) {
                std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
                    deleteValue, mFontsHolder[Fonts::FiraSansRegular], 0,
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (deleteIndex)*250 + 60, 560), 
                    sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255)
                );
                mSceneLayers[Nodes]->getChildren().insert(mSceneLayers[Nodes]->getChildren().begin() + deleteIndex, std::move(newNode));
            } else {
                std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
                    deleteValue, mFontsHolder[Fonts::FiraSansRegular], 0,
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (deleteIndex)*250 + 60    , 310), 
                    sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255)
                );
                mSceneLayers[Nodes]->getChildren().insert(mSceneLayers[Nodes]->getChildren().begin() + deleteIndex, std::move(newNode));
            }
            if (deleteIndex != 0 && deleteIndex != mListData.size() - 1) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 0), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + deleteIndex*250 + 130 - 22, 555), -66.8
                );
                mSceneLayers[Arrow]->getChildren().insert(mSceneLayers[Arrow]->getChildren().begin() + deleteIndex, std::move(newArrow));
            } else {
                if (deleteIndex == 0) {
                    std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                        mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 0),  
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + deleteIndex*250 + 130 + 22, 305), 0
                    );
                    mSceneLayers[Arrow]->getChildren().insert(mSceneLayers[Arrow]->getChildren().begin() + deleteIndex, std::move(newArrow));
                } else {
                    std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                        mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 0),  
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (deleteIndex - 1)*250 + 130 + 22, 305), 0
                    );
                    mSceneLayers[Arrow]->getChildren().insert(mSceneLayers[Arrow]->getChildren().begin() + deleteIndex - 1, std::move(newArrow));
                }
            }
            if (deleteIndex == 0 || deleteIndex == mListData.size() - 1) mAnimationOrder = 7;
            else mAnimationOrder = 5;
            break;
        }

        case 7: {
            if (deleteIndex == 0 && mListData.size()%2 != 0) {
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index > 0) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250, 0);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneMoving = 0;
                            mAnimationOrder = 6;
                        }
                    }
                    index++;
                }
                index = 0;
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (index > 0) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250, 0);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneMoving = 0;
                        }
                    }
                    index++;
                }
            } else if (deleteIndex == mListData.size() - 1 && mListData.size()%2 == 0) {
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index < deleteIndex) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250, 180);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneMoving = 0;
                            mAnimationOrder = 6;
                        }
                    }
                    index++;
                }
                index = 0;
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (index < deleteIndex - 1) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250, 180);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneMoving = 0;
                        }
                    }
                    index++;
                }
            } else {
                mAnimationOrder = 6;
            }
            break;
        }

        case 6: {
            if (deleteIndex == 0) {
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*1.5, 100, 0, 0);
                    }
                    break;
                }
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*2, 110, speed, 50);
                        child->triggerMoveAnimation(dt, speed*2, 30, 45 - 180);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        mAnimationOrder = 2;
                    }
                    break;
                }
            } else if (deleteIndex == mListData.size() - 1) {
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index == mListData.size() - 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed*1.5, 100, 0, 0);
                        }
                    }
                    index++;
                }
                index = 0;
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (index == deleteIndex - 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed*2, 110, speed, 50);
                            child->triggerMoveAnimation(dt, speed*2, 30, 45 - 180);
                        } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                            mAnimationOrder = 2;
                        }
                    }
                    index++;
                }

            }
            break;
        }

        case 5: {
            int index = 0;
            for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                if (index == deleteIndex - 1) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed, 250, 0, 0);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        mAnimationOrder = 4;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index > deleteIndex && mListData.size()%2 != 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                } else if (index < deleteIndex && mListData.size()%2 == 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                if (index > deleteIndex && mListData.size()%2 != 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                } else if (index < deleteIndex && mListData.size()%2 == 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
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
                        child->triggerScaleAnimation(dt, speed*2, (110/std::cos(66.8*std::atan(1)*4/180)), speed, 50);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        mAnimationOrder = 3;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == deleteIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*1.5, 100, 0, 0);
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
                        child->triggerScaleAnimation(dt, speed, -250, 0, 0);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                    }
                }
                if (index == deleteIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerRotateAnimation(dt, speed, 66.8);
                        child->triggerScaleAnimation(dt, speed, -(110/std::cos(66.8*std::atan(1)*4/180)) + 110, 0, 0);
                        child->triggerMoveAnimation(dt, speed, 270, 94.5 + 180);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        child->mIsDoneMoving = 0;
                        child->mIsDoneRotating = 0;
                        mAnimationOrder = 2;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == deleteIndex) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, -90);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            break;
        }

        case 2: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == this->mColorIndex && index < deleteIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex--;
                        if (this->mColorIndex < 0) {
                            this->mColorIndex = 0;
                            mAnimationOrder = 1;
                        }
                    }
                } else if (index == this->mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, 100, 
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex--;
                    }  
                }
                index++;
            }
            break;
        }
    }
}   

void LinkedListState::DLLUpdateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue) {
    switch (mAnimationOrder) {
        case 1: {
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsColoring && !child->mIsDoneColoring) {
                    child->triggerColorAnimation(
                        dt, 100, 
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255),
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                    );
                } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                    child->mIsDoneColoring = 0;
                    mAnimationOrder = 2;
                }
            }
            break;
        }
        case 2: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == this->mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex++;
                        if (this->mColorIndex > updateIndex && !mIsActionPaused) {
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
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == updateIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(78, 62, 222, 255), sf::Color(78, 62, 222, 255),
                            sf::Color(78, 62, 222, 255), sf::Color::White, sf::Color(78, 62, 222, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring) {
                        child->mIsDoneColoring = 0;
                        child->triggerChangeContent(std::to_string(updateValue));
                        mAnimationOrder = 4;
                    }
                }
                index++;
            }
            break;
        }
        case 4: {
            if (!mIsEndAnimation) {
                mListData[updateIndex] = updateValue;
                mIsEndAnimation = 1;
            }
            break;
        }
    }
}

void LinkedListState::DLLUpdateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue) {
    mIsEndAnimation = 0;
    switch (mAnimationOrder) {
        case 4: {
            mListData[updateIndex] = prevValue;
            mAnimationOrder = 3;
            break;
        }
        case 3: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == updateIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(78, 62, 222, 255), sf::Color(78, 62, 222, 255),
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        child->triggerChangeContent(std::to_string(prevValue));
                        mAnimationOrder = 2;
                    }
                }
                index++;
            }
            break;
        }
        case 2: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == this->mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex--;
                        if (this->mColorIndex < 0 && !mIsActionPaused) {
                            this->mColorIndex = 0;
                            mAnimationOrder = 1;
                            break;
                        }
                    }
                }
                index++;
            }
            break;
        }
    }
}

void LinkedListState::DLLSearchAnimation(sf::Time dt, double speed, int searchValue) {
    switch(mAnimationOrder) {
        case 1: {
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsColoring && !child->mIsDoneColoring) {
                    child->triggerColorAnimation(
                        dt, 100, 
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255),
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                    );
                } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                    child->mIsDoneColoring = 0;
                    mAnimationOrder = 2;
                }
            }
            break;
        }
        case 2: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == this->mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex++;
                        if (std::stoi(child->getStringData()) == searchValue) {
                            this->mColorIndex--;    
                            mAnimationOrder = 3;
                        } else if (this->mColorIndex == mListData.size()) {
                            mAnimationOrder = 4;
                        }
                    }
                }
                index++;
            }
            break;
        }
        case 3: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == this->mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(221, 99, 230, 255), sf::Color(221, 99, 230, 255),
                            sf::Color(221, 99, 230, 255), sf::Color::White, sf::Color(221, 99, 230, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        mAnimationOrder = 4;
                    }
                }
                index++;
            }
            break;
        }
        case 4: {
            if (!mIsEndAnimation) {
                mIsEndAnimation = 1;
            }
        }
    }
}

void LinkedListState::DLLSearchAnimationReversed(sf::Time dt, double speed, int searchValue) {
    mIsEndAnimation = 0;
    switch(mAnimationOrder) {
        case 4: {
            if (this->mColorIndex == mListData.size()) {
                this->mColorIndex--;
                mAnimationOrder = 2;
            } 
            else mAnimationOrder = 3;
            break;
        }
        case 3: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == this->mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(221, 99, 230, 255), sf::Color(221, 99, 230, 255),
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        mAnimationOrder = 2;
                    }
                }
                index++;
            }
            break;
        }
        case 2: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == this->mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex--;
                        if (this->mColorIndex < 0) {
                            mAnimationOrder = 1;
                        }
                    }
                }
                index++;
            }
            break;
        }
    }
}