#include <State/StackState.hpp>

void StackState::createDataStructure(std::vector<int> list) {
    for (int i = 0; i < LayerCount; i++) {
        mSceneLayers[i]->getChildren().clear();
    }
    if (list.size() == 0) return;
    mListData = list;
    for (int i = 0; i < mListData.size(); i++) {
        if (i == 0) {
            std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
                mListData[i], mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, "top", 50*Constant::scaleX,
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + i*250*Constant::scaleX, 250*Constant::scaleX), 
                sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
            );
            mSceneLayers[Nodes]->attachChild(std::move(newNode));
        }
        else {
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
            sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + i*250*Constant::scaleX + 130*Constant::scaleX, 285*Constant::scaleX), 0
        );
        mSceneLayers[Arrow]->attachChild(std::move(newArrow));
    }
}

void StackState::insertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue) {
    insertIndex = 0;
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
        (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::StackPush])
    ) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::StackPush], mFontsHolder[Fonts::FiraMonoRegular], 25*Constant::scaleX,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::StackPush] = 1;
    }
    switch (mAnimationOrder) {  
        case 1: {
            if (mListData.size() == 0) {
                mAnimationOrder = 2;
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
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({0});
                } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                    child->mIsDoneColoring = 0;
                    mAnimationOrder = 2;
                }
            }
            break;
        }
        case 2: {
            if (mSceneLayers[NewNode]->getChildren().size() == 0) {
                if (mListData.size() == 0) {
                    std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                        insertValue, mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, "newNode", 50*Constant::scaleX,
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (insertIndex)*250*Constant::scaleX, 500*Constant::scaleX), 
                        sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
                    );
                    mSceneLayers[NewNode]->attachChild(std::move(addedNode));
                    mAnimationOrder = 4;
                    break;
                } else {
                    std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                        insertValue, mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX,
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (insertIndex)*250*Constant::scaleX, 750*Constant::scaleX), 
                        sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
                    );
                    mSceneLayers[NewNode]->attachChild(std::move(addedNode));
                }
            }
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, -90);
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});

                } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                    child->mIsDoneMoving = 0;
                    mAnimationOrder = 3;
                }
            }
            break;
        }
        case 3: {
            if (mSceneLayers[NewArrow]->getChildren().size() == 0) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 50*Constant::scaleX), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (insertIndex)*250*Constant::scaleX + 35*Constant::scaleX, 490*Constant::scaleX), -90
                );
                mSceneLayers[NewArrow]->attachChild(std::move(newArrow));
            }
            for (auto &child : this->mSceneLayers[NewArrow]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed, 110*Constant::scaleX, 0, 0);
                } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                    child->mIsDoneScaling = 0;
                    mAnimationOrder = 4;
                }
            }
            break;
        }
        case 4: {
            int index = 0;
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
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, -90);
                } else if (!child->mIsMoving && child->mIsDoneMoving) {
                    child->mIsDoneMoving = 0;
                    mAnimationOrder = 5;
                }
            }
            for (auto &child : this->mSceneLayers[NewArrow]->getChildren()) {
                if (!child->mIsRotating && !child->mIsDoneRotating) {
                    child->triggerRotateAnimation(dt, speed, 90);
                    child->triggerMoveAnimation(dt, speed, 225.05318547*Constant::scaleX, -66.16125981683);
                } else if (!child->mIsRotating && child->mIsDoneRotating) {
                    child->mIsDoneRotating = 0;
                }
            }
            break;
        }
        case 5: {
            std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                insertValue, mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX,
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (insertIndex)*250*Constant::scaleX, 250*Constant::scaleX), 
                sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
            );

            mSceneLayers[Nodes]->getChildren().insert(mSceneLayers[Nodes]->getChildren().begin() + insertIndex, std::move(addedNode));
            if (mListData.size() > 0) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(110*Constant::scaleX, 50*Constant::scaleX), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + insertIndex*250*Constant::scaleX + 130*Constant::scaleX, 285*Constant::scaleX), 0
                );
                mSceneLayers[Arrow]->getChildren().insert(mSceneLayers[Arrow]->getChildren().begin() + insertIndex, std::move(newArrow)); 
            }

            mListData.insert(mListData.begin() + insertIndex, insertValue);

            mSceneLayers[NewArrow]->getChildren().clear();
            mSceneLayers[NewNode]->getChildren().clear();

            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2});
            
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == 0) child->setLabel("top");
                else if (index == 1) {
                    child->setLabel("");
                    break;
                }
                index++;
            }

            mAnimationOrder = 6;
            break;
        }
        case 6: {
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
            }
            else {
                mIsEndAnimation = 1;
            }
        }
    }
}

