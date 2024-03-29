#include <State/DLLState.hpp>

void DLLState::createDataStructure(SinglyLinkedList<int> &list) {
    for (int i = 0; i < LayerCount; i++) {
        mSceneLayers[i]->getChildren().clear();
    }
    if (list.size() == 0) return;
    mListData = list;
    for (int i = 0; i < mListData.size(); i++) {
        if (mListData.size() == 1) {
            std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
                mListData[i], mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, "head/tail", 50*Constant::scaleX, 
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + i*250*Constant::scaleX, 250*Constant::scaleX), 
                sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
            );
            mSceneLayers[Nodes]->attachChild(std::move(newNode));
        }
        else if (i == 0) {
            std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
                mListData[i], mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, "head", 50*Constant::scaleX, 
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + i*250*Constant::scaleX, 250*Constant::scaleX), 
                sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
            );
            mSceneLayers[Nodes]->attachChild(std::move(newNode));
        } else if (i == mListData.size() - 1) {
            std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
                mListData[i], mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, "tail", 50*Constant::scaleX, 
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + i*250*Constant::scaleX, 250*Constant::scaleX), 
                sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
            );
            mSceneLayers[Nodes]->attachChild(std::move(newNode));
        } else {
            std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
                mListData[i], mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, 
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + i*250*Constant::scaleX, 250*Constant::scaleX), 
                sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
            );
            mSceneLayers[Nodes]->attachChild(std::move(newNode));
        }
    }
    
    for (int i = 0; i < mListData.size() - 1; i++) {
        std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
            mTexturesHolder[Textures::rightArrow], sf::Vector2f(110*Constant::scaleX, 50*Constant::scaleX), 
            sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + i*250*Constant::scaleX + 130*Constant::scaleX, 275*Constant::scaleX), 0
        );
        mSceneLayers[Arrow]->attachChild(std::move(newArrow));
    }

    for (int i = 0; i < mListData.size() - 1; i++) {
        std::unique_ptr<SpriteNode> newDLLArrow = std::make_unique<SpriteNode>(
            mTexturesHolder[Textures::leftArrow], sf::Vector2f(110*Constant::scaleX, 50*Constant::scaleX), 
            sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + i*250*Constant::scaleX + 130*Constant::scaleX, 295*Constant::scaleX), 0
        );
        mSceneLayers[DLLArrow]->attachChild(std::move(newDLLArrow));
    }
}


