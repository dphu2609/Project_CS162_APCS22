#include <State/StaticArrayState.hpp>

void StaticArrayState::createDataStructure(std::vector<int> list) {
    for (int i = 0; i < LayerCount; i++) {
        mSceneLayers[i]->getChildren().clear();
    }
    for (int i = 0; i < 10; i++) {
        std::unique_ptr<ContainerNode> blankNode = std::make_unique<ContainerNode>(
            mWindow, sf::Vector2f(120, 120), 10, 
            sf::Vector2f(mWindow.getSize().x/2 - 645 + 130*i, 250),
            sf::Color::White, sf::Color(145, 174, 226, 255)
        );
        mSceneLayers[BlankNode]->attachChild(std::move(blankNode));
    }
    if (list.size() == 0) return;
    if (mIsReplay && mInsertActivated) {
        for (int i = mActionIndex; i < mListData.size() - 1; i++) {
            mTempListData[i] = mTempListData[i + 1];
        }
        if (!mIsInsertOnce) {
            mTempListData.pop_back();   
        }
    } else if (mIsReplay && mDeleteActivated) {
        for (int i = mListData.size() - 1; i > mActionIndex; i--) {
            mTempListData[i] = mTempListData[i - 1];
        }
        mTempListData[mActionIndex] = mActionValue;
    } else if (mIsReplay && mUpdateActivated) {
        mTempListData[mActionIndex] = list[mActionIndex];
    }
    if (mTempListData.size() == 0) {
        if (mInsertActivated || mDeleteActivated || mUpdateActivated) {
            mTempListData = list;
            mIsInsertOnce = 0;
        }
        mListData = list;
        for (int i = 0; i < list.size(); i++) {
            std::unique_ptr<DisplayNode> arrayNode = std::make_unique<DisplayNode>(
                mListData[i], mFontsHolder[Fonts::FiraSansRegular], 100, sf::Vector2f(mWindow.getSize().x/2 - 645 + 130*i, 250),
                sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
            );
            mSceneLayers[Nodes]->attachChild(std::move(arrayNode));
        }
    } else {
        mListData = list;
        for (int i = 0; i < mTempListData.size(); i++) {
            std::unique_ptr<DisplayNode> arrayNode = std::make_unique<DisplayNode>(
                mTempListData[i], mFontsHolder[Fonts::FiraSansRegular], 100, sf::Vector2f(mWindow.getSize().x/2 - 645 + 130*i, 250),
                sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
            );
            mSceneLayers[Nodes]->attachChild(std::move(arrayNode));
        }
    }
    std::unique_ptr<ContainerNode> arrayBorder = std::make_unique<ContainerNode>(
        mWindow, sf::Vector2f(120*mListData.size() + 10*(mListData.size() - 1), 120), 10, sf::Vector2f(mWindow.getSize().x/2 - 645, 250),
        sf::Color::Transparent, sf::Color(201, 16, 16, 255)
    );
    mSceneLayers[ArrayBoder]->attachChild(std::move(arrayBorder));  
}