void StackState::insertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue) {
    insertIndex = 0;
    mIsEndAnimation = 0;
    switch(mAnimationOrder) {
        case 6: {
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
                        mAnimationOrder = 5;
                    }
                }
            }
            else mAnimationOrder = 5;
            break;
        }
        case 5: {
            mSceneLayers[Nodes]->getChildren().erase(mSceneLayers[Nodes]->getChildren().begin() + insertIndex);
            if (mListData.size() > 1) 
                mSceneLayers[Arrow]->getChildren().erase(mSceneLayers[Arrow]->getChildren().begin() + insertIndex); 

            mListData.erase(mListData.begin() + insertIndex);

            std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                insertValue, mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, "newNode", 50*Constant::scaleX,
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (insertIndex)*250*Constant::scaleX, 250*Constant::scaleX), 
                sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
            );
            mSceneLayers[NewNode]->attachChild(std::move(addedNode));

            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});

            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                child->setLabel("top");
                break;
            }

            if (mListData.size() != 0) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(110*Constant::scaleX, 50*Constant::scaleX), 
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + insertIndex*250*Constant::scaleX + 130*Constant::scaleX, 285*Constant::scaleX), 0
                );
                mSceneLayers[NewArrow]->attachChild(std::move(newArrow));
            }
            if (mListData.size() == 0) mAnimationOrder = 2;
            else mAnimationOrder = 4;
            break;
        }
        case 4: {
            int index = 0;
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
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 90);
                } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                    child->mIsDoneMoving = 0;
                    mAnimationOrder = 3;
                }
            }
            for (auto &child : this->mSceneLayers[NewArrow]->getChildren()) {
                if (!child->mIsRotating && !child->mIsDoneRotating) {
                    child->triggerRotateAnimation(dt, speed, -90);
                    child->triggerMoveAnimation(dt, speed, 225.05318547*Constant::scaleX, -66.16125981683 + 180);
                } else if (!child->mIsRotating && child->mIsDoneRotating && !mIsActionPaused) {
                    child->mIsDoneRotating = 0;
                }
            }
            break;
        }
        case 3: {
            for (auto &child : this->mSceneLayers[NewArrow]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed, -110*Constant::scaleX, 0, 0);
                } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                    child->mIsDoneScaling = 0;
                    mAnimationOrder = 2;
                    this->mSceneLayers[NewArrow]->getChildren().clear();
                }
            }
            break;
        }
        case 2: {
            for (auto &child : this->mSceneLayers[NewNode]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 90);
                } else if (!child->mIsMoving && child->mIsDoneMoving) {
                    if (mSceneLayers[NewNode]->getChildren().size() != 0) 
                        mSceneLayers[NewNode]->getChildren().clear();
                    mAnimationOrder = 1;
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({0});
                }
            }
            break;
        }
    }
}

void StackState::deleteAnimation(sf::Time dt, double speed, int deleteIndex) {
    deleteIndex = 0;
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
    (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::StackPop])
    ) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::StackPop], mFontsHolder[Fonts::FiraMonoRegular], 25*Constant::scaleX,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::StackPop] = 1;
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
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({0});
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
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1, 2});
                } else if (!child->mIsColoring && child->mIsDoneColoring) {
                    child->mIsDoneColoring = 0;
                    mAnimationOrder = 3;
                }
                break;
            }
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == 0) child->setLabel("temp");
                else if (index == 1) {
                    child->setLabel("top");
                    break;
                }
                index++;
            }
            break;
        }
        case 3: {
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed*1.5, -100*Constant::scaleX, 0, 0);
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({3});
                } else if (!child->mIsScaling && child->mIsDoneScaling) {
                    mAnimationOrder = 4;
                }
                break;
            }
            for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed*2, -110*Constant::scaleX, speed, -50*Constant::scaleX);
                    child->triggerMoveAnimation(dt, speed*2, 30*Constant::scaleX, 45);
                }
                break;
            }
            break;
        }
        case 4: {
            if (mListData.size()%2 != 0 && mListData.size() != 1) {
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index > 0) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
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
                            child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 180);
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
                mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({4});
                mIsEndAnimation = 1;
            }
            break;
        }
    }
}

void StackState::deleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue) {
    deleteIndex = 0;
    mIsEndAnimation = 0;
    switch (mAnimationOrder) {
        case 5: {
            mListData.insert(mListData.begin() + deleteIndex, deleteValue);
            std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
                deleteValue, mFontsHolder[Fonts::FiraSansRegular], 0, "temp", 0,
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + (deleteIndex)*250*Constant::scaleX + 60*Constant::scaleX, 310*Constant::scaleX), 
                sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255)
            );
            mSceneLayers[Nodes]->getChildren().insert(mSceneLayers[Nodes]->getChildren().begin() + deleteIndex, std::move(newNode));
            if (mListData.size() != 1) {
                std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                    mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 0),  
                    sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (mListData.size()/2)*250*Constant::scaleX + deleteIndex*250*Constant::scaleX + 130*Constant::scaleX + 22*Constant::scaleX, 305*Constant::scaleX), 0
                );
                mSceneLayers[Arrow]->getChildren().insert(mSceneLayers[Arrow]->getChildren().begin() + deleteIndex, std::move(newArrow));
            }
            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({3});
            mAnimationOrder = 4;
            break;
        }
        case 4: {
            if (mListData.size()%2 != 0 && mListData.size() != 1) {
                int index = 0;
                for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                    if (index > 0) {
                        if (!child->mIsMoving && !child->mIsDoneMoving) {
                            child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
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
                            child->triggerMoveAnimation(dt, speed, 250*Constant::scaleX, 0);
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
                    child->triggerScaleAnimation(dt, speed*1.5, 100*Constant::scaleX, 0, 0);
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1, 2});       
                } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                    mAnimationOrder = 2;
                }
                break;
            }
            for (auto &child : mSceneLayers[Arrow]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed*2, 110*Constant::scaleX, speed, 50);
                    child->triggerMoveAnimation(dt, speed*2, 30*Constant::scaleX, 45 - 180);
                }
                break;
            }
            break;
        }
        case 2: {
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (!child->mIsColoring && !child->mIsDoneColoring) {
                    child->triggerColorAnimation(
                        dt, speed, 
                        sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255),
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                    );
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({0});      
                } else if (!child->mIsColoring && child->mIsDoneColoring) {
                    child->mIsDoneColoring = 0;
                    mAnimationOrder = 1;
                }
                break;
            }
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == 0) {
                    child->setLabel("top");
                }
                else if (index == 1) {
                    child->setLabel("");
                    break;
                }
                index++;
            }
            break;
        }
    }
}