void DLLState::insertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue) {
    if (insertIndex != mListData.size() && !(mAnimationOrder == 8 && insertIndex == mListData.size() - 1)) {
        if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
            (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::DoublyLinkedListInsert])
        ) {
            mSceneLayers[CodeBox]->getChildren().clear();
            std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
                mWindow, mCodeHolder[Code::DoublyLinkedListInsert], mFontsHolder[Fonts::FiraMonoRegular], 25*Constant::scaleX,
                sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
            );
            mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
            for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
                mCodeHolder.mStateActivated[i] = 0;
            }
            mCodeHolder.mStateActivated[Code::DoublyLinkedListInsert] = 1;
        }
    } else {
        if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
            (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::DoublyLinkedListInsertTail])
        ) {
            mSceneLayers[CodeBox]->getChildren().clear();
            std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
                mWindow, mCodeHolder[Code::DoublyLinkedListInsertTail], mFontsHolder[Fonts::FiraMonoRegular], 25*Constant::scaleX,
                sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
            );
            mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
            for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
                mCodeHolder.mStateActivated[i] = 0;
            }
            mCodeHolder.mStateActivated[Code::DoublyLinkedListInsertTail] = 1;
        }
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
                        dt, speed, 
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255),
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                    );
                    if (insertIndex != 0 && insertIndex != mListData.size()) {
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({7});
                    } else if (insertIndex == mListData.size()) {
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({0});
                    }
                } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                    child->mIsDoneColoring = 0;
                    mAnimationOrder = 2;
                }
            }
            break;
        }
        case 2: {
            if (insertIndex == 0) {
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
                        if (insertIndex != mListData.size()) {
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({8, 9, 10});
                            if (index != 0) child->setLabel("cur");
                            else child->setLabel("head/cur");
                        }
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex++;
                        if (index != 0) child->setLabel("");
                        else child->setLabel("head");
                        if (this->mColorIndex >= insertIndex && !mIsActionPaused) {
                            this->mColorIndex--;
                            mAnimationOrder = 3;
                            if (insertIndex != 1) {
                                if (insertIndex != mListData.size()) child->setLabel("cur");
                                else child->setLabel("tail");
                            }
                            else {
                                if (mListData.size() != 1) child->setLabel("head/cur");
                                else child->setLabel("head/tail");
                            }
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
                if (mListData.size() > 0 && insertIndex != mListData.size() && mListData.size() != 0) {
                    std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                        insertValue, mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, "newNode", 50*Constant::scaleX,
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (insertIndex)*250*Constant::scaleX, 750*Constant::scaleX), 
                        sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
                    );
                    mSceneLayers[NewNode]->attachChild(std::move(addedNode));
                } else {
                    std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                        insertValue, mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, "newNode", 50*Constant::scaleX,
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (insertIndex)*250*Constant::scaleX, 500*Constant::scaleX), 
                        sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
                    );
                    mSceneLayers[NewNode]->attachChild(std::move(addedNode));
                }
            }
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, -90);
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    if (insertIndex == 0) {
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2});
                    } else if (insertIndex == mListData.size()) {
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
                    } else {
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({11});
                    }
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
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 50*Constant::scaleX), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (insertIndex)*250*Constant::scaleX + 25*Constant::scaleX, 490*Constant::scaleX), -90
                );
                mSceneLayers[NewArrow]->attachChild(std::move(newArrow));

                std::unique_ptr<SpriteNode> newDLLArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 50*Constant::scaleX), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (insertIndex)*250*Constant::scaleX + 95*Constant::scaleX, 380*Constant::scaleX), 90
                );
                mSceneLayers[NewDLLArrow]->attachChild(std::move(newDLLArrow));
            }
            for (auto &child : this->mSceneLayers[NewArrow]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed, 110*Constant::scaleX, 0, 0);
                    if (insertIndex != 0) {
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({12, 13});
                    } else {
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({3});
                    }
                } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                    child->mIsDoneScaling = 0;
                    if(insertIndex != 0) mAnimationOrder = 5;
                    else mAnimationOrder = 6;
                }
            }
            for (auto &child : this->mSceneLayers[NewDLLArrow]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed, 110*Constant::scaleX, 0, 0);
                } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                    child->mIsDoneScaling = 0;
                    mSceneLayers[NewDLLArrow]->getChildren().clear();
                    std::unique_ptr<SpriteNode> newDLLArrow = std::make_unique<SpriteNode>(
                        mTexturesHolder[Textures::leftArrow], sf::Vector2f(110*Constant::scaleX, 50*Constant::scaleX), 
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (insertIndex)*250*Constant::scaleX + 45*Constant::scaleX, 490*Constant::scaleX), -90
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
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 50*Constant::scaleX), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (insertIndex - 1)*250*Constant::scaleX + 130*Constant::scaleX, 275*Constant::scaleX), 0
                );
                mSceneLayers[Arrow]->attachChild(std::move(newArrow));
                std::unique_ptr<SpriteNode> newDLLArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 50*Constant::scaleX), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (insertIndex - 1)*250*Constant::scaleX + 240*Constant::scaleX, 345*Constant::scaleX), 180
                );
                mSceneLayers[DLLArrow]->attachChild(std::move(newDLLArrow));
            }
            for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                if (index == insertIndex - 1) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        if (insertIndex != mListData.size()) {
                            child->triggerRotateAnimation(dt, speed, 66.8);
                            child->triggerScaleAnimation(dt, speed*0.8, ((110/std::cos(66.8*std::atan(1)*4/180)) - 110)*Constant::scaleX, 0, 0);
                            child->triggerMoveAnimation(dt, speed*2, 25*Constant::scaleX, 30);
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({14});
                        }
                        else {
                            child->triggerScaleAnimation(dt, speed*0.8, 110*Constant::scaleX, 0, 0);
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({6, 7});
                        }
                    } 
                    else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        child->mIsDoneRotating = 0;
                        if (insertIndex != mListData.size()) mAnimationOrder = 6;
                        else {
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({8});
                            mAnimationOrder = 7;
                        }
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
                            child->triggerScaleAnimation(dt, speed*0.8, ((110/std::cos(66.8*std::atan(1)*4/180)) - 110)*Constant::scaleX, 0, 0);
                            child->triggerMoveAnimation(dt, speed*2, 25*Constant::scaleX, 30);
                        }
                        else {
                            child->triggerScaleAnimation(dt, speed*0.8, 110*Constant::scaleX, 0, 0);
                        }
                    } 
                    else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneRotating = 0;
                        child->mIsDoneScaling = 0;
                        if (insertIndex == mListData.size()) {
                            mSceneLayers[DLLArrow]->getChildren().pop_back();
                            std::unique_ptr<SpriteNode> newDLLArrow = std::make_unique<SpriteNode>(
                                mTexturesHolder[Textures::leftArrow], sf::Vector2f(110*Constant::scaleX, 50*Constant::scaleX), 
                                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (insertIndex - 1)*250*Constant::scaleX + 130*Constant::scaleX, 295*Constant::scaleX), 0
                            );
                            mSceneLayers[DLLArrow]->attachChild(std::move(newDLLArrow));
                        }
                    }
                    break;
                }
                index++;
            }
            break;
        }

        case 6: {
            int index = 0;
            if (insertIndex != 0 && insertIndex != mListData.size()) {
                for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                    if (index == insertIndex - 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerRotateAnimation(dt, speed, -66.8);
                            child->triggerScaleAnimation(dt, speed*0.99, (-(110/std::cos(66.8*std::atan(1)*4/180)) + 110)*Constant::scaleX, 0, 0);
                            child->triggerMoveAnimation(dt, speed*2, 25*Constant::scaleX, -150);
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({15});
                        } else if (!child->mIsScaling && child->mIsDoneScaling) {
                            child->mIsDoneMoving = 0;
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
                            child->triggerScaleAnimation(dt, speed*0.99, (-(110/std::cos(66.8*std::atan(1)*4/180)) + 110)*Constant::scaleX, 0, 0);
                            child->triggerMoveAnimation(dt, speed*2, 25*Constant::scaleX, -150);
                        } else if (!child->mIsScaling && child->mIsDoneScaling) {
                            child->mIsDoneMoving = 0;
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
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
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
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
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
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, -90);
                    if (insertIndex == 0) {
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({4});
                    }
                } else if (!child->mIsMoving && child->mIsDoneMoving) {
                    child->mIsDoneMoving = 0;
                    mAnimationOrder = 7;
                }
            }
            for (auto &child : this->mSceneLayers[NewArrow]->getChildren()) {
                if (!child->mIsRotating && !child->mIsDoneRotating) {
                    child->triggerRotateAnimation(dt, speed, 90);
                    child->triggerMoveAnimation(dt, speed, 239.26972228011*Constant::scaleX, -63.97040780849);
                } else if (!child->mIsRotating && child->mIsDoneRotating) {
                    child->mIsDoneRotating = 0;
                }
            }
            for (auto &child : this->mSceneLayers[NewDLLArrow]->getChildren()) {
                if (!child->mIsRotating && !child->mIsDoneRotating) {
                    child->triggerRotateAnimation(dt, speed, 90);
                    child->triggerMoveAnimation(dt, speed, 212.72047386183*Constant::scaleX, -66.44773632711);
                } else if (!child->mIsRotating && child->mIsDoneRotating) {
                    child->mIsDoneRotating = 0;
                }
            }
            break;
        }
        case 7: {
            if (insertIndex == 0 && mListData.size() != 0) {
                mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({5});
            } else if (mListData.size() == 0) {
                mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2, 3, 4});
            }
            
            std::string str;
            if (mListData.size() != 0) {
                if (insertIndex == 0) {
                    mSceneLayers[Nodes]->getChildren().front()->setLabel("");
                    str = "head";
                }
                else if (insertIndex == mListData.size()) str = "tail";
                else str = "newNode";
            } else str = "head/tail";

            if (insertIndex == mListData.size() && mListData.size() != 0) mSceneLayers[Nodes]->getChildren().back()->setLabel("");

            std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                insertValue, mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, str, 50*Constant::scaleX,
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (insertIndex)*250*Constant::scaleX, 250*Constant::scaleX), 
                sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
            );

            mSceneLayers[Nodes]->getChildren().insert(mSceneLayers[Nodes]->getChildren().begin() + insertIndex, std::move(addedNode));
            if (mListData.size() > 0 && insertIndex != mListData.size()) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(110*Constant::scaleX, 50*Constant::scaleX), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + insertIndex*250*Constant::scaleX + 130*Constant::scaleX, 275*Constant::scaleX), 0
                );
                mSceneLayers[Arrow]->getChildren().insert(mSceneLayers[Arrow]->getChildren().begin() + insertIndex, std::move(newArrow)); 
                std::unique_ptr<SpriteNode> newDLLArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::leftArrow], sf::Vector2f(110*Constant::scaleX, 50*Constant::scaleX), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + insertIndex*250*Constant::scaleX + 130*Constant::scaleX, 295*Constant::scaleX), 0
                );
                mSceneLayers[DLLArrow]->getChildren().insert(mSceneLayers[DLLArrow]->getChildren().begin() + insertIndex, std::move(newDLLArrow)); 
            }

            mListData.insert(mListData.begin() + insertIndex, insertValue);

            mSceneLayers[NewArrow]->getChildren().clear();
            mSceneLayers[NewDLLArrow]->getChildren().clear();
            mSceneLayers[NewNode]->getChildren().clear();

            if (mListData.size() == 2) {
                mSceneLayers[Nodes]->getChildren().front()->setLabel("head");
                mSceneLayers[Nodes]->getChildren().back()->setLabel("tail");
            }

            mAnimationOrder = 8;
            break;
        }

        case 8: {
            if (mListData.size()%2 == 0) {
                for (auto &child : this->mSceneLayers[Nodes]->getChildren()) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
                    }
                }
                for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving) {
                        mIsEndAnimation = 1;
                    }
                }
                for (auto &child : this->mSceneLayers[DLLArrow]->getChildren()) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
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