void StaticArrayState::insertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
    (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::StaticArrayInsert])
    ) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::StaticArrayInsert], mFontsHolder[Fonts::FiraMonoRegular], 25,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::StaticArrayInsert] = 1;
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
                } else if (!child->mIsColoring && child->mIsDoneColoring) {
                    child->mIsDoneColoring = 0;
                    mAnimationOrder = 2;
                }
            }
            break;
        }
        case 2: {
            int index = 0;
            if (mListData.size() == 0) {
                std::unique_ptr<DisplayNode> arrayNode = std::make_unique<DisplayNode>(
                    mListData.back(), mFontsHolder[Fonts::FiraSansRegular], 100, sf::Vector2f(mWindow.getSize().x/2 - 645 + 130*mListData.size(), 250),
                    sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                );
                mSceneLayers[Nodes]->attachChild(std::move(arrayNode));
                mAnimationOrder = 4;
                break;
            }
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == mListData.size() - 1) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1, 2, 3});
                        int tempIndex = 0;
                        if (mTempListData.size() == mListData.size()) {
                            for (auto &blankNode : mSceneLayers[BlankNode]->getChildren()) {
                                if (tempIndex == mListData.size()) {
                                    if (!blankNode->mIsColoring && !blankNode->mIsDoneColoring) {
                                        blankNode->triggerColorAnimation(
                                            dt, speed,
                                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                                        );
                                    } else if (!blankNode->mIsColoring && blankNode->mIsDoneColoring) {
                                        blankNode->mIsDoneColoring = 0;
                                    }
                                }
                                tempIndex++;
                            }
                            std::cout << 34;
                        }
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        if (mTempListData.size() == mListData.size()) {
                            std::unique_ptr<DisplayNode> arrayNode = std::make_unique<DisplayNode>(
                                mListData.back(), mFontsHolder[Fonts::FiraSansRegular], 100, sf::Vector2f(mWindow.getSize().x/2 - 645 + 130*mListData.size(), 250),
                                sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                            );
                            mSceneLayers[Nodes]->attachChild(std::move(arrayNode));
                        }
                        if (mListData.size() == 1) mAnimationOrder = 4;
                        else mAnimationOrder = 3;
                    }
                } else if (index == mListData.size() && mTempListData.size() != mListData.size()) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                    }
                }
                index++;
            }
            break;
        }
        case 3: {
            if (mColorIndex == 0) {
                mColorIndex = mListData.size() - 1;
            }
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        child->triggerChangeContent(std::to_string(mListData[mColorIndex - 1]));
                        mColorIndex--;
                        if (mColorIndex == insertIndex) {
                            mAnimationOrder = 4;
                            mColorIndex++;
                        }
                    }
                } else if (index == mColorIndex - 1)  {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                    }
                }
                index++;    
            }
            break;
        }
        case 4: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == insertIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(31, 224, 205, 255), sf::Color(31, 224, 205, 255),
                            sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({4});
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        child->triggerChangeContent(std::to_string(insertValue));
                        mAnimationOrder = 5;
                    }
                }
                index++;
            }
            break;
        }
        case 5: {   
            for (auto &child : mSceneLayers[ArrayBoder]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed, 130, 0, 0);
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({5});
                } else if (!child->mIsScaling && child->mIsDoneScaling) {
                    child->mIsDoneScaling = 0;
                    mAnimationOrder = 6;
                }
            }
            break;
        }

        case 6: {
            if (!mIsInsertOnce && mListData.size() != mTempListData.size()) {
                mIsInsertOnce = 1;
            }
            if (!mIsEndAnimation) {
                mIsEndAnimation = 1;
                if (mTempListData.size() == mListData.size()) mTempListData.resize(mTempListData.size() + 1);
                for (int i = mListData.size() - 1; i >= insertIndex; i--) {
                    mTempListData[i + 1] = mTempListData[i];
                }
                mTempListData[insertIndex] = insertValue;
                mListData.insert(mListData.begin() + insertIndex, insertValue);
            }
        }
    }
}

