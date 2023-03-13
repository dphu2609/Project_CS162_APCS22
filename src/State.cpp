#include "../header/State.hpp"

State::State(sf::RenderWindow &window) : mWindow(window) {}

void State::draw() {
    mWindow.draw(mSceneGraph);
}

void State::update(sf::Time dt) {
    mSceneGraph.update(dt);
} 

LinkedListState::LinkedListState(sf::RenderWindow &window) : State(window) {
    loadTextures();
    loadFonts();
    buildScence();
} 

void LinkedListState::loadTextures() {
    this->mTexturesHolder.load(Textures::playButton, "img/playButton.png");
    this->mTexturesHolder.load(Textures::playButtonHoverred, "img/playButtonHoverred.png");
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
    arr = {-6, 23, 49, 100, -35, 4433};
    addIndex = 2;
    for (int i = 0; i < arr.size(); i++) {
        std::unique_ptr<LinkedListNode> newNode = std::make_unique<LinkedListNode>(
            arr[i], mFontsHolder[Fonts::FiraSansRegular], 
            sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (arr.size()/2)*250 + i*250, 250), 
            sf::Color::Black, sf::Color::White, sf::Color::Blue
        );
        mSceneLayers[Nodes]->attachChild(std::move(newNode));
    }

    std::unique_ptr<ButtonNode> newButton = std::make_unique<ButtonNode>(
        this->mWindow,
        mTexturesHolder[Textures::playButton], mTexturesHolder[Textures::playButtonHoverred],
        100, 100, sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - 50, sf::VideoMode::getDesktopMode().height - 300)
    );
    mSceneLayers[Button]->attachChild(std::move(newButton));
    animationOrder = 1;
    isAdd = 1;
}  

void LinkedListState::activateAnimation(sf::Time dt, double speed) {
    for (auto& child : mSceneLayers[Nodes]->getChildren()) {
        child->triggerMoveAnimation(dt, speed, 250, 30);
    }
}

void LinkedListState::addAnimation(sf::Time dt, double speed) {
    switch (animationOrder) {
        case 1: {
            for (auto &child : this->mSceneLayers[newNode]->getChildren()) {
                if (!child->isProcess) animationOrder = 2;
                return;
            }
            std::unique_ptr<LinkedListNode> addedNode = std::make_unique<LinkedListNode>(
                12, mFontsHolder[Fonts::FiraSansRegular], 
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (arr.size()/2)*250 + (addIndex)*250, 750), 
                sf::Color::Black, sf::Color::White, sf::Color::Blue
            );
            addedNode->triggerMoveAnimation(dt, speed, 250, -90);
            mSceneLayers[newNode]->attachChild(std::move(addedNode));
            break;
        }
        case 2: {
            std::cout << 2;
        }
    }
}