void DLLState::insertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue) {
    mIsEndAnimation = 0;
    switch (mAnimationOrder) {
        case 8: {
            if (mListData.size()%2 == 0) {
                for (auto &child : this->mSceneLayers[Nodes]->getChildren()) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving) {
                        child->mIsDoneMoving = 0;
                    }
                }
                for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving) {
                        child->mIsDoneMoving = 0;
                        mAnimationOrder = 7;
                    }
                }
                for (auto &child : this->mSceneLayers[DLLArrow]->getChildren()) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving) {
                        child->mIsDoneMoving = 0;
                    }
                }
            }
            else mAnimationOrder = 7;
            break;
        }

        case 7: {
            mSceneLayers[Nodes]->getChildren().erase(mSceneLayers[Nodes]->getChildren().begin() + insertIndex);
            if (mListData.size() > 1 && insertIndex != mListData.size() - 1) {
                mSceneLayers[Arrow]->getChildren().erase(mSceneLayers[Arrow]->getChildren().begin() + insertIndex); 
                mSceneLayers[DLLArrow]->getChildren().erase(mSceneLayers[DLLArrow]->getChildren().begin() + insertIndex); 
            }
            mListData.erase(mListData.begin() + insertIndex);

            if (mListData.size() != 0) {
                if (mListData.size() == 1) mSceneLayers[Nodes]->getChildren().front()->setLabel("head/tail");
                else if (insertIndex == 0) mSceneLayers[Nodes]->getChildren().front()->setLabel("head");
                else if (insertIndex == mListData.size()) mSceneLayers[Nodes]->getChildren().back()->setLabel("tail");
            }
            std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                insertValue, mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, "newNode", 50*Constant::scaleX,
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (insertIndex)*250*Constant::scaleX, 250*Constant::scaleX), 
                sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
            );
            mSceneLayers[NewNode]->attachChild(std::move(addedNode));

            if (insertIndex != mListData.size() && mListData.size() != 0) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(110*Constant::scaleX, 50*Constant::scaleX), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + insertIndex*250*Constant::scaleX + 130*Constant::scaleX, 275*Constant::scaleX), 0
                );
                mSceneLayers[NewArrow]->attachChild(std::move(newArrow));
                std::unique_ptr<SpriteNode> newDLLArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::leftArrow], sf::Vector2f(110*Constant::scaleX, 50*Constant::scaleX), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + insertIndex*250*Constant::scaleX + 130*Constant::scaleX, 295*Constant::scaleX), 0
                );
                mSceneLayers[NewDLLArrow]->attachChild(std::move(newDLLArrow));
            }
            if (mListData.size() == 0) mAnimationOrder = 3;
            else if (insertIndex != mListData.size()) mAnimationOrder = 6;
            else mAnimationOrder = 5;
            break;
        }
        case 6: {
            int index = 0;
            if (insertIndex != 0 && insertIndex != mListData.size()) {
                for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                    if (index == insertIndex - 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerRotateAnimation(dt, speed, 66.8);
                            child->triggerScaleAnimation(dt, speed*0.99, ((110/std::cos(66.8*std::atan(1)*4/180)) - 110)*Constant::scaleX, 0, 0);
                            child->triggerMoveAnimation(dt, speed*2, 25*Constant::scaleX, 30);
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({14});
                        } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
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
                            child->triggerRotateAnimation(dt, speed, 66.8);
                            child->triggerScaleAnimation(dt, speed*0.99, ((110/std::cos(66.8*std::atan(1)*4/180)) - 110)*Constant::scaleX, 0, 0);
                            child->triggerMoveAnimation(dt, speed*2, 25*Constant::scaleX, 30);
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
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
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
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : this->mSceneLayers[DLLArrow]->getChildren()) {
                if (index >= insertIndex) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 90);
                    if (insertIndex == 0) {
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({4});
                    }
                } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                    child->mIsDoneMoving = 0;
                    if (insertIndex != 0) mAnimationOrder = 5;
                    else mAnimationOrder = 4;
                }
            }
            for (auto &child : this->mSceneLayers[NewArrow]->getChildren()) {
                if (!child->mIsRotating && !child->mIsDoneRotating) {
                    child->triggerRotateAnimation(dt, speed, -90);
                    child->triggerMoveAnimation(dt, speed, 239.26972228011*Constant::scaleX, -63.97040780849 + 180);
                } else if (!child->mIsRotating && child->mIsDoneRotating && !mIsActionPaused) {
                    child->mIsDoneRotating = 0;
                }
            }
            for (auto &child : this->mSceneLayers[NewDLLArrow]->getChildren()) {
                if (!child->mIsRotating && !child->mIsDoneRotating) {
                    child->triggerRotateAnimation(dt, speed, -90);
                    child->triggerMoveAnimation(dt, speed, 212.72047386183*Constant::scaleX, -66.44773632711 + 180);
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
                            child->triggerScaleAnimation(dt, speed*0.8, (-(110/std::cos(66.8*std::atan(1)*4/180)) + 110)*Constant::scaleX, 0, 0);
                            child->triggerMoveAnimation(dt, speed*2, 25*Constant::scaleX, 210);
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({12, 13});
                        }
                        else {
                            child->triggerScaleAnimation(dt, speed*0.8, -110*Constant::scaleX, 0, 0);
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({6, 7});
                            mSceneLayers[DLLArrow]->getChildren().pop_back();
                            std::unique_ptr<SpriteNode> newDLLArrow = std::make_unique<SpriteNode>(
                                mTexturesHolder[Textures::rightArrow], sf::Vector2f(110, 50), 
                                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (insertIndex - 1)*250*Constant::scaleX + 240*Constant::scaleX, 345*Constant::scaleX), 180
                            );
                            mSceneLayers[DLLArrow]->attachChild(std::move(newDLLArrow));
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
            index = 0;
            for (auto &child : this->mSceneLayers[DLLArrow]->getChildren()) {
                if (index == insertIndex - 1) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        if (insertIndex != mListData.size()) {
                            child->triggerRotateAnimation(dt, speed, -66.8);
                            child->triggerScaleAnimation(dt, speed*0.8, (-(110/std::cos(66.8*std::atan(1)*4/180)) + 110)*Constant::scaleX, 0, 0);
                            child->triggerMoveAnimation(dt, speed*2, 25*Constant::scaleX, 210);
                        } 
                        else child->triggerScaleAnimation(dt, speed, -110*Constant::scaleX, 0, 0);
                    } 
                    else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        child->mIsDoneRotating = 0;
                        if (insertIndex == mListData.size()) 
                            mSceneLayers[DLLArrow]->getChildren().pop_back();
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
                    child->triggerScaleAnimation(dt, speed, -110*Constant::scaleX, 0, 0);
                    if (insertIndex != 0) {
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({11});
                    } else {
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({3});
                    }
                    mSceneLayers[NewDLLArrow]->getChildren().clear();
                    std::unique_ptr<SpriteNode> newDLLArrow = std::make_unique<SpriteNode>(
                        mTexturesHolder[Textures::rightArrow], sf::Vector2f(110*Constant::scaleX, 50*Constant::scaleX), 
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (insertIndex)*250*Constant::scaleX + 95*Constant::scaleX, 380*Constant::scaleX), 90
                    );
                    mSceneLayers[NewDLLArrow]->attachChild(std::move(newDLLArrow));
                } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                    child->mIsDoneScaling = 0;
                    mAnimationOrder = 3;
                    this->mSceneLayers[NewArrow]->getChildren().clear();
                }
            }
            for (auto &child : this->mSceneLayers[NewDLLArrow]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed, -110*Constant::scaleX, 0, 0);
                } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                    child->mIsDoneScaling = 0;
                    this->mSceneLayers[NewDLLArrow]->getChildren().clear();
                }
            }
            break;
        }

        case 3: {
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 90);
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    if (insertIndex == 0) {
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2});
                    } else if (insertIndex == mListData.size()) {
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
                    } else {
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({8, 9, 10});
                    }
                } else if (!child->mIsMoving && child->mIsDoneMoving) {
                    if (mSceneLayers[NewNode]->getChildren().size() != 0) 
                        mSceneLayers[NewNode]->getChildren().clear();
                    if (!mIsActionPaused) {
                        if (mListData.size() == 0) mAnimationOrder = 1;
                        else mAnimationOrder = 2;
                    }
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
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                        if (insertIndex != mListData.size()) {
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({8, 9, 10});
                            if (index != 0) child->setLabel("cur");
                            else child->setLabel("head/cur");
                        }
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        if (insertIndex != mListData.size()) {
                            if (index != 0) child->setLabel("");
                            else child->setLabel("head");
                        }
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

void DLLState::deleteAnimation(sf::Time dt, double speed, int deleteIndex) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
    (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::DoublyLinkedListDelete])
    ) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::DoublyLinkedListDelete], mFontsHolder[Fonts::FiraMonoRegular], 25*Constant::scaleX,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::DoublyLinkedListDelete] = 1;
    }
    switch (mAnimationOrder) {
        case 1: {
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsColoring && !child->mIsDoneColoring) {
                    child->triggerColorAnimation(
                        dt, speed, 
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255),
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                    );
                    if (deleteIndex != 0) {
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({7});
                    }
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
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({8, 9, 10});
                        if (index != 0) child->setLabel("cur");
                        else child->setLabel("head/cur");
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        if (index != 0) child->setLabel("");
                        else child->setLabel("head");
                        child->mIsDoneColoring = 0;
                        this->mColorIndex++;
                        if (mColorIndex == deleteIndex) {
                            if (deleteIndex != 1) child->setLabel("cur");
                            else child->setLabel("head/cur");
                        }
                    }
                } else if (index == this->mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255),
                            sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255)
                        );
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        if (deleteIndex == 0) {
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2});
                        } else if (deleteIndex == mListData.size() - 1) {
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({11, 12, 13});
                        } else {
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({11, 12});
                        }
                        child->setLabel("temp");
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
                        child->triggerScaleAnimation(dt, speed, 250*Constant::scaleX, 0, 0);
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({12, 13});
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                    }
                }
                if (index == deleteIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerRotateAnimation(dt, speed, -66.8);
                        child->triggerScaleAnimation(dt, speed, ((110/std::cos(66.8*std::atan(1)*4/180)) - 110)*Constant::scaleX, 0, 0);
                        child->triggerMoveAnimation(dt, speed, 270*Constant::scaleX, 94.5);
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
            for (auto &child : mSceneLayers[DLLArrow]->getChildren()) {
                if (index == deleteIndex - 1) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed, 250*Constant::scaleX, 0, 0);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                    }
                }
                if (index == deleteIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerRotateAnimation(dt, speed, -66.8);
                        child->triggerScaleAnimation(dt, speed, ((110/std::cos(66.8*std::atan(1)*4/180)) - 110)*Constant::scaleX, 0, 0);
                        child->triggerMoveAnimation(dt, speed, 270*Constant::scaleX, 94.5);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        child->mIsDoneMoving = 0;
                        child->mIsDoneRotating = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == deleteIndex) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 90);
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
                        child->triggerScaleAnimation(dt, speed*2, (-(110/std::cos(66.8*std::atan(1)*4/180)))*Constant::scaleX, speed, -50);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        mAnimationOrder = 5;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[DLLArrow]->getChildren()) {
                if (index == deleteIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*2, -(110/std::cos(66.8*std::atan(1)*4/180))*Constant::scaleX, speed, -50);
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == deleteIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*1.5, -100*Constant::scaleX, 0, 0);
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({14});
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
                        child->triggerScaleAnimation(dt, speed, -250*Constant::scaleX, 0, 0);
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({15});
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        mAnimationOrder = 8;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[DLLArrow]->getChildren()) {
                if (index == deleteIndex - 1) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed, -250*Constant::scaleX, 0, 0);
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
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                } else if (index < deleteIndex && mListData.size()%2 == 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
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
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                } else if (index < deleteIndex && mListData.size()%2 == 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[DLLArrow]->getChildren()) {
                if (index > deleteIndex && mListData.size()%2 != 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                } else if (index < deleteIndex && mListData.size()%2 == 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
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
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index == 0) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed*1.5, -100*Constant::scaleX, 0, 0);
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({3, 4});
                        } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                            mAnimationOrder = 7;
                        }
                    } else if (index == 1) {
                        if (mListData.size() != 2) child->setLabel("head");
                        else child->setLabel("head/tail");
                    }
                    index++;
                }
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*2, -110*Constant::scaleX, speed, -50*Constant::scaleX);
                        child->triggerMoveAnimation(dt, speed*2, 30*Constant::scaleX, 45);
                    }
                    break;
                }
                for (auto &child : mSceneLayers[DLLArrow]->getChildren()) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*2, -110*Constant::scaleX, speed, -50*Constant::scaleX);
                        child->triggerMoveAnimation(dt, speed*2, 30*Constant::scaleX, 45);
                    }
                    break;
                }
            } else if (deleteIndex == mListData.size() - 1) {
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index == mListData.size() - 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed*1.5, -100*Constant::scaleX, 0, 0);
                        }
                    }
                    else if (index == mListData.size() - 2) {
                        if (mListData.size() == 2) child->setLabel("head/tail");
                        else child->setLabel("tail");
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({14, 15});
                    }
                    index++;
                }
                index = 0;
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (index == deleteIndex - 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed*2, -110*Constant::scaleX, speed, -50*Constant::scaleX);
                            child->triggerMoveAnimation(dt, speed*2, 30*Constant::scaleX, 45);
                        } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                            mAnimationOrder = 7;
                        }
                    }
                    index++;
                }
                index = 0;
                for (auto &child : mSceneLayers[DLLArrow]->getChildren()) {
                    if (index == deleteIndex - 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed*2, -110*Constant::scaleX, speed, -50*Constant::scaleX);
                            child->triggerMoveAnimation(dt, speed*2, 30*Constant::scaleX, 45);
                        }
                    }
                    index++;
                }
            }
            break;
        }

        case 7: {
            if (deleteIndex == 0 && mListData.size()%2 != 0 && mListData.size() != 1) {
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index > 0) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
                        } else if (!child->mIsMoving && child->mIsDoneMoving) {
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
                            child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
                        } else if (!child->mIsMoving && child->mIsDoneMoving) {
                            child->mIsDoneMoving = 0;
                        }
                    }
                    index++;
                }
                index = 0;
                for (auto &child : mSceneLayers[DLLArrow]->getChildren()) {
                    if (index > 0) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
                        } else if (!child->mIsMoving && child->mIsDoneMoving) {
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
                            child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
                        } else if (!child->mIsMoving && child->mIsDoneMoving) {
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
                            child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
                        } else if (!child->mIsMoving && child->mIsDoneMoving) {
                            child->mIsDoneMoving = 0;
                        }
                    }
                    index++;
                }
                index = 0;
                for (auto &child : mSceneLayers[DLLArrow]->getChildren()) {
                    if (index < deleteIndex - 1) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
                        } else if (!child->mIsMoving && child->mIsDoneMoving) {
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
                mSceneLayers[Nodes]->getChildren().erase(mSceneLayers[Nodes]->getChildren().begin() + deleteIndex);
                if (mListData.size() != 1) {
                    mSceneLayers[Arrow]->getChildren().erase(mSceneLayers[Arrow]->getChildren().begin() + deleteIndex);
                    mSceneLayers[DLLArrow]->getChildren().erase(mSceneLayers[DLLArrow]->getChildren().begin() + deleteIndex);
                }
                mListData.erase(mListData.begin() + deleteIndex);
                mIsEndAnimation = 1;
            }
            break;
        }

        default:
            break;
    }
}

