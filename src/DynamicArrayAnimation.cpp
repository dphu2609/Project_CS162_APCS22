#include <State/DynamicArrayState.hpp>

void DynamicArrayState::createDataStructure(SinglyLinkedList<int> &list) {
    for (int i = 0; i < LayerCount; i++) {
    mSceneLayers[i]->getChildren().clear();
    }
    if (list.size() == 0) return;
    mListData = list;
    for (int i = 0; i < list.size(); i++) {
        std::unique_ptr<DisplayNode> arrayNode = std::make_unique<DisplayNode>(
            mListData[i], mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, 
            sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - 645*Constant::scaleX + 140*i*Constant::scaleX, 250*Constant::scaleX),
            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
        );
        mSceneLayers[Nodes]->attachChild(std::move(arrayNode));
    }
}
void DynamicArrayState::insertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
    (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::DynamicArrayInsert])
    ) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::DynamicArrayInsert], mFontsHolder[Fonts::FiraMonoRegular], 25*Constant::scaleX,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::DynamicArrayInsert] = 1;
    }
    switch(mAnimationOrder) {
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
            if (mSceneLayers[BlankNode]->getChildren().size() == 0) {
                for (int i = 0; i < mListData.size() + 1; i++) {
                    std::unique_ptr<ContainerNode> blankNode = std::make_unique<ContainerNode>(
                        mWindow, sf::Vector2f(120*Constant::scaleX, 120*Constant::scaleX), 10*Constant::scaleX, 
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - 645*Constant::scaleX + 140*i*Constant::scaleX, 625*Constant::scaleX),
                        sf::Color::White, sf::Color(145, 174, 226, 255)
                    );
                    mSceneLayers[BlankNode]->attachChild(std::move(blankNode));
                    mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                    mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
                }
            }
            if (!mIsActionPaused) {
                mAnimationOrder = 3;
            }
            break;
        }
        case 3: {
            if (insertIndex == 0) {
                mAnimationOrder = 4;
                break;
            }
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2, 3, 4});
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[BlankNode]->getChildren()) {
                if (index == mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring) {
                        if (mColorIndex == mSceneLayers[NewArray]->getChildren().size()) {
                            std::unique_ptr<DisplayNode> arrayNode = std::make_unique<DisplayNode>(
                                mListData[index], mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, 
                                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - 645*Constant::scaleX + 140*index*Constant::scaleX, 625*Constant::scaleX),
                                sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                            );
                            mSceneLayers[NewArray]->attachChild(std::move(arrayNode));
                        }
                        if (!mIsActionPaused) {
                            child->mIsDoneColoring = 0;
                            mColorIndex++;
                            if (mColorIndex >= insertIndex) {
                                mAnimationOrder = 4;
                            }
                            break;
                        }
                    }
                }
                index++;
            }
            break;
        }
        case 4: {
            int index = 0;
            for (auto &child : mSceneLayers[BlankNode]->getChildren()) {
                if (index == mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White,sf::Color(31, 224, 205, 255), sf::Color(31, 224, 205, 255),
                            sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
                        );
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({5});
                    } else if (!child->mIsColoring && child->mIsDoneColoring) {
                        if (mColorIndex == mSceneLayers[NewArray]->getChildren().size()) {
                            std::unique_ptr<DisplayNode> arrayNode = std::make_unique<DisplayNode>(
                                insertValue, mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, 
                                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - 645*Constant::scaleX + 140*index*Constant::scaleX, 625*Constant::scaleX),
                                sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
                            );
                            mSceneLayers[NewArray]->attachChild(std::move(arrayNode));
                        }
                        if (!mIsActionPaused) {
                            child->mIsDoneColoring = 0;
                            mColorIndex++;
                            mAnimationOrder = 5;
                            break;
                        }
                    }
                }
                index++;
            }
            break;
        }
        case 5: {
            if (insertIndex == mListData.size()) {
                mSceneLayers[BlankNode]->getChildren().clear();
                mAnimationOrder = 6;
                break;
            }
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == mColorIndex - 1) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({6, 7, 8});
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[BlankNode]->getChildren()) {
                if (index == mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring) {
                        if (mColorIndex == mSceneLayers[NewArray]->getChildren().size()) {
                            std::unique_ptr<DisplayNode> arrayNode = std::make_unique<DisplayNode>(
                                mListData[index - 1], mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, 
                                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - 645*Constant::scaleX + 140*index*Constant::scaleX, 625*Constant::scaleX),
                                sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                            );
                            mSceneLayers[NewArray]->attachChild(std::move(arrayNode));
                        }
                        if (!mIsActionPaused) {
                            child->mIsDoneColoring = 0;
                            mColorIndex++;
                            if (mColorIndex >= mListData.size() + 1) {
                                mAnimationOrder = 6;
                                mSceneLayers[BlankNode]->getChildren().clear();
                                mColorIndex--;
                            }
                            break;
                        }
                    }
                }
                index++;
            }
            break;
        }
        case 6: {
            if (mSceneLayers[Nodes]->getChildren().size() > 0) {
                mSceneLayers[Nodes]->getChildren().clear();
                mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({10, 11});
            }
            if (!mIsActionPaused) {
                mAnimationOrder = 7;
            }
            break;
        }
        case 7: {
            for (auto &child : mSceneLayers[NewArray]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 375*Constant::scaleX, -90);
                } else if (!child->mIsMoving && child->mIsDoneMoving) {
                    child->mIsDoneMoving = 0;
                    mAnimationOrder = 8;
                }
            }
            break;
        }
        case 8: {
            if (!mIsEndAnimation) {
                mListData.insert(mListData.begin() + insertIndex, insertValue);
                mSceneLayers[Nodes]->getChildren() = std::move(mSceneLayers[NewArray]->getChildren());
                mSceneLayers[NewArray]->getChildren().clear();
                mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({12});
                mIsEndAnimation = 1;
            }
            break;
        }
    }
}
void DynamicArrayState::insertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue) {
    mIsEndAnimation = 0;
    switch(mAnimationOrder) {
        case 8: {
            mSceneLayers[NewArray]->getChildren() = std::move(mSceneLayers[Nodes]->getChildren());
            mSceneLayers[Nodes]->getChildren().clear();
            mListData.erase(mListData.begin() + insertIndex);
            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({10, 11});
            mAnimationOrder = 7;
            break;
        }
        case 7: {
            for (auto &child : mSceneLayers[NewArray]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 375*Constant::scaleX, 90);
                } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                    child->mIsDoneMoving = 0;
                    mAnimationOrder = 6;
                }   
            }
            break;
        }
        case 6: {
            if (mSceneLayers[Nodes]->getChildren().size() == 0) {
                for (int i = 0; i < mListData.size(); i++) {
                    std::unique_ptr<DisplayNode> arrayNode = std::make_unique<DisplayNode>(
                        mListData[i], mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, 
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - 645*Constant::scaleX + 140*i*Constant::scaleX, 250*Constant::scaleX),
                        sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                    );
                    mSceneLayers[Nodes]->attachChild(std::move(arrayNode));
                }
            }
            if (mSceneLayers[BlankNode]->getChildren().size() == 0) {
                for (int i = 0; i < mListData.size() + 1; i++) {
                    std::unique_ptr<ContainerNode> blankNode = std::make_unique<ContainerNode>(
                        mWindow, sf::Vector2f(120*Constant::scaleX, 120*Constant::scaleX), 10*Constant::scaleX, 
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - 645*Constant::scaleX + 140*i*Constant::scaleX, 625*Constant::scaleX),
                        sf::Color::White, sf::Color(237, 139, 26, 255)
                    );
                    mSceneLayers[BlankNode]->attachChild(std::move(blankNode));
                }
                mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({6, 7, 8});
            }
            if (!mIsActionPaused) {
                if (insertIndex == mListData.size()) {
                    mAnimationOrder = 4;
                } 
                else mAnimationOrder = 5;
            }
            break;
        }
        case 5: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == mColorIndex - 1) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({6, 7, 8});
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[BlankNode]->getChildren()) {
                if (index == mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        mSceneLayers[NewArray]->getChildren().pop_back();
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        mColorIndex--;
                        if (mColorIndex <= insertIndex) {
                            mAnimationOrder = 4;
                        }
                    }
                }
                index++;
            }
            break;
        }
        case 4: {
            if (insertIndex == 0) {
                mAnimationOrder = 2;
                break;
            }
            int index = 0;
            for (auto &child : mSceneLayers[BlankNode]->getChildren()) {
                if (index == mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        mSceneLayers[NewArray]->getChildren().pop_back();
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(31, 224, 205, 255), sf::Color(31, 224, 205, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({5});
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        mColorIndex--;
                        mAnimationOrder = 3;
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
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2, 3, 4});
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[BlankNode]->getChildren()) {
                if (index == mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        mSceneLayers[NewArray]->getChildren().pop_back();
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        mColorIndex--;
                        if (mColorIndex < 0) {
                            mColorIndex = 0;
                            mAnimationOrder = 2;
                        }
                    }
                }
                index++;
            }
            break;
        }
        case 2: {
            mSceneLayers[BlankNode]->getChildren().clear();
            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
            mAnimationOrder = 1;
            break;
        }
    }
}
void DynamicArrayState::deleteAnimation(sf::Time dt, double speed, int deleteIndex) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
    (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::DynamicArrayDelete])
    ) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::DynamicArrayDelete], mFontsHolder[Fonts::FiraMonoRegular], 25*Constant::scaleX,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::DynamicArrayDelete] = 1;
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
            if (mSceneLayers[BlankNode]->getChildren().size() == 0) {
                for (int i = 0; i < mListData.size() - 1; i++) {
                    std::unique_ptr<ContainerNode> blankNode = std::make_unique<ContainerNode>(
                        mWindow, sf::Vector2f(120*Constant::scaleX, 120*Constant::scaleX), 10*Constant::scaleX, 
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - 645*Constant::scaleX + 140*i*Constant::scaleX, 625*Constant::scaleX),
                        sf::Color::White, sf::Color(145, 174, 226, 255)
                    );
                    mSceneLayers[BlankNode]->attachChild(std::move(blankNode));
                }
                mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
            }
            if (!mIsActionPaused) {
                mAnimationOrder = 3;
            }
            break;
        }
        case 3: {
            if (deleteIndex == 0) {
                mAnimationOrder = 4;
                break;
            }
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2, 3, 4});
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[BlankNode]->getChildren()) {
                if (index == mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring) {
                        if (mColorIndex == mSceneLayers[NewArray]->getChildren().size()) {
                            std::unique_ptr<DisplayNode> arrayNode = std::make_unique<DisplayNode>(
                                mListData[index], mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, 
                                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - 645*Constant::scaleX + 140*index*Constant::scaleX, 625*Constant::scaleX),
                                sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                            );
                            mSceneLayers[NewArray]->attachChild(std::move(arrayNode));
                        }
                        if (!mIsActionPaused) {
                            child->mIsDoneColoring = 0;
                            mColorIndex++;
                            if (mColorIndex >= deleteIndex) {
                                mAnimationOrder = 4;
                            }
                            break;
                        }
                    }
                }
                index++;
            }
            break;
        }
        case 4: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255),
                            sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        mColorIndex++;
                        child->mIsDoneColoring = 0;
                        mAnimationOrder = 5;
                        break;
                    }
                }
                index++;
            }
            break;
        }
        case 5: {
            if (deleteIndex == mListData.size() - 1) {
                mSceneLayers[BlankNode]->getChildren().clear();
                mAnimationOrder = 6;
                break;
            }
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({5, 6, 7});
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[BlankNode]->getChildren()) {
                if (index == mColorIndex - 1) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring) {
                        if (mColorIndex == mSceneLayers[NewArray]->getChildren().size() + 1) {
                            std::unique_ptr<DisplayNode> arrayNode = std::make_unique<DisplayNode>(
                                mListData[index + 1], mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, 
                                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - 645*Constant::scaleX + 140*index*Constant::scaleX, 625*Constant::scaleX),
                                sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                            );
                            mSceneLayers[NewArray]->attachChild(std::move(arrayNode));
                        }
                        if (!mIsActionPaused) {
                            child->mIsDoneColoring = 0;
                            mColorIndex++;
                            if (mColorIndex >= mListData.size()) {
                                mAnimationOrder = 6;
                                mSceneLayers[BlankNode]->getChildren().clear();
                                mColorIndex--;
                            }
                            break;
                        }
                    }
                }
                index++;
            }
            break;
        }
        case 6: {
            if (mSceneLayers[Nodes]->getChildren().size() > 0) {
                mSceneLayers[Nodes]->getChildren().clear();
                mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({8, 9, 10});
            }
            if (!mIsActionPaused) {
                mAnimationOrder = 7;
            }
            break;
        }
        case 7: {
            for (auto &child : mSceneLayers[NewArray]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 375*Constant::scaleX, -90);
                } else if (!child->mIsMoving && child->mIsDoneMoving) {
                    child->mIsDoneMoving = 0;
                    mAnimationOrder = 8;
                }
            }
            break;
        }
        case 8: {
            if (!mIsEndAnimation) {
                mListData.erase(mListData.begin() + deleteIndex);
                mSceneLayers[Nodes]->getChildren() = std::move(mSceneLayers[NewArray]->getChildren());
                mSceneLayers[NewArray]->getChildren().clear();
                mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({11});
                mIsEndAnimation = 1;
            }
            break;
        }
    }
}
void DynamicArrayState::deleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue) {
    mIsEndAnimation = 0;
    switch(mAnimationOrder) {
        case 8: {
            mSceneLayers[NewArray]->getChildren() = std::move(mSceneLayers[Nodes]->getChildren());
            mSceneLayers[Nodes]->getChildren().clear();
            mListData.insert(mListData.begin() + deleteIndex, deleteValue);
            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({8, 9, 10});
            mAnimationOrder = 7;
            break;
        }
        case 7: {
            for (auto &child : mSceneLayers[NewArray]->getChildren()) {
                if (!child->mIsMoving && !child->mIsDoneMoving) {
                    child->triggerMoveAnimation(dt, speed, 375*Constant::scaleX, 90);
                } else if (!child->mIsMoving && child->mIsDoneMoving && !mIsActionPaused) {
                    child->mIsDoneMoving = 0;
                    mAnimationOrder = 6;
                }
            }
            break;
        }
        case 6: {
            if (mSceneLayers[Nodes]->getChildren().size() == 0) {
                for (int i = 0; i < mListData.size(); i++) {
                    std::unique_ptr<DisplayNode> arrayNode = std::make_unique<DisplayNode>(
                        mListData[i], mFontsHolder[Fonts::FiraSansRegular], 100*Constant::scaleX, 
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - 645*Constant::scaleX + 140*i*Constant::scaleX, 250*Constant::scaleX),
                        sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                    );
                    mSceneLayers[Nodes]->attachChild(std::move(arrayNode));
                }
                mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({5, 6, 7});
            }
            if (mSceneLayers[BlankNode]->getChildren().size() == 0) {
                for (int i = 0; i < mListData.size() - 1; i++) {
                    std::unique_ptr<ContainerNode> blankNode = std::make_unique<ContainerNode>(
                        mWindow, sf::Vector2f(120*Constant::scaleX, 120*Constant::scaleX), 10*Constant::scaleX, 
                        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - 645*Constant::scaleX + 140*i*Constant::scaleX, 625*Constant::scaleX),
                        sf::Color::White, sf::Color(145, 174, 226, 255)
                    );
                    mSceneLayers[BlankNode]->attachChild(std::move(blankNode));
                }
            }
            if (!mIsActionPaused) {
                if (deleteIndex == mListData.size() - 1) {
                    mAnimationOrder = 4;
                } 
                else mAnimationOrder = 5;
            }
            break;
        }
        case 5: {
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
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[BlankNode]->getChildren()) {
                if (index == mColorIndex - 1) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        mSceneLayers[NewArray]->getChildren().pop_back();
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        mColorIndex--;
                        if (mColorIndex <= deleteIndex) {
                            mAnimationOrder = 4;
                        }   
                    }
                }
                index++;
            }
            break;
        }
        case 4: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(150, 0, 25, 255), sf::Color(150, 0, 25, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        mColorIndex--;
                        child->mIsDoneColoring = 0;
                        mAnimationOrder = 3;
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
                        mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                        mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2, 3, 4});
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                    }
                }
                index++;
            }
            index = 0;
            for (auto &child : mSceneLayers[BlankNode]->getChildren()) {
                if (index == mColorIndex) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        mSceneLayers[NewArray]->getChildren().pop_back();
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        child->mIsDoneColoring = 0;
                        mColorIndex--;
                        if (mColorIndex < 0) {
                            mColorIndex = 0;
                            mAnimationOrder = 2;
                        }
                    }
                }
                index++;
            }
            break;
        }
        case 2: {
            mSceneLayers[BlankNode]->getChildren().clear();
            mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
            mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({1});
            mAnimationOrder = 1;
            break;
        }
    }
}
void DynamicArrayState::updateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
    (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::DynamicArrayUpdate])
    ) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::DynamicArrayUpdate], mFontsHolder[Fonts::FiraMonoRegular], 25*Constant::scaleX,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::DynamicArrayUpdate] = 1;
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
                mSceneLayers[CodeBox]->getChildren()[0]->resetCodeBoxColor();
                mSceneLayers[CodeBox]->getChildren()[0]->changeCodeBoxColor({2});
            }
            break;
        }
    }
}
void DynamicArrayState::updateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue) {
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
void DynamicArrayState::searchAnimation(sf::Time dt, double speed, int searchValue) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || 
    (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::DynamicArraySearch])
    ) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::DynamicArraySearch], mFontsHolder[Fonts::FiraMonoRegular], 25*Constant::scaleX,
            sf::Color::Black, sf::Color(145, 174, 226, 255), sf::Color::Black, sf::Color(86, 114, 163, 255)
        );
        mSceneLayers[CodeBox]->attachChild(std::move(codeBlock));
        for (int i = 0; i < mCodeHolder.mStateActivated.size(); i++) {
            mCodeHolder.mStateActivated[i] = 0;
        }
        mCodeHolder.mStateActivated[Code::DynamicArraySearch] = 1;
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
void DynamicArrayState::searchAnimationReversed(sf::Time dt, double speed, int searchValue) {
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