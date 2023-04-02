#include <State/DataStructureState.hpp>

DataStructureState::DataStructureState(sf::RenderWindow &window) : State(window) {
    loadTextures();
    loadFonts();
    loadCode();
    buildScence();
} 

void DataStructureState::loadTextures() {
    this->mTexturesHolder.load(Textures::rightArrow, "img/rightArrow.png");
    this->mTexturesHolder.load(Textures::leftArrow, "img/leftArrow.png");
}

void DataStructureState::loadFonts() {
    this->mFontsHolder.load(Fonts::FiraSansRegular, "fonts/FiraSans-Regular.ttf");
    this->mFontsHolder.load(Fonts::FiraMonoRegular, "fonts/Fira_Mono/FiraMono-Regular.ttf");
}

void DataStructureState::loadCode() {
    this->mCodeHolder.load();
}

void DataStructureState::buildScence() {
    for (int i = 0; i < LayerCount; i++) {
        SceneNode::Ptr layer = std::make_unique<SceneNode>();
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }
    
} 

void DataStructureState::resetNodeState() {
    for (int i = 0; i < LayerCount; i++) {
        for (auto &child : mSceneLayers[i]->getChildren()) {
            child->mIsDoneColoring = 0;
            child->mIsDoneMoving = 0;
            child->mIsDoneRotating = 0;
            child->mIsDoneScaling = 0;
        }
    }
}

bool DataStructureState::isProcessing() {
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