void DLLState::deleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue) {
    mIsEndAnimation = 0;
    switch (mAnimationOrder) {
        case 8: {
            mListData.insert(mListData.begin() + deleteIndex, deleteValue);
            if (deleteIndex != 0 && deleteIndex != mListData.size() - 1) {
                std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
                    deleteValue, mFontsHolder[Fonts::FiraSansRegular], 0, "temp", 0,
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (deleteIndex)*250*Constant::scaleX + 60*Constant::scaleX, 560*Constant::scaleX), 
                    sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255)
                );
                mSceneLayers[Nodes]->getChildren().insert(mSceneLayers[Nodes]->getChildren().begin() + deleteIndex, std::move(newNode));
            } else {
                std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
                    deleteValue, mFontsHolder[Fonts::FiraSansRegular], 0, "temp", 0,
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (deleteIndex)*250*Constant::scaleX + 60*Constant::scaleX, 310*Constant::scaleX), 
                    sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255)
                );
                mSceneLayers[Nodes]->getChildren().insert(mSceneLayers[Nodes]->getChildren().begin() + deleteIndex, std::move(newNode));
            }
            if (mListData.size() == 1) {
                mAnimationOrder = 7;
                break;
            }
            if (deleteIndex != 0 && deleteIndex != mListData.size() - 1) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 0), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + deleteIndex*250*Constant::scaleX + 130*Constant::scaleX - 22*Constant::scaleX, 545*Constant::scaleX), -66.8
                );
                mSceneLayers[Arrow]->getChildren().insert(mSceneLayers[Arrow]->getChildren().begin() + deleteIndex, std::move(newArrow));
                std::unique_ptr<SpriteNode> newDLLArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::leftArrow], sf::Vector2f(0, 0), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + deleteIndex*250*Constant::scaleX + 130*Constant::scaleX - 22*Constant::scaleX, 565*Constant::scaleX), -66.8
                );
                mSceneLayers[DLLArrow]->getChildren().insert(mSceneLayers[DLLArrow]->getChildren().begin() + deleteIndex, std::move(newDLLArrow));
            } else {
                if (deleteIndex == 0) {
                    std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                        mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 0),  
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + deleteIndex*250*Constant::scaleX + 130*Constant::scaleX + 22*Constant::scaleX, 295*Constant::scaleX), 0
                    );
                    mSceneLayers[Arrow]->getChildren().insert(mSceneLayers[Arrow]->getChildren().begin() + deleteIndex, std::move(newArrow));
                    std::unique_ptr<SpriteNode> newDLLArrow = std::make_unique<SpriteNode>(
                        mTexturesHolder[Textures::leftArrow], sf::Vector2f(0, 0),  
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + deleteIndex*250*Constant::scaleX + 130*Constant::scaleX + 22*Constant::scaleX, 315*Constant::scaleX), 0
                    );
                    mSceneLayers[DLLArrow]->getChildren().insert(mSceneLayers[DLLArrow]->getChildren().begin() + deleteIndex, std::move(newDLLArrow));
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({3, 4});
                    int index = 0;
                    for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                        if (index == 1) {
                            child->setLabel("head");
                            break;
                        }
                        index++;
                    }
                } else {
                    std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                        mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 0),  
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (deleteIndex - 1)*250*Constant::scaleX + 130*Constant::scaleX + 22*Constant::scaleX, 295*Constant::scaleX), 0
                    );
                    mSceneLayers[Arrow]->getChildren().insert(mSceneLayers[Arrow]->getChildren().begin() + deleteIndex - 1, std::move(newArrow));
                    std::unique_ptr<SpriteNode> newDLLArrow = std::make_unique<SpriteNode>(
                        mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 0),  
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (deleteIndex - 1)*250*Constant::scaleX + 130*Constant::scaleX + 22*Constant::scaleX, 315*Constant::scaleX), 0
                    );
                    mSceneLayers[DLLArrow]->getChildren().insert(mSceneLayers[Arrow]->getChildren().begin() + deleteIndex - 1, std::move(newDLLArrow));
                }
            }
            if (deleteIndex == 0 || deleteIndex == mListData.size() - 1) mAnimationOrder = 7;
            else mAnimationOrder = 5;
            break;
        }

        case 7: {
            if (deleteIndex == 0 && mListData.size()%2 != 0 && mListData.size() != 1) {
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index > 0) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
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
                            child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneMoving = 0;
                        }
                    }
                    index++;
                }
                index = 0;
                for (auto &child : mSceneLayers[DLLArrow]->getChildren()) {
                    if (index > 0) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
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
                            child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
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
                            child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneMoving = 0;
                        }
                    }
                    index++;
                }
                index = 0;
                for (auto &child : mSceneLayers[DLLArrow]->getChildren()) {
                    if (index < deleteIndex - 1) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
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
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index == 0) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed*1.5, 100*Constant::scaleX, 0, 0);
                        } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                            mAnimationOrder = 2;
                        }
                    } else if (index == 1) {
                        if (mListData.size() != 2) child->setLabel("");
                        else child->setLabel("tail");
                        break;
                    }
                    index++;
                }
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*2, 110*Constant::scaleX, speed, 50*Constant::scaleX);
                        child->triggerMoveAnimation(dt, speed*2, 30*Constant::scaleX, 45 - 180);
                    }
                    break;
                }
                for (auto &child : mSceneLayers[DLLArrow]->getChildren()) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*2, 110*Constant::scaleX, speed, 50*Constant::scaleX);
                        child->triggerMoveAnimation(dt, speed*2, 30*Constant::scaleX, 45 - 180);
                    }
                    break;
                }
            } else if (deleteIndex == mListData.size() - 1) {
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index == mListData.size() - 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed*1.5, 100*Constant::scaleX, 0, 0);
                        }
                    }
                    else if (index == mListData.size() - 2) {
                        if (mListData.size() != 2) child->setLabel("cur");
                        else child->setLabel("head/cur");
                    }
                    index++;
                }
                index = 0;
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (index == deleteIndex - 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed*2, 110*Constant::scaleX, speed, 50*Constant::scaleX);
                            child->triggerMoveAnimation(dt, speed*2, 30*Constant::scaleX, 45 - 180);
                        } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                            mAnimationOrder = 2;
                        }
                    }
                    index++;
                }
                index = 0;
                for (auto &child : mSceneLayers[DLLArrow]->getChildren()) {
                    if (index == deleteIndex - 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed*2, 110*Constant::scaleX, speed, 50*Constant::scaleX);
                            child->triggerMoveAnimation(dt, speed*2, 30*Constant::scaleX, 45 - 180);
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
                        child->triggerScaleAnimation(dt, speed, 250*Constant::scaleX, 0, 0);
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({14, 15});
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        mAnimationOrder = 4;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[DLLArrow]->getChildren()) {
                if (index == deleteIndex - 1) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed, 250*Constant::scaleX, 0, 0);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index > deleteIndex && mListData.size()%2 != 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                } else if (index < deleteIndex && mListData.size()%2 == 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
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
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                } else if (index < deleteIndex && mListData.size()%2 == 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[DLLArrow]->getChildren()) {
                if (index > deleteIndex && mListData.size()%2 != 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                } else if (index < deleteIndex && mListData.size()%2 == 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
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
                        child->triggerScaleAnimation(dt, speed*2, (110/std::cos(66.8*std::atan(1)*4/180))*Constant::scaleX, speed, 50*Constant::scaleX);
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({12, 13});
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[DLLArrow]->getChildren()) {
                if (index == deleteIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*2, (110/std::cos(66.8*std::atan(1)*4/180))*Constant::scaleX, speed, 50*Constant::scaleX);
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
                        child->triggerScaleAnimation(dt, speed*1.5, 100*Constant::scaleX, 0, 0);
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
                        child->triggerScaleAnimation(dt, speed, -250*Constant::scaleX, 0, 0);
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({11});
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                    }
                }
                if (index == deleteIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerRotateAnimation(dt, speed, 66.8);
                        child->triggerScaleAnimation(dt, speed, (-(110/std::cos(66.8*std::atan(1)*4/180)) + 110)*Constant::scaleX, 0, 0);
                        child->triggerMoveAnimation(dt, speed, 270*Constant::scaleX, 94.5 + 180);
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
            for (auto &child : mSceneLayers[DLLArrow]->getChildren()) {
                if (index == deleteIndex - 1) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed, -250*Constant::scaleX, 0, 0);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                    }
                }
                if (index == deleteIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerRotateAnimation(dt, speed, 66.8);
                        child->triggerScaleAnimation(dt, speed, (-(110/std::cos(66.8*std::atan(1)*4/180)) + 110)*Constant::scaleX, 0, 0);
                        child->triggerMoveAnimation(dt, speed, 270*Constant::scaleX, 94.5 + 180);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        child->mIsDoneMoving = 0;
                        child->mIsDoneRotating = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == deleteIndex) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, -90);
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
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({8, 9, 10});  
                        if (index != 0) child->setLabel("cur");
                        else child->setLabel("head/cur");
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        if (index != 0) child->setLabel("");
                        else child->setLabel("head");
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
                            dt, speed, 
                            sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        if (deleteIndex == 0) {
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2});
                            child->setLabel("head");
                        } else if (deleteIndex == mListData.size() - 1) {
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({8, 9, 10});
                            child->setLabel("tail");
                        }
                        else {
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({8, 9, 10}); 
                            child->setLabel("");
                        }
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        if (deleteIndex != 0) this->mColorIndex--;
                        else mAnimationOrder = 1;
                        if (mListData.size() == 1) mSceneLayers[Nodes]->getChildren().front()->setLabel("head/tail");
                        else if (mListData.size() == 2) {
                            mSceneLayers[Nodes]->getChildren().front()->setLabel("head");
                            mSceneLayers[Nodes]->getChildren().back()->setLabel("tail");
                        }
                    }  
                }
                index++;
            }
            break;
        }
    }
}   

