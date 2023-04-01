#include <State/SinglyLinkedListState.hpp>

void LinkedListState::createStaticArray(std::vector<int> list) {
    for (int i = 0; i < LayerCount; i++) {
        mSceneLayers[i]->getChildren().clear();
    }
    for (int i = 0; i < 10; i++) {
        std::unique_ptr<ContainerNode> blankNode = std::make_unique<ContainerNode>(
            mWindow, sf::Vector2f(120, 120), 10, sf::Vector2f(mWindow.getSize().x/2 - 645 + 130*i, 250),
            sf::Color::White, sf::Color(145, 174, 226, 255)
        );
        mSceneLayers[BlankNode]->attachChild(std::move(blankNode));
    }
    if (list.size() == 0) return;
    if (mIsReplay) {
        for (int i = mActionIndex; i < mListData.size() - 1; i++) {
            mTempListData[i] = mTempListData[i + 1];
        }
        mTempListData.pop_back();
    }
    if (mTempListData.size() == 0) {
        if (mInsertActivated) mTempListData = list;
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

void LinkedListState::staticArrayInsertAnimation(sf::Time dt, double speed, int insertIndex, int insertData) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::SinglyLinkedListInsert])) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::StaticArrayInsert], mFontsHolder[Fonts::FiraMonoRegular], 25,
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
                        dt, 1, 
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255),
                        sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                    );
                    // mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    // mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({7});
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
                        int tempIndex = 0;
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
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        std::unique_ptr<DisplayNode> arrayNode = std::make_unique<DisplayNode>(
                            mListData.back(), mFontsHolder[Fonts::FiraSansRegular], 100, sf::Vector2f(mWindow.getSize().x/2 - 645 + 130*mListData.size(), 250),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                        mSceneLayers[Nodes]->attachChild(std::move(arrayNode));
                        if (mListData.size() == 1) mAnimationOrder = 4;
                        else mAnimationOrder = 3;
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
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        child->triggerChangeContent(std::to_string(insertData));
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
                } else if (!child->mIsScaling && child->mIsDoneScaling) {
                    child->mIsDoneScaling = 0;
                    mAnimationOrder = 6;
                }
            }
            break;
        }

        case 6: {
            if (!mIsEndAnimation) {
                mIsEndAnimation = 1;
                if (mTempListData.size() == mListData.size()) mTempListData.resize(mTempListData.size() + 1);
                for (int i = mListData.size() - 1; i > insertIndex; i--) {
                    mTempListData[i + 1] = mTempListData[i];
                }
                mTempListData[insertIndex] = insertData;
                mListData.insert(mListData.begin() + insertIndex, insertData);
            }
        }
    }
}

void LinkedListState::staticArrayInsertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertData) {
    mIsEndAnimation = 0;
    switch(mAnimationOrder) {
        case 6: {
            for (int i = insertIndex; i < mListData.size() - 1; i++) {
                mTempListData[i] = mTempListData[i + 1];
            }
            mListData.erase(mListData.begin() + insertIndex);
            mAnimationOrder = 5;
            break;
        }
        case 5: {
            for (auto &child : mSceneLayers[ArrayBoder]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed, -130, 0, 0);
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
                        mSceneLayers[Nodes]->getChildren().pop_back();
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
void LinkedListState::staticArrayDeleteAnimation(sf::Time dt, double speed, int deleteIndex) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::SinglyLinkedListInsert])) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::StaticArrayDelete], mFontsHolder[Fonts::FiraMonoRegular], 25,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::SinglyLinkedListInsert] = 1;
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
                            dt, 1, 
                            sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255),
                            sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255)
                        );
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
                        if (mColorIndex >= mListData.size() - 1) {
                            mAnimationOrder = 4;
                        }
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
void LinkedListState::staticArrayDeleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue) {
    mIsEndAnimation = 0;
    switch(mAnimationOrder) {
        case 4: {
            mListData.insert(mListData.begin() + deleteIndex, deleteValue);
            mAnimationOrder = 3;
            break;
        }
        case 3: {
            for (auto &child : mSceneLayers[ArrayBoder]->getChildren()) {
                if (!child->mIsScaling && !child->mIsDoneScaling) {
                    child->triggerScaleAnimation(dt, speed, 130, 0, 0);
                } else if (!child->mIsScaling && child->mIsDoneScaling) {
                    child->mIsDoneScaling = 0;
                    mAnimationOrder = 2;
                }
            }
            break;
        }
        case 2: {
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
                        if (mColorIndex <= deleteIndex) {
                            mAnimationOrder = 1;
                        }
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
                    }
                }
                index++;
            }
        }
    }
}
void LinkedListState::staticArrayUpdateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::SinglyLinkedListInsert])) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::StaticArrayUpdate], mFontsHolder[Fonts::FiraMonoRegular], 25,
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
                        dt, 1, 
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
                        mAnimationOrder = 2;
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
            }
            break;
        }
    }
}
void LinkedListState::staticArrayUpdateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue) {
    mIsEndAnimation = 0;
    switch(mAnimationOrder) {
        case 3: {
            mListData[updateIndex] = prevValue;
            mAnimationOrder = 2;
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
                    }
                }
                index++;
            }
            break;
        }
    }
}
void LinkedListState::staticArraySearchAnimation(sf::Time dt, double speed, int searchValue) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::SinglyLinkedListInsert])) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::StaticArraySearch], mFontsHolder[Fonts::FiraMonoRegular], 25,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::SinglyLinkedListInsert] = 1;
    }
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
            break;
        }
     }
}
void LinkedListState::staticArraySearchAnimationReversed(sf::Time dt, double speed, int searchValue) {
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