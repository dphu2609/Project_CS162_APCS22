#include <State/CLLState.hpp>

void CLLState::createDataStructure(std::vector<int> list) {
    for (int i = 0; i < LayerCount; i++) {
        mSceneLayers[i]->getChildren().clear();
    }
    if (list.size() == 0) return;
    mListData = list;
    for (int i = 0; i < mListData.size(); i++) {
        if (i != 0) {
            std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
                mListData[i], mFontsHolder[Fonts::FiraSansRegular], 100, 
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + i*250, 250), 
                sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
            );
            mSceneLayers[Nodes]->attachChild(std::move(newNode));
        } else {
            std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
                mListData[i], mFontsHolder[Fonts::FiraSansRegular], 100, "head", 50, 
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + i*250, 250), 
                sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
            );
            mSceneLayers[Nodes]->attachChild(std::move(newNode));
        }
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
    if (insertIndex != 0) {
        if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
            (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::CircularLinkedListInsert])
        ) {
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
    } else {
        if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
            (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::CircularLinkedListInsertHead])
        ) {
            mSceneLayers[CodeBox]->getChildren().clear();
            std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
                mWindow, mCodeHolder[Code::CircularLinkedListInsertHead], mFontsHolder[Fonts::FiraMonoRegular], 25,
                sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
            );
            mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
            for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
                mCodeHolder.mStateActivated[i] = 0;
            }
            mCodeHolder.mStateActivated[Code::CircularLinkedListInsertHead] = 1;
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
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    if (insertIndex != 0) mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
                    else mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({6});
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
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        if (insertIndex != 0) mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2, 3, 4});    
                        else mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({7, 8, 9});
                        if (index != 0) child->setLabel("cur");
                        else child->setLabel("head/cur");
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex++;
                        if (index != 0) child->setLabel("");
                        else child->setLabel("head");
                        if (insertIndex != 0 && this->mColorIndex >= insertIndex) {
                            this->mColorIndex--;
                            if (insertIndex != 1) child->setLabel("cur");
                            else child->setLabel("head/cur");
                            mAnimationOrder = 3;
                            break;
                        } else if (this->mColorIndex >= mListData.size() && insertIndex == 0) {
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
            if (mSceneLayers[NewNode]->getChildren().size() == 0) {
                if (mListData.size() > 0) {
                    std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                        insertValue, mFontsHolder[Fonts::FiraSansRegular], 100, "newNode", 50,
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250, 750), 
                        sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
                    );
                    mSceneLayers[NewNode]->attachChild(std::move(addedNode));
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    if (insertIndex != 0) mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({5});    
                    else mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({10});
                } else {
                    std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                        insertValue, mFontsHolder[Fonts::FiraSansRegular], 100, "newNode", 50,
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250, 500), 
                        sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
                    );
                    mSceneLayers[NewNode]->attachChild(std::move(addedNode));
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2});    
                    mAnimationOrder = 6;
                    break;
                }
            }
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250, -90);
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
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    if (mListData.size() == 0) mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({3});
                    else if (insertIndex != 0) mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({6});    
                    else mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({11});
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
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        if (insertIndex != 0) mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({7});    
                        else mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({12});
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
            for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                if (index == insertIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerRotateAnimation(dt, speed, -66.8);
                        child->triggerScaleAnimation(dt, speed*0.99, -(110/std::cos(66.8*std::atan(1)*4/180)) + 110, 0, 0);
                        child->triggerMoveAnimation(dt, speed*2, 25, -150);
                    } else if (!child->mIsScaling && child->mIsDoneScaling) {
                        child->mIsDoneMoving = 0;
                    }
                    break;
                }
                index++;
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
            std::string str;
            if (insertIndex == 0) {
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    child->setLabel("");
                    break;
                }
                str = "head";
                mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                if (mListData.size() == 0) mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({4});    
                else mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({13});
            }
            else str = "newNode";

            std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                insertValue, mFontsHolder[Fonts::FiraSansRegular], 100, str, 50,
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250, 250), 
                sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
            );
            mSceneLayers[Nodes]->getChildren().insert(mSceneLayers[Nodes]->getChildren().begin() + insertIndex, std::move(addedNode));

            if (mListData.size() == 0) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(110, 50), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 - 120, 285), 0
                );
                mSceneLayers[Arrow]->attachChild(std::move(newArrow)); 
            }
            else if (insertIndex != mListData.size()) {
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
void CLLState::insertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue) {
    mIsEndAnimation = 0;
    switch (mAnimationOrder) {
        case 10: {
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
                        mAnimationOrder = 9;
                    }
                }
                for (auto &child : this->mSceneLayers[CLLArrow]->getChildren()) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 0);
                    }
                    else if (!child->mIsMoving && child->mIsDoneMoving) {
                        child->mIsDoneMoving = 0;
                    }
                }
            }
            else mAnimationOrder = 9;
            break;
        }
        case 9: {
            mSceneLayers[Nodes]->getChildren().erase(mSceneLayers[Nodes]->getChildren().begin() + insertIndex);
            if (insertIndex != mListData.size() - 1 || mListData.size() == 1)
                mSceneLayers[Arrow]->getChildren().erase(mSceneLayers[Arrow]->getChildren().begin() + insertIndex + 1); 

            mListData.erase(mListData.begin() + insertIndex);

            std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                insertValue, mFontsHolder[Fonts::FiraSansRegular], 100, "newNode", 50,
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250, 250), 
                sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
            );
            mSceneLayers[NewNode]->attachChild(std::move(addedNode));

            if (insertIndex != mListData.size() && mListData.size() != 0) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(110, 50), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex + 1)*250 - 120, 285), 0
                );
                mSceneLayers[NewArrow]->attachChild(std::move(newArrow));
            }
            if (mListData.size() == 0) {
                mSceneLayers[CLLArrow]->getChildren().clear();
                mAnimationOrder = 3;
            }
            else if (insertIndex == mListData.size()) mAnimationOrder = 8;
            else mAnimationOrder = 6;

            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
            if (mListData.size() == 0) mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({3});    
            else if (insertIndex != 0) mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({7});
            else mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({12});
            break;
        }
        case 8: {
            int index = 0;
            for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                if (index == mListData.size()) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed, -110, 0, 0);
                        std::cout << 1;
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                        mSceneLayers[Arrow]->getChildren().pop_back();
                        mAnimationOrder = 7;
                    }
                }
                index++;
            }
            break;
        }
        case 7: {
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {   
                    child->triggerMoveAnimation(dt, speed, 250, 90);
                } else if (!child->mIsMoving && child->mIsDoneMoving) {
                    child->mIsDoneMoving = 0;
                    mAnimationOrder = 3;
                }
            }
            int index = 0;
            for (auto &child : mSceneLayers[CLLArrow]->getChildren()) {
                if (index == 0 || index == 1) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving) {
                        child->mIsDoneMoving = 0;
                    }
                } else if (index == 2) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed, -250, 0, 0);
                    }
                }
                index++;
            }
            break;
        }
        case 6: {
            int index = 0;
            for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                if (index == insertIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerRotateAnimation(dt, speed, 66.8);
                        child->triggerScaleAnimation(dt, speed*0.99, (110/std::cos(66.8*std::atan(1)*4/180)) - 110, 0, 0);
                        child->triggerMoveAnimation(dt, speed*2, 25, 30);
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
                if (index >= insertIndex + 1) {
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
                    mAnimationOrder = 5;
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
            index = 0;
            for (auto &child : mSceneLayers[CLLArrow]->getChildren()) {
                if (index == 0 || index == 1) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                } else if (index == 2) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed, -250, 0, 0);
                    }
                }
                index++;
            }
            break;
        }
        case 5: {
            int index = 0;
            for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                if (index == insertIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerRotateAnimation(dt, speed, -66.8);
                        child->triggerScaleAnimation(dt, speed*0.8, -(110/std::cos(66.8*std::atan(1)*4/180)) + 110, 0, 0);
                        child->triggerMoveAnimation(dt, speed*2, 25, 210);
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        if (insertIndex != 0) mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({6});    
                        else mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({11});
                    } 
                    else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        child->mIsDoneRotating = 0;
                        child->mIsDoneMoving = 0;
                        mAnimationOrder = 4;
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
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    if (mListData.size() == 0) mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2});
                    else if (insertIndex != 0) mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({5});    
                    else mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({10});
                } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                    child->mIsDoneScaling = 0;
                    mAnimationOrder = 3;
                    this->mSceneLayers[NewArrow]->getChildren().clear();
                }
            }
            break;
        }
        case 3: {
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250, 90);
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    if (mListData.size() == 0) mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2});
                    else if (insertIndex != 0) mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({5});    
                    else mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({10});
                } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                    if (mSceneLayers[NewNode]->getChildren().size() != 0) 
                        mSceneLayers[NewNode]->getChildren().clear();
                    if (mListData.size() == 0) mAnimationOrder = 1;
                    else mAnimationOrder = 2;
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
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        if (insertIndex != 0) mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2, 3, 4});    
                        else mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({7, 8, 9});
                        if (index != 0) child->setLabel("cur");
                        else child->setLabel("head/cur");
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        if (index != 0) child->setLabel("");
                        else child->setLabel("head");
                        child->mIsDoneColoring = 0;
                        this->mColorIndex--;
                        if (this->mColorIndex < 0) {
                            this->mColorIndex = 0;
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            if (insertIndex != 0) mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});    
                            else mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({6});
                            mAnimationOrder = 1;
                        }
                    }
                }
                index++;
            }
        }
    }
}
void CLLState::deleteAnimation(sf::Time dt, double speed, int deleteIndex) {
    if (deleteIndex != 0) {
        if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
            (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::CircularLinkedListDelete])
        ) {
            mSceneLayers[CodeBox]->getChildren().clear();
            std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
                mWindow, mCodeHolder[Code::CircularLinkedListDelete], mFontsHolder[Fonts::FiraMonoRegular], 25,
                sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
            );
            mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
            for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
                mCodeHolder.mStateActivated[i] = 0;
            }
            mCodeHolder.mStateActivated[Code::CircularLinkedListDelete] = 1;
        }
    } else {
        if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
            (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::CircularLinkedListDeleteHead])
        ) {
            mSceneLayers[CodeBox]->getChildren().clear();
            std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
                mWindow, mCodeHolder[Code::CircularLinkedListDeleteHead], mFontsHolder[Fonts::FiraMonoRegular], 25,
                sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
            );
            mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
            for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
                mCodeHolder.mStateActivated[i] = 0;
            }
            mCodeHolder.mStateActivated[Code::CircularLinkedListDeleteHead] = 1;
        }
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
                    if (deleteIndex != 0) mAnimationOrder = 2;
                    else mAnimationOrder = 3;
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
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2, 3, 4});
                        if (index != 0) child->setLabel("cur");
                        else child->setLabel("head/cur");
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        if (index != 0) child->setLabel("");
                        else child->setLabel("head");
                        child->mIsDoneColoring = 0;
                        this->mColorIndex++;
                        if (this->mColorIndex >= deleteIndex) child->setLabel("cur");
                    }
                } else if (index == this->mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255),
                            sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255)
                        );
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({5});
                        child->setLabel("temp");
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex++;
                        if (this->mColorIndex > deleteIndex) {
                            this->mColorIndex--;
                            mAnimationOrder = 4;
                        }
                    }  
                }
                index++;
            }
            break;
        }
        case 3: {
            if (mListData.size() != 1) {
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
                            child->mIsDoneColoring = 0;
                            if (index != 0) child->setLabel("");
                            else child->setLabel("head");
                            this->mColorIndex++;
                        }
                    }
                    index++;
                }
            } else mColorIndex = 1;
            if (this->mColorIndex >= mListData.size()) {
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index == 0) {
                        if (!child->mIsColoring && !child->mIsDoneColoring) {
                            child->triggerColorAnimation(
                                dt, speed, 
                                sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255),
                                sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255)
                            );
                            child->setLabel("temp");
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({5, 6});
                        } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                            child->mIsDoneColoring = 0;
                            if (mListData.size() == 1) mAnimationOrder = 7;
                            else mAnimationOrder = 4;
                        }
                    } else if (index == 1) {
                        child->setLabel("head");
                        break;
                    }
                    index++;
                }
            }
            break;
        }
        case 4: {
            int index = 0;
            if (deleteIndex != mListData.size() - 1) {
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (index == deleteIndex) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed, 250, 0, 0);
                        } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                            child->mIsDoneScaling = 0;
                        }
                    }
                    if (index == deleteIndex + 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerRotateAnimation(dt, speed, -66.8);
                            child->triggerScaleAnimation(dt, speed, (110/std::cos(66.8*std::atan(1)*4/180)) - 110, 0, 0);
                            child->triggerMoveAnimation(dt, speed, 270, 94.5);
                        } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                            child->mIsDoneScaling = 0;
                            child->mIsDoneMoving = 0;
                            child->mIsDoneRotating = 0;
                            mAnimationOrder = 5;
                        }
                    }
                    index++;
                }
            } 
            else {
                for (auto &child : mSceneLayers[CLLArrow]->getChildren()) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerRotateAnimation(dt, speed, -66.4);
                        child->triggerScaleAnimation(dt, speed, (110/std::cos(66.8*std::atan(1)*4/180)) - 55, 0, 0);
                        child->triggerMoveAnimation(dt, speed, 310, 94.5);
                        mSceneLayers[Arrow]->getChildren().pop_back();
                        std::unique_ptr<ContainerNode> newCLLArrow1st = std::make_unique<ContainerNode>(
                            mWindow, sf::Vector2f(110, 5), 0, sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (mListData.size() - 1)*250 - 130, 305),
                            sf::Color(240, 114, 53, 255), sf::Color::Transparent
                        );
                        mSceneLayers[Arrow]->attachChild(std::move(newCLLArrow1st));
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;  
                        child->mIsDoneMoving = 0;
                        child->mIsDoneRotating = 0;
                        mAnimationOrder = 5;
                    }
                    break;
                }
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (index == deleteIndex) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed, 250, 0, 0);
                        } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                            child->mIsDoneScaling = 0;
                        }
                    }
                    index++;
                }
            }
            index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == deleteIndex) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 90);
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        if (deleteIndex != 0)  mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({6});
                        else  mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({7});
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            break;
        }
        case 5: {
            int index = 0;
            if (deleteIndex != mListData.size() - 1) {
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (index == deleteIndex + 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed*2, -(110/std::cos(66.8*std::atan(1)*4/180)), speed, -50);
                        } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                            mAnimationOrder = 6;
                        }
                    }
                    index++;
                }
            }
            else {
                for (auto &child : mSceneLayers[CLLArrow]->getChildren()) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*2, -(110/std::cos(66.8*std::atan(1)*4/180)) - 55, speed, -5);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        mAnimationOrder = 6;
                    }
                    break;
                }
            }
            index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == deleteIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*1.5, -100, 0, 0);
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        if (deleteIndex != 0)  mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({7});
                        else  mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({8});
                    }
                }
                index++;
            }
            break;
        }
        case 6: {
            int index = 0;
            for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                if (index == deleteIndex) {
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
                if (index > deleteIndex + 1 && mListData.size()%2 != 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                } else if (index < deleteIndex + 1 && mListData.size()%2 == 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            if (mListData.size()%2 != 0) {
                index = 0;
                for (auto &child : mSceneLayers[CLLArrow]->getChildren()) {
                    if (index == 0 || index == 1) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250, 180);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneMoving = 0;
                        }
                    } else if (index == 2) {
                        if (!child->mIsScaling && !child->mIsDoneScaling && !mIsActionPaused) {
                            child->triggerScaleAnimation(dt, speed, -250, 0, 0);
                        }
                    }
                    index++;
                }
            } else {
                index = 0;
                for (auto &child : mSceneLayers[CLLArrow]->getChildren()) {
                    if (index == 3) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250, 0);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneMoving = 0;
                        }
                    } else if (index == 2) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerScaleAnimation(dt, speed, -250, 0, 0);
                            child->triggerMoveAnimation(dt, speed, 250, 0);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneScaling = 0;
                            child->mIsDoneMoving = 0;
                        }
                    }
                    index++;
                }
            }
            break;
        }
        case 7: {
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed*2, -100, 0, 0);
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({8});
                } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                    mAnimationOrder = 8;
                }
                break;
            }
            int index = 0;
            for (auto &child : mSceneLayers[CLLArrow]->getChildren()) {
                if (index == 0) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, 0, 0, speed, -5);
                    }
                }
                else if (index == 1 || index == 3) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed, -5, 0, 0);
                    }
                }
                else if (index == 2) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, 0, 0, speed, -5);
                    }
                }
                index++;
            }
            for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed*2, -110, speed, -50);
                }
                break;
            }
            break;
        }
        case 8: {
            if (!mIsEndAnimation) {
                mSceneLayers[Nodes]->getChildren().erase(mSceneLayers[Nodes]->getChildren().begin() + deleteIndex);
                if (deleteIndex == mListData.size() - 1) {
                    mSceneLayers[CLLArrow]->getChildren()[0] = std::move(mSceneLayers[Arrow]->getChildren().back());
                }
                if (mListData.size() == 0) {
                    mSceneLayers[CLLArrow]->getChildren().clear();
                }
                mSceneLayers[Arrow]->getChildren().erase(mSceneLayers[Arrow]->getChildren().begin() + deleteIndex + 1);
                mListData.erase(mListData.begin() + deleteIndex);
                mIsEndAnimation = 1;
                mIsReplay = 0;
            }
            break;
        }
    }
}
void CLLState::deleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue) {
    mIsEndAnimation = 0;
    switch (mAnimationOrder) {
        case 8: {
            if (!mIsReplay) {
                mListData.insert(mListData.begin() + deleteIndex, deleteValue);
                if (mListData.size() != 1) {
                    std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
                        deleteValue, mFontsHolder[Fonts::FiraSansRegular], 0, "temp", 0,
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (deleteIndex)*250 + 60, 560), 
                        sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255)
                    );
                    mSceneLayers[Nodes]->getChildren().insert(mSceneLayers[Nodes]->getChildren().begin() + deleteIndex, std::move(newNode));
                } else {
                    std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
                        deleteValue, mFontsHolder[Fonts::FiraSansRegular], 0, "temp", 0,
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (deleteIndex)*250 + 60, 310), 
                        sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255)
                    );
                    mSceneLayers[Nodes]->getChildren().insert(mSceneLayers[Nodes]->getChildren().begin() + deleteIndex, std::move(newNode));
                }
            }
            if (deleteIndex != mListData.size() - 1) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 0), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + deleteIndex*250 + 130 - 22, 555), -66.8
                );
                mSceneLayers[Arrow]->getChildren().insert(mSceneLayers[Arrow]->getChildren().begin() + deleteIndex + 1, std::move(newArrow));
                mAnimationOrder = 6;
                break;
            } else if (mListData.size() != 1) {
                if (!mIsReplay) {
                    mSceneLayers[Arrow]->getChildren().push_back(std::move(mSceneLayers[CLLArrow]->getChildren()[0]));
                    if (mListData.size()%2 == 0) {
                        std::unique_ptr<ContainerNode> newCLLArrow = std::make_unique<ContainerNode>(
                            mWindow, sf::Vector2f(0, 0), 0, sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + deleteIndex*250 + 130 - 30, 610),
                            sf::Color(240, 114, 53, 255), sf::Color::Transparent
                        );
                        mSceneLayers[CLLArrow]->getChildren()[0] = std::move(newCLLArrow);
                    } else {
                        std::unique_ptr<ContainerNode> newCLLArrow = std::make_unique<ContainerNode>(
                            mWindow, sf::Vector2f(0, 0), 0, sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (deleteIndex - 1)*250 + 130 - 30, 610),
                            sf::Color(240, 114, 53, 255), sf::Color::Transparent
                        );
                        mSceneLayers[CLLArrow]->getChildren()[0] = std::move(newCLLArrow);
                    }
                    mIsReplay = 1;
                }
                for (auto &child : mSceneLayers[CLLArrow]->getChildren()) { 
                    if (!child->mIsRotating && !child->mIsDoneRotating) {
                        child->triggerRotateAnimation(dt, 100, -83.f);
                    }
                    else if (!child->mIsRotating && child->mIsDoneRotating) {
                        child->mIsDoneRotating = 0;
                        mAnimationOrder = 6;
                    }
                    break;
                }
            } else {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 0), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + deleteIndex*250 - 120, 285), 0
                );
                mSceneLayers[Arrow]->attachChild(std::move(newArrow));
                
                std::unique_ptr<ContainerNode> newCLLArrow1st = std::make_unique<ContainerNode>(
                    mWindow, sf::Vector2f(110, 5), 0, sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + mListData.size()*250 - 130, 305),
                    sf::Color(240, 114, 53, 255), sf::Color::Transparent
                );
                mSceneLayers[CLLArrow]->attachChild(std::move(newCLLArrow1st));

                std::unique_ptr<ContainerNode> newCLLArrow2nd = std::make_unique<ContainerNode>(
                    mWindow, sf::Vector2f(0, 175), 0, sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + mListData.size()*250 - 20, 135),
                    sf::Color(240, 114, 53, 255), sf::Color::Transparent
                );
                mSceneLayers[CLLArrow]->attachChild(std::move(newCLLArrow2nd));

                std::unique_ptr<ContainerNode> newCLLArrow3rd = std::make_unique<ContainerNode>(
                    mWindow, sf::Vector2f(mListData.size()*250 + 100, 0), 0, sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 - 120, 135),
                    sf::Color(240, 114, 53, 255), sf::Color::Transparent
                );
                mSceneLayers[CLLArrow]->attachChild(std::move(newCLLArrow3rd));

                std::unique_ptr<ContainerNode> newCLLArrow4th = std::make_unique<ContainerNode>(
                    mWindow, sf::Vector2f(0, 175), 0, sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 - 120, 135),
                    sf::Color(240, 114, 53, 255), sf::Color::Transparent
                );
                mSceneLayers[CLLArrow]->attachChild(std::move(newCLLArrow4th));
                mAnimationOrder = 7;
                break;
            }
            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
            if (deleteIndex != 0)  mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({7});
            else  mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({8});
            break;
        }
        case 7: {
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed*2, 100, 0, 0);
                } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                    mAnimationOrder = 3;
                }
                break;
            }
            int index = 0;
            for (auto &child : mSceneLayers[CLLArrow]->getChildren()) {
                if (index == 0 || index == 2) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, 0, 0, speed*2, 5);
                    }
                }
                else if (index == 1 || index == 3) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*2, 5, 0, 0);
                    }
                }
                index++;
            }
            for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed*2, 110, speed, 50);
                }
                break;
            }
            break;
        }
        case 6: {
            int index = 0;
            for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                if (index == deleteIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed, 250, 0, 0);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        mAnimationOrder = 5;
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
                if (index > deleteIndex + 1 && mListData.size()%2 != 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 0);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                } else if (index < deleteIndex + 1 && mListData.size()%2 == 0) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, 180);
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            if (mListData.size()%2 != 0) {
                index = 0;
                for (auto &child : mSceneLayers[CLLArrow]->getChildren()) {
                    if (index == 0 || index == 1) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250, 0);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneMoving = 0;
                        }
                    } else if (index == 2) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed, 250, 0, 0);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneMoving = 0;
                        }
                    }
                    index++;
                }
            } else {
                index = 0;
                for (auto &child : mSceneLayers[CLLArrow]->getChildren()) {
                    if (index == 3) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250, 180);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneMoving = 0;
                        }
                    } else if (index == 2) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerScaleAnimation(dt, speed, 250, 0, 0);
                            child->triggerMoveAnimation(dt, speed, 250, 180);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneMoving = 0;
                        }
                    }
                    index++;
                }
            }
            break;
        }
        case 5: {
            int index = 0;
            if (deleteIndex != mListData.size() - 1) {
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (index == deleteIndex + 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed*2, (110/std::cos(66.8*std::atan(1)*4/180)), speed, 50);
                        } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                            child->mIsDoneScaling = 0;
                            mAnimationOrder = 4;
                        }
                    }
                    index++;
                }
            }
            else {
                for (auto &child : mSceneLayers[CLLArrow]->getChildren()) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*2, (110/std::cos(66.8*std::atan(1)*4/180)) + 50, speed, 5);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        mAnimationOrder = 4;
                    }
                    break;
                }
            }
            index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == deleteIndex) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerScaleAnimation(dt, speed*1.5, 100, 0, 0);
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        if (deleteIndex != 0)  mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({6});
                        else  mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({7});
                    }
                }
                index++;
            }
            break;
        }
        case 4: {
            int index = 0;
            if (deleteIndex != mListData.size() - 1) {
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (index == deleteIndex) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed, -250, 0, 0);
                        } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                            child->mIsDoneScaling = 0;
                        }
                    }
                    if (index == deleteIndex + 1) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerRotateAnimation(dt, speed, 66.8);
                            child->triggerScaleAnimation(dt, speed, -(110/std::cos(66.8*std::atan(1)*4/180)) + 110, 0, 0);
                            child->triggerMoveAnimation(dt, speed, 270, 94.5 + 180);
                        } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                            child->mIsDoneScaling = 0;
                            child->mIsDoneMoving = 0;
                            child->mIsDoneRotating = 0;
                            if (deleteIndex == 0) mAnimationOrder = 3;
                            else mAnimationOrder = 2;
                        }
                    }
                    index++;
                }
            } 
            else {
                for (auto &child : mSceneLayers[CLLArrow]->getChildren()) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerRotateAnimation(dt, speed, 66.4);
                        child->triggerScaleAnimation(dt, speed, -(110/std::cos(66.8*std::atan(1)*4/180)) + 60, 0, 0);
                        child->triggerMoveAnimation(dt, speed, 305, 94.5 + 180);
                    } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;  
                        child->mIsDoneMoving = 0;
                        child->mIsDoneRotating = 0;
                        mAnimationOrder = 2;
                    }
                    break;
                }
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (index == deleteIndex) {
                        if (!child->mIsScaling && !child->mIsDoneScaling) {
                            child->triggerScaleAnimation(dt, speed, -240, 0, 0);
                        } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                            child->mIsDoneScaling = 0;
                            mSceneLayers[Arrow]->getChildren().pop_back();
                            std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                                mTexturesHolder[Textures::rightArrow], sf::Vector2f(110, 50), 
                                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (deleteIndex)*250 - 120, 285), 0
                            );
                            mSceneLayers[Arrow]->attachChild(std::move(newArrow));
                        }
                    }
                    index++;
                }
            }
            index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == deleteIndex) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerMoveAnimation(dt, speed, 250, -90);
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        if (deleteIndex != 0)  mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({5});
                        else  mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({5, 6});
                    } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                        child->mIsDoneMoving = 0;
                    }
                }
                index++;
            }
            break;
        }
        case 3: {
            int index = 0;
            if (mListData.size() != 1) {
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index == this->mColorIndex) {
                        if (!child->mIsColoring && !child->mIsDoneColoring) {
                            child->triggerColorAnimation(
                                dt, speed, 
                                sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                                sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                            );
                            if (index != 0) child->setLabel("cur");
                            else child->setLabel("head/cur");
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2, 3, 4});
                        } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                            child->mIsDoneColoring = 0;
                            this->mColorIndex--;
                            if (index != 0) child->setLabel("");
                            else child->setLabel("head");
                            if (this->mColorIndex < 0) {
                                this->mColorIndex = 0;
                                mAnimationOrder = 1;
                            }
                        }
                    }
                    index++;
                }
            } else mColorIndex = 1;
            if (this->mColorIndex >= mListData.size()) {
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index == 0) {
                        if (!child->mIsColoring && !child->mIsDoneColoring) {
                            child->triggerColorAnimation(
                                dt, speed, 
                                sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255),
                                sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                            );
                            child->setLabel("head");
                        } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                            child->mIsDoneColoring = 0;
                            if (mListData.size() == 1) {
                                mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                                mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
                                mAnimationOrder = 1;
                            }
                            this->mColorIndex--;
                        }
                    } else if (index == 1) {
                        child->setLabel("");
                        break;
                    }
                    index++;
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
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                        if (index != 0) child->setLabel("cur");
                        else child->setLabel("head/cur");
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2, 3, 4});
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex--;
                        if (index != 0) child->setLabel("");
                        else child->setLabel("head");
                        if (this->mColorIndex < 0) {
                            this->mColorIndex = 0;
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
                            mAnimationOrder = 1;
                        }
                    }
                } else if (index == this->mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
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

void CLLState::updateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
        (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::SinglyLinkedListUpdate])
    ) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::SinglyLinkedListUpdate], mFontsHolder[Fonts::FiraMonoRegular], 25,
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

void CLLState::updateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue) {
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
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
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

void CLLState::searchAnimation(sf::Time dt, double speed, int searchValue) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
        (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::SinglyLinkedListSearch])
    ) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::SinglyLinkedListSearch], mFontsHolder[Fonts::FiraMonoRegular], 25,
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

void CLLState::searchAnimationReversed(sf::Time dt, double speed, int searchValue) {
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