void DLLState::updateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
        (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::SinglyLinkedListUpdate])
    ) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::SinglyLinkedListUpdate], mFontsHolder[Fonts::FiraMonoRegular], 25*Constant::scaleX,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::SinglyLinkedListUpdate] = 1;
    }
    switch (mAnimationOrder) {
        case 1: {
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsColoring && !child->mIsDoneColoring) {
                    child->triggerColorAnimation(
                        dt, speed, 
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255),
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                    );
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
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
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2, 3, 4});
                        if (index != 0) child->setLabel("cur");
                        else child->setLabel("head/cur");
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        if (index != 0) child->setLabel("");
                        else child->setLabel("head");
                        child->mIsDoneColoring = 0;
                        this->mColorIndex++;
                        if (this->mColorIndex > updateIndex && !mIsActionPaused) {
                            this->mColorIndex--;
                            child->setLabel("cur");
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
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({5});
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
                mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({6});
            }
            break;
        }
    }
}

void DLLState::updateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue) {
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
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({5});
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
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2, 3, 4});
                        if (index != 0) child->setLabel("cur");
                        else child->setLabel("head/cur");
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        if (index != 0) child->setLabel("");
                        else child->setLabel("head");
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

void DLLState::searchAnimation(sf::Time dt, double speed, int searchValue) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
        (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::SinglyLinkedListSearch])
    ) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::SinglyLinkedListSearch], mFontsHolder[Fonts::FiraMonoRegular], 25*Constant::scaleX,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::SinglyLinkedListSearch] = 1;
    }
    switch(mAnimationOrder) {
        case 1: {
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsColoring && !child->mIsDoneColoring) {
                    child->triggerColorAnimation(
                        dt, speed, 
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255),
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                    );
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
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
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2, 6, 7});
                        if (index != 0) child->setLabel("cur");
                        else child->setLabel("head/cur");
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        if (index != 0) child->setLabel("");
                        else child->setLabel("head");
                        child->mIsDoneColoring = 0;
                        this->mColorIndex++;
                        if (std::stoi(child->getStringData()) == searchValue) {
                            child->setLabel("cur");
                            this->mColorIndex--;    
                            mAnimationOrder = 3;
                        } else if (this->mColorIndex == mListData.size()) {
                            child->setLabel("cur");
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
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({3, 4, 5});
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
                if (mColorIndex == mListData.size()) {
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({8});
                }
                mIsEndAnimation = 1;
            }
        }
    }
}

void DLLState::searchAnimationReversed(sf::Time dt, double speed, int searchValue) {
    mIsEndAnimation = 0;
    switch(mAnimationOrder) {
        case 4: {
            if (this->mColorIndex == mListData.size()) {
                this->mColorIndex--;
                mAnimationOrder = 2;
            } 
            else {
                mAnimationOrder = 3;
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
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({3, 4, 5});
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
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2, 6, 7});
                        if (index != 0) child->setLabel("cur");
                        else child->setLabel("head/cur");
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        if (index != 0) child->setLabel("");
                        else child->setLabel("head");
                        child->mIsDoneColoring = 0;
                        this->mColorIndex--;
                        if (this->mColorIndex < 0) {
                            mAnimationOrder = 1;
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
                        }
                    }
                }
                index++;
            }
            break;
        }
    }
}