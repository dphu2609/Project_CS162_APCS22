#include "../header/State.hpp"

State::State(sf::RenderWindow &window) : mWindow(window) {
    loadTextures();
    loadFonts();
    buildScence();
}

void State::draw() {
    mWindow.draw(mSceneGraph);
}

void State::update(sf::Time dt) {
    mSceneGraph.update(dt);
} 

MenuState::MenuState(sf::RenderWindow &window) : State(window) {
    loadTextures();
    loadFonts();
    buildScence();
}

void State::loadTextures() {
    // this->mTexturesHolder.load(Textures::menuBackGround, "img/menu_background.jpg");
}

void State::loadFonts() {
    this->mFontsHolder.load(Fonts::ComfortaaRegular, "fonts/FiraSans-Regular.ttf");
}

void State::buildScence() {
    for (int i = 0; i < LayerCount; i++) {
        SceneNode::Ptr layer = std::make_unique<SceneNode>();
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }
    arr = {-6, 23, 49, 100, -35, 4433};
    for (int i = 0; i < arr.size(); i++) {
        std::unique_ptr<LinkedListNode> newNode = std::make_unique<LinkedListNode>(
            arr[i], mFontsHolder[Fonts::ComfortaaRegular], 
            sf::Vector2f(10 + i*250, 500), 
            sf::Color::Black, sf::Color::White, sf::Color::Blue
        );
        mSceneLayers[Nodes]->attachChild(std::move(newNode));
    }
}  

void MenuState::loadTextures() {
    // this->mTexturesHolder.load(Textures::menuBackGround, "./img/menu_background.jpg");
}

void MenuState::loadFonts() {
    // this->mFontsHolder.load(Fonts::ComfortaaRegular, "fonts/Comfortaa_Regular.ttf");
}

void MenuState::buildScence() {
    // for (int i = 0; i < LayerCount; i++) {
    //     SceneNode::Ptr layer = std::make_unique<SceneNode>();
    //     mSceneLayers[i] = layer.get();
    //     mSceneGraph.attachChild(std::move(layer));
    // }
    // // arr = {-6, 23, 49, 100, -35, 4433};
    // // for (int i = 0; i < arr.size(); i++) {
    // //     std::cout << 4;
    // //     std::unique_ptr<LinkedListNode> newNode = std::make_unique<LinkedListNode>(
    // //         arr[i], mFontsHolder[Fonts::ComfortaaRegular], 
    // //         sf::Vector2f(sf::VideoMode::getDesktopMode().width - arr.size()*250/2 + i *250, 250), 
    // //         sf::Color::Black, sf::Color::White, sf::Color::Blue);
    // //     // nodes.push_back(std::move(newNode));
    // //     mSceneLayers[Nodes]->attachChild(std::move(newNode));
    // // }
}  

void MenuState::activateAnimation(sf::Time dt, double speed) {
    for (auto& child : mSceneLayers[Nodes]->getChildren()) {
        child->triggerMoveAnimation(dt, speed, 250, 0);
    }
}