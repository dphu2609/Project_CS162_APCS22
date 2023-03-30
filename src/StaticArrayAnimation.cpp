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
    mListData = list;
    for (int i = 0; i < list.size(); i++) {
        std::unique_ptr<DisplayNode> arrayNode = std::make_unique<DisplayNode>(
            mListData[i], mFontsHolder[Fonts::FiraSansRegular], 100, sf::Vector2f(mWindow.getSize().x/2 - 645 + 130*i, 250),
            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
        );
        mSceneLayers[Nodes]->attachChild(std::move(arrayNode));
    }
    std::unique_ptr<ContainerNode> arrayBorder = std::make_unique<ContainerNode>(
        mWindow, sf::Vector2f(120*list.size() + 10*(list.size() - 1), 120), 10, sf::Vector2f(mWindow.getSize().x/2 - 645, 250),
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
                mListData.insert(mListData.begin() + insertIndex, insertData);
            }
        }
    }
}

void LinkedListState::staticArrayInsertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertData) {}
void LinkedListState::staticArrayDeleteAnimation(sf::Time dt, double speed, int deleteIndex) {}
void LinkedListState::staticArrayDeleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue) {}
void LinkedListState::staticArrayUpdateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue) {}
void LinkedListState::staticArrayUpdateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue) {}
void LinkedListState::staticArraySearchAnimation(sf::Time dt, double speed, int searchValue) {}
void LinkedListState::staticArraySearchAnimationReversed(sf::Time dt, double speed, int searchValue) {}