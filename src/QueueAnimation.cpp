#include <State/QueueState.hpp>

void QueueState::createDataStructure(std::vector<int> list) {
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
            sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + i*250 + 130, 285), 0
        );
        mSceneLayers[Arrow]->attachChild(std::move(newArrow));
    }
}

void QueueState::insertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::SinglyLinkedListInsert])) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::QueuePush], mFontsHolder[Fonts::FiraMonoRegular], 25,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::QueuePush] = 1;
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
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == mListData.size() - 1) {
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
                        if (this->mColorIndex >= insertIndex && !mIsActionPaused) {
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
                std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                    insertValue, mFontsHolder[Fonts::FiraSansRegular], 100,
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250, 500), 
                    sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
                );
                mSceneLayers[NewNode]->attachChild(std::move(addedNode));
            }
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250, -90);
                    // mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    // mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({11});

                } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                    child->mIsDoneMoving = 0;
                    if (mListData.size() == 0) mAnimationOrder = 5;
                    else mAnimationOrder = 4;
                }
            }
            break;
        }
        case 4: {
            if (mSceneLayers[Arrow]->getChildren().size() != mListData.size()) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 50), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex - 1)*250 + 130, 285), 0
                );
                mSceneLayers[Arrow]->attachChild(std::move(newArrow));
            }
            int index = 0;
            for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                if (index == insertIndex - 1) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerScaleAnimation(dt, speed*0.8, 110, 0, 0);
                    }
                    else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        mAnimationOrder = 5;
                    }
                    break;
                }
                index++;
            }
            break;
        }
        case 5: {
            std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                insertValue, mFontsHolder[Fonts::FiraSansRegular], 100,
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250, 250), 
                sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
            );
            mSceneLayers[Nodes]->getChildren().insert(mSceneLayers[Nodes]->getChildren().begin() + insertIndex, std::move(addedNode));
            mListData.insert(mListData.begin() + insertIndex, insertValue);

            mSceneLayers[NewArrow]->getChildren().clear();
            mSceneLayers[NewNode]->getChildren().clear();

            mAnimationOrder = 6;
            break;
        }
        case 6: {
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
            }
            else {
                mIsEndAnimation = 1;
            }
        }
    }
}

void QueueState::insertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue) {
    mIsEndAnimation = 0;
    switch(mAnimationOrder) {
        case 6: {
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
        case 5: {
            mListData.erase(mListData.begin() + insertIndex);
            std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                insertValue, mFontsHolder[Fonts::FiraSansRegular], 100,
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (insertIndex)*250, 250), 
                sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
            );
            mSceneLayers[NewNode]->attachChild(std::move(addedNode));mSceneLayers[Nodes]->getChildren().erase(mSceneLayers[Nodes]->getChildren().begin() + insertIndex);
            mAnimationOrder = 4;
            break;
        }
        case 4: {
            int index = 0;
            for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                if (index == insertIndex - 1) {
                    if (!child->mIsMoving && !child->mIsDoneMoving) {
                        child->triggerScaleAnimation(dt, speed*0.8, 110, 0, 0);
                    }
                    else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                        child->mIsDoneScaling = 0;
                        mSceneLayers[Arrow]->getChildren().pop_back();
                        mAnimationOrder = 3;
                    }
                    break;
                }
                index++;
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
                    if (mListData.size() == 0) mAnimationOrder = 1;
                    else mAnimationOrder = 2;
                }
            }
            break;
        }
        case 2: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == mListData.size() - 1) {
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
                        if (this->mColorIndex >= insertIndex && !mIsActionPaused) {
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

void QueueState::deleteAnimation(sf::Time dt, double speed, int deleteIndex) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::SinglyLinkedListInsert])) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::QueuePop], mFontsHolder[Fonts::FiraMonoRegular], 25,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::QueuePop] = 1;
    }
    switch(mAnimationOrder) {
        case 1: {
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
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsColoring && !child->mIsDoneColoring) {
                    child->triggerColorAnimation(
                        dt, speed, 
                        sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255),
                        sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255)
                    );
                } else if (!child->mIsColoring && child->mIsDoneColoring) {
                    child->mIsDoneColoring = 0;
                    mAnimationOrder = 3;
                }
                break;
            }
            break;
        }
        case 3: {
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed*1.5, -100, 0, 0);
                } else if (!child->mIsScaling && child->mIsDoneScaling) {
                    mAnimationOrder = 4;
                }
                break;
            }
            for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed*2, -110, speed, -50);
                    child->triggerMoveAnimation(dt, speed*2, 30, 45);
                }
                break;
            }
        }
        case 4: {
            if (mListData.size()%2 != 0 && mListData.size() != 1) {
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index > 0) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250, 180);
                        } else if (!child->mIsMoving && child->mIsDoneMoving) {
                            child->mIsDoneMoving = 0;
                            mAnimationOrder = 5;
                        }
                    }
                    index++;
                }
                index = 0;
                for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                    if (index > 0) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250, 180);
                        } else if (!child->mIsMoving && child->mIsDoneMoving) {
                            child->mIsDoneMoving = 0;
                        }
                    }
                    index++;
                }
            }
            else mAnimationOrder = 5;
            break;
        }
        case 5: {
            if (!mIsEndAnimation) {
                mSceneLayers[Nodes]->getChildren().erase(mSceneLayers[Nodes]->getChildren().begin() + deleteIndex);
                if (mListData.size() != 1) mSceneLayers[Arrow]->getChildren().erase(mSceneLayers[Arrow]->getChildren().begin() + deleteIndex);
                mListData.erase(mListData.begin() + deleteIndex);
                mIsEndAnimation = 1;
            }
            break;
        }
    }
}

void QueueState:deleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue) {
    mIsEndAnimation = 0;
    switch (mAnimationOrder) {
        case 5: {
            mListData.insert(mListData.begin() + deleteIndex, deleteValue);
            std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
                deleteValue, mFontsHolder[Fonts::FiraSansRegular], 0,
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + (deleteIndex)*250 + 60, 310), 
                sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255)
            );
            mSceneLayers[Nodes]->getChildren().insert(mSceneLayers[Nodes]->getChildren().begin() + deleteIndex, std::move(newNode));
            if (mListData.size() != 1) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 0),  
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250 + deleteIndex*250 + 130 + 22, 305), 0
                );
                mSceneLayers[Arrow]->getChildren().insert(mSceneLayers[Arrow]->getChildren().begin() + deleteIndex, std::move(newArrow));
            }
            mAnimationOrder = 4;
            break;
        }
        case 4: {
            if (mListData.size()%2 != 0 && mListData.size() != 1) {
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index > 0) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250, 0);
                        } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                            child->mIsDoneMoving = 0;
                            mAnimationOrder = 3;
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
            }
            else mAnimationOrder = 3;
            break;
        }
        case 3: {
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed*1.5, 100, 0, 0);
                } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                    mAnimationOrder = 2;
                }
                break;
            }
            for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed*2, 110, speed, 50);
                    child->triggerMoveAnimation(dt, speed*2, 30, 45 - 180);
                }
                break;
            }
        }
        case 2: {
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsColoring && !child->mIsDoneColoring) {
                    child->triggerColorAnimation(
                        dt, speed, 
                        sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255),
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                    );
                } else if (!child->mIsColoring && child->mIsDoneColoring) {
                    child->mIsDoneColoring = 0;
                    mAnimationOrder = 1;
                }
                break;
            }
            break;
        }
    }
}