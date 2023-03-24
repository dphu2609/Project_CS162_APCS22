#include <State/SinglyLinkedListState.hpp>

LinkedListState::LinkedListState(sf::RenderWindow &window) : State(window) {
    loadTextures();
    loadFonts();
    buildScence();
} 

void LinkedListState::loadTextures() {
    this->mTexturesHolder.load(Textures::playButton, "img/playButton.png");
    this->mTexturesHolder.load(Textures::playButtonHoverred, "img/playButtonHoverred.png");
    this->mTexturesHolder.load(Textures::rightArrow, "img/rightArrow.png");
}

void LinkedListState::loadFonts() {
    this->mFontsHolder.load(Fonts::FiraSansRegular, "fonts/FiraSans-Regular.ttf");
}

void LinkedListState::buildScence() {
    for (int i = 0; i < LayerCount; i++) {
        SceneNode::Ptr layer = std::make_unique<SceneNode>();
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }
    mAnimationOrder = 0;
}  

void LinkedListState::handleClick(sf::Event &event) {
    //Handle Button
    int index = 0;
    for (auto &child : this->mSceneLayers[Button]->getChildren()) {
        if (child->getClickedIndex(event) == 0) {
            switch (index) {
                case ButtonType::Create : {
                    std::cout << "Button Create Clicked" << std::endl;
                    // if (!this->isAdd) {
                    //     this->animationOrder = 1;
                    //     // this->isAdd = 1;
                    // }
                }
            }
        }
    }
    //------------------------------------------------------
}

void LinkedListState::createList(std::vector<int> &list) {
    for (int i = 0; i < LayerCount; i++) {
        mSceneLayers[i]->getChildren().clear();
    }
    mListData = list;
    // mActionIndex = 2;
    // mInsertValue = 12;
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