void StaticArrayState::insertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue) {
    mIsEndAnimation = 0;
    switch(mAnimationOrder) {
        case 6: {
            for (int i = insertIndex; i < mListData.size() - 1; i++) {
                mTempListData[i] = mTempListData[i + 1];
            }
            if (!mIsInsertOnce) {
                mTempListData.pop_back();
            }
            mListData.erase(mListData.begin() + insertIndex);
            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({5});
            mAnimationOrder = 5;
            break;
        }
        case 5: {
            for (auto &child : mSceneLayers[ArrayBoder]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed, -130, 0, 0);
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({4});
                } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                    child->mIsDoneScaling = 0;
                    mAnimationOrder = 4;
                }
            }
            break;
        }
        case 4: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == insertIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(31, 224, 205, 255), sf::Color(31, 224, 205, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1, 2, 3});
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        child->triggerChangeContent(std::to_string(mListData[insertIndex]));
                        if (mListData.size() <= 1) mAnimationOrder = 2;
                        else mAnimationOrder = 3;
                    }
                }
                index++;
            }
            break;
        }
        case 3: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        child->triggerChangeContent(std::to_string(mListData[mColorIndex]));  
                        mColorIndex++;
                        if (mColorIndex > mListData.size() - 1) {
                            mColorIndex = mListData.size() - 1;
                            mAnimationOrder = 2;
                        } 
                        break;
                    }
                } 
                if (index == mColorIndex - 1) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                    }
                }
                index++;
            }
            break;
        }
        case 2: {
            int index = 0;
            if (mListData.size() == 0) {
                mSceneLayers[Nodes]->getChildren().clear();
                mAnimationOrder = 1;
                break;
            }
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == mListData.size() - 1) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({0});
                    } else if (!child->mIsColoring && child->mIsDoneColoring) {
                        child->mIsDoneColoring = 0;
                    }
                } else if (index == mListData.size()) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring) {
                        child->mIsDoneColoring = 0;
                        if (!mIsInsertOnce) {
                            mSceneLayers[Nodes]->getChildren().pop_back();
                        }
                        mAnimationOrder = 1;
                        break;
                    }
                }
                index++;
            }
            break;
        }   
    }
}
void StaticArrayState::deleteAnimation(sf::Time dt, double speed, int deleteIndex) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
    (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::StaticArrayDelete])
    ) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::StaticArrayDelete], mFontsHolder[Fonts::FiraMonoRegular], 25,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::StaticArrayDelete] = 1;
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
                } else if (!child->mIsColoring && child->mIsDoneColoring) {
                    child->mIsDoneColoring = 0;
                    mAnimationOrder = 2;
                }
            }
            break;
        }
        case 2: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == deleteIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255),
                            sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255)
                        );
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1, 2, 3});
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        mAnimationOrder = 3;
                    } 
                }
                index++;
            }
            break;
        }
        case 3: {
            if (mColorIndex == 0) {
                mColorIndex = deleteIndex + 1;
            }
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        mColorIndex++;
                        if (mColorIndex > mListData.size() - 1) {
                            mAnimationOrder = 4;
                            mColorIndex -= 2;
                        }
                        break;
                    }
                } else if (index == mColorIndex - 1) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        child->triggerChangeContent(std::to_string(mListData[mColorIndex]));
                    }
                }
                index++;
            }
            break;
        }
        case 4: {
            for (auto &child : mSceneLayers[ArrayBoder]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed, -130, 0, 0);
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({4});
                } else if (!child->mIsScaling && child->mIsDoneScaling) {
                    child->mIsDoneScaling = 0;
                    mAnimationOrder = 5;
                }
            }
            break;
        }
        case 5: {
            if (!mIsEndAnimation) {
                mIsEndAnimation = 1;
                for (int i = deleteIndex; i < mTempListData.size() - 1; i++) {
                    mTempListData[i] = mTempListData[i + 1];
                }
                mListData.erase(mListData.begin() + deleteIndex);
            }
            break;
        }
    }
}
void StaticArrayState::deleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue) {
    mIsEndAnimation = 0;
    switch(mAnimationOrder) {
        case 5: {
            for (int i = mTempListData.size() - 1; i > deleteIndex; i--) {
                mTempListData[i] = mTempListData[i - 1];
            }
            mListData.insert(mListData.begin() + deleteIndex, deleteValue);
            mAnimationOrder = 4;
            break;
        }
        case 4: {
            for (auto &child : mSceneLayers[ArrayBoder]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed, 130, 0, 0);
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1, 2, 3});
                } else if (!child->mIsScaling && child->mIsDoneScaling && !mIsActionPaused) {
                    child->mIsDoneScaling = 0;
                    mAnimationOrder = 3;
                }
            }
            break;
        }
        case 3: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == mColorIndex + 1) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring) {
                        child->triggerChangeContent(std::to_string(mListData[mColorIndex + 1]));
                        if (!mIsActionPaused) {
                            child->mIsDoneColoring = 0;
                            mColorIndex--;
                            if (mColorIndex < deleteIndex) {
                                mAnimationOrder = 2;
                                mColorIndex = deleteIndex + 1;
                            }
                        }
                        break;
                    }
                } else if (index == mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring) {
                        if (mColorIndex == deleteIndex) {
                            child->triggerChangeContent(std::to_string(mListData[mColorIndex]));
                        }
                        if (!mIsActionPaused) {
                            child->mIsDoneColoring = 0;
                        }
                    }
                }
                index++;
            }
            break;
        }
        case 2: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == deleteIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, 1, 
                            sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring) {
                        child->mIsDoneColoring = 0;
                        mAnimationOrder = 1;
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({0});
                    } 
                }
                index++;
            }
            break;
        }
    }
}
void StaticArrayState::updateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
    (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::StaticArrayUpdate])
    ) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::StaticArrayUpdate], mFontsHolder[Fonts::FiraMonoRegular], 25,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::StaticArrayUpdate] = 1;
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
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({0});
                } else if (!child->mIsColoring && child->mIsDoneColoring) {
                    child->mIsDoneColoring = 0;
                    mAnimationOrder = 2;
                }
            }
            break;
        }
        case 2: {
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
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
                    } else if (!child->mIsColoring && child->mIsDoneColoring) {
                        child->mIsDoneColoring = 0;
                        child->triggerChangeContent(std::to_string(updateValue));
                        mAnimationOrder = 3;
                    }
                }
                index++;
            }
            break;
        }
        case 3: {
            if (!mIsEndAnimation) {
                mIsEndAnimation = 1;
                mListData[updateIndex] = updateValue;
                mTempListData[updateIndex] = updateValue;
                mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2});
            }
            break;
        }
    }
}
void StaticArrayState::updateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue) {
    mIsEndAnimation = 0;
    switch(mAnimationOrder) {
        case 3: {
            mListData[updateIndex] = prevValue;
            mTempListData[updateIndex] = prevValue;
            mAnimationOrder = 2;
            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
            break;
        }
        case 2: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == updateIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(78, 62, 222, 255), sf::Color(78, 62, 222, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring) {
                        child->mIsDoneColoring = 0;
                        child->triggerChangeContent(std::to_string(prevValue));
                        mAnimationOrder = 1;
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({0});
                    }
                }
                index++;
            }
            break;
        }
    }
}
void StaticArrayState::searchAnimation(sf::Time dt, double speed, int searchValue) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
    (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::StaticArraySearch])
    ) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::StaticArraySearch], mFontsHolder[Fonts::FiraMonoRegular], 25,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::StaticArraySearch] = 1;
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
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        this->mColorIndex++;
                        if (std::stoi(child->getStringData()) == searchValue) {
                            this->mColorIndex--;    
                            mAnimationOrder = 3;
                        } else if (this->mColorIndex == mListData.size()) {
                            mAnimationOrder = 4;
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({6});
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
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2});
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        mAnimationOrder = 4;
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({3});
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
            break;
        }
    }
}
void StaticArrayState::searchAnimationReversed(sf::Time dt, double speed, int searchValue) {
    mIsEndAnimation = 0;
    switch(mAnimationOrder) {
        case 4: {
            if (this->mColorIndex == mListData.size()) {
                this->mColorIndex--;
                mAnimationOrder = 2;
                mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
            } 
            else {
                mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2});
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
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        mAnimationOrder = 2;
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
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
                            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({0});
                        }
                    }
                }
                index++;
            }
            break;
        }
    }
}