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
    arr = {-6, 23, 49, 100, -35, 4433};
    addIndex = 2;
    for (int i = 0; i < arr.size(); i++) {
        std::unique_ptr<DisplayNode> newNode = std::make_unique<DisplayNode>(
            arr[i], mFontsHolder[Fonts::FiraSansRegular], 
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

    std::unique_ptr<ButtonNode> newButton = std::make_unique<ButtonNode>(
        this->mWindow,
        mTexturesHolder[Textures::playButton], mTexturesHolder[Textures::playButtonHoverred],
        sf::Vector2f(100, 100), sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - 50, sf::VideoMode::getDesktopMode().height - 300)
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
                if (!child->mIsMoving) animationOrder = 2;
                return;
            }
            std::unique_ptr<DisplayNode> addedNode = std::make_unique<DisplayNode>(
                12, mFontsHolder[Fonts::FiraSansRegular], 
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (arr.size()/2)*250 + (addIndex)*250, 750), 
                sf::Color::Black, sf::Color::White, sf::Color(145, 174, 226, 255)
            );
            addedNode->triggerMoveAnimation(dt, speed, 250, -90);
            mSceneLayers[newNode]->attachChild(std::move(addedNode));
            break;
        }
        case 2: {
            for (auto &child : this->mSceneLayers[tempArrow]->getChildren()) {
                if (child->mIsDoneScaling) animationOrder = 3;
                return;
            }
            std::unique_ptr<SpriteNode> newArrow = std::make_unique<SpriteNode>(
                mTexturesHolder[Textures::rightArrow], sf::Vector2f(0, 50), 
                sf::Vector2f(sf::VideoMode::getDesktopMode().width/2 - (arr.size()/2)*250 + (addIndex)*250 + 35, 500), -90
            );
            newArrow->triggerScaleAnimation(dt, speed, 110, 0, 0);
            mSceneLayers[tempArrow]->attachChild(std::move(newArrow));
            break;
        }
        case 3: {
            int index = 0;
            for (auto &child : this->mSceneLayers[Arrow]->getChildren()) {
                if (index == addIndex - 1) {
                    if (!child->mIsScaling && !child->mIsDoneScaling) {
                        child->triggerRotateAnimation(dt, speed*1.25, 66.8);
                        child->triggerScaleAnimation(dt, speed*0.7, (110/std::cos(66.8*std::atan(1)*4/180)) - 110, 0, 0);
                        child->triggerMoveAnimation(dt, speed*2, 25, 30);
                    } 
                    else if (!child->mIsScaling && child->mIsDoneScaling) {
                        animationOrder = 4;
                    }
                    return;
                }
                index++;
            }
            break;
        }
    }
}

void LinkedListState::handleEvent() {
    //Handle Button
    int index = 0;
    for (auto &child : this->mSceneLayers[Button]->getChildren()) {
        if (child->isLeftClicked()) {
            switch (index) {
                case ButtonType::Create : {
                    std::cout << "Button Create Clicked" << std::endl;
                    this->animationOrder = 1;
                    this->isAdd = 1;
                }
            }
        }
    }
    //------------------------------------------------------
}