#include <State/SinglyLinkedListState.hpp>

LinkedListState::LinkedListState(sf::RenderWindow &window) : State(window) {
    loadTextures();
    loadFonts();
    loadCode();
    buildScence();
} 

void LinkedListState::loadTextures() {
    this->mTexturesHolder.load(Textures::playButton, "img/playButton.png");
    this->mTexturesHolder.load(Textures::playButtonHoverred, "img/playButtonHoverred.png");
    this->mTexturesHolder.load(Textures::rightArrow, "img/rightArrow.png");
}

void LinkedListState::loadFonts() {
    this->mFontsHolder.load(Fonts::FiraSansRegular, "fonts/FiraSans-Regular.ttf");
    this->mFontsHolder.load(Fonts::FiraMonoRegular, "fonts/Fira_Mono/FiraMono-Regular.ttf");
}

void LinkedListState::loadCode() {
    this->mCodeHolder.load();
}

void LinkedListState::buildScence() {
    for (int i = 0; i < LayerCount; i++) {
        SceneNode::Ptr layer = std::make_unique<SceneNode>();
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }
    
}  

void LinkedListState::handleClick(sf::Event &event) {
    // //Handle Button
    // int index = 0;
    // for (auto &child : this->mSceneLayers[Button]->getChildren()) {
    //     if (child->getClickedIndex(event) == 0) {
    //         switch (index) {
    //             case ButtonType::Create : {
    //                 std::cout << "Button Create Clicked" << std::endl;
    //                 // if (!this->isAdd) {
    //                 //     this->animationOrder = 1;
    //                 //     // this->isAdd = 1;
    //                 // }
    //             }
    //         }
    //     }
    // }
    //------------------------------------------------------
}

void LinkedListState::resetNodeState() {
    for (int i = 0; i < LayerCount; i++) {
        for (auto &child : mSceneLayers[i]->getChildren()) {
            child->mIsDoneColoring = 0;
            child->mIsDoneMoving = 0;
            child->mIsDoneRotating = 0;
            child->mIsDoneScaling = 0;
        }
    }
}

bool LinkedListState::isProcessing() {
    for (int i = 0; i < LayerCount; i++) {
        for (auto &child : mSceneLayers[i]->getChildren()) {
            if (child->mIsColoring) return 1;
            if (child->mIsMoving) return 1;
            if (child->mIsRotating) return 1;
            if (child->mIsScaling) return 1;
        }
    }
    return 0;
}