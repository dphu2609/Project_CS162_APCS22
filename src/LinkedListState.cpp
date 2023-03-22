#include <State/LinkedListState.hpp>

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
    arr = {-6, 23, 49, 100, -35, 4433, -5000};
    addIndex = 2;
    addValue = 12;
    for (int i = 0; i < arr.size(); i++) {
        std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
            arr[i], mFontsHolder[Fonts::FiraSansRegular], 100, 
            sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (arr.size()/2)*250 + i*250, 250), 
            sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
        );
        mSceneLayers[Nodes]->attachChild(std::move(newNode));
    }
    
    for (int i = 0; i < arr.size() - 1; i++) {
        std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
            mTexturesHolder[Textures::rightArrow], sf::Vector2f(110, 50), 
            sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (arr.size()/2)*250 + i*250 + 130, 285), 0
        );
        mSceneLayers[Arrow]->attachChild(std::move(newArrow));
    }

    std::unique_ptr<ImageButtonNode> newButton = std::make_unique<ImageButtonNode>(
        this->mWindow,
        mTexturesHolder[Textures::playButton], mTexturesHolder[Textures::playButtonHoverred],
        sf::Vector2f(100, 100), sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - 50, sf::VideoMode::getDesktopMode().height - 300)
    );
    mSceneLayers[Button]->attachChild(std::move(newButton));
    animationOrder = 1;
    isAdd = 1;
}  

void LinkedListState::handleClick(sf::Event &event) {
    //Handle Button
    int index = 0;
    for (auto &child : this->mSceneLayers[Button]->getChildren()) {
        if (child->getClickedIndex(event) == 0) {
            switch (index) {
                case ButtonType::Create : {
                    std::cout << "Button Create Clicked" << std::endl;
                    if (!this->isAdd) {
                        this->animationOrder = 1;
                        this->isAdd = 1;
                    }
                }
            }
        }
    }
    //------------------------------------------------------
}