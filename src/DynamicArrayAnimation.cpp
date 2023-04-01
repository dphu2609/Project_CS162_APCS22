#include <State/SinglyLinkedListState.hpp>

void LinkedListState::createDynamicArray(std::vector<int> list) {
    for (int i = 0; i < LayerCount; i++) {
    mSceneLayers[i]->getChildren().clear();
    }
    if (list.size() == 0) return;
    mListData = list;
    for (int i = 0; i < list.size(); i++) {
        std::unique_ptr<DisplayNode> arrayNode = std::make_unique<DisplayNode>(
            mListData[i], mFontsHolder[Fonts::FiraSansRegular], 100, sf::Vector2f(mWindow.getSize().x/2 - 645 + 130*i, 250),
            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
        );
        mSceneLayers[Nodes]->attachChild(std::move(arrayNode));
    }
}
void LinkedListState::dynamicArrayInsertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue) {
    if (mSceneLayers[CodeBox]->getChildren().size() == 0 || (mSceneLayers[CodeBox]->getChildren().size() == 1 && !mCodeHolder.mStateActivated[Code::SinglyLinkedListInsert])) {
        mSceneLayers[CodeBox]->getChildren().clear();
        std::unique_ptr<CodeBlockNode> codeBlock = std::make_unique<CodeBlockNode>(
            mWindow, mCodeHolder[Code::DynamicArrayInsert], mFontsHolder[Fonts::FiraMonoRegular], 25,
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
            if (mListData.size() == 0) {
                mAnimationOrder = 2;
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
            if (mSceneLayers[BlankNode]->getChildren().size() == 0) {
                for (int i = 0; i < mListData.size() + 1; i++) {
                    std::unique_ptr<ContainerNode> blankNode = std::make_unique<ContainerNode>(
                        mWindow, sf::Vector2f(120, 120), 10, sf::Vector2f(mWindow.getSize().x/2 - 645 + 130*i, 625),
                        sf::Color::White, sf::Color(145, 174, 226, 255)
                    );
                    mSceneLayers[BlankNode]->attachChild(std::move(blankNode));
                }
            }
            if (!mIsActionPaused) {
                mAnimationOrder = 3;
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
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
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
                                mListData[index], mFontsHolder[Fonts::FiraSansRegular], 100, sf::Vector2f(mWindow.getSize().x/2 - 645 + 130*i, 250),
                                sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                            );
                            mSceneLayers[NewArray]->attachChild(std::move(arrayNode));
                        }
                        if (!mIsActionPaused) {
                            child->mIsDoneColoring = 0;
                            mColorIndex++;
                            if (mColorIndex >= insertIndex) {
                                mAnimationOrder = 4;
                            }
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
                            sf::Color::White,sf::Color(31, 224, 205, 255), sf::Color(145, 174, 226, 255),
                            sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
                        );
                    } else if (!child->mIsColoring && child->mIsDoneColoring && !mIsActionPaused) {
                        if (mColorIndex == mSceneLayers[NewArray]->getChildren().size()) {
                            std::unique_ptr<DisplayNode> arrayNode = std::make_unique<DisplayNode>(
                                mListData[index], mFontsHolder[Fonts::FiraSansRegular], 100, sf::Vector2f(mWindow.getSize().x/2 - 645 + 130*i, 250),
                                sf::Color(31, 224, 205, 255), sf::Color::White, sf::Color(31, 224, 205, 255)
                            );
                            mSceneLayers[NewArray]->attachChild(std::move(arrayNode));
                        }
                        if (!mIsActionPaused) {
                            child->mIsDoneColoring = 0;
                            mColorIndex++;
                            mAnimationOrder = 5;
                        }
                    }
                }
                index++;
            }
        }
        case 5: {
            int index = 0;
            for (auto &child : mSceneLayers[Nodes]->getChildren()) {
                if (index == mColorIndex - 1) {
                    if (!child->mIsColoring && !child->mIsDoneColoring) {
                        child->triggerColorAnimation(
                            dt, speed, 
                            sf::Color::White, sf::Color(237, 139, 26, 255), sf::Color(237, 139, 26, 255),
                            sf::Color(237, 139, 26, 255), sf::Color::White, sf::Color(237, 139, 26, 255)
                        );
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
                                mListData[index], mFontsHolder[Fonts::FiraSansRegular], 100, sf::Vector2f(mWindow.getSize().x/2 - 645 + 130*i, 250),
                                sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
                            );
                            mSceneLayers[NewArray]->attachChild(std::move(arrayNode));
                        }
                        if (!mIsActionPaused) {
                            child->mIsDoneColoring = 0;
                            mColorIndex++;
                            if (mColorIndex >= mListData.size() + 1) {
                                mAnimationOrder = 6;
                            }
                        }
                    }
                }
                index++;
            }
            break;
        }
    }
}
void LinkedListState::dynamicArrayInsertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue) {}
void LinkedListState::dynamicArrayDeleteAnimation(sf::Time dt, double speed, int deleteIndex) {}
void LinkedListState::dynamicArrayDeleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue) {}
void LinkedListState::dynamicArrayUpdateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue) {}
void LinkedListState::dynamicArrayUpdateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue) {}
void LinkedListState::dynamicArraySearchAnimation(sf::Time dt, double speed, int searchValue) {}
void LinkedListState::dynamicArraySearchAnimationReversed(sf::Time dt, double speed, int searchValue) {}