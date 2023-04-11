#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <ResourceHolder.hpp>
#include <SceneGraph/SceneNode.hpp>
#include <Event.hpp>
#include <CodeHolder.hpp>
#include <Constant.hpp>


class State : private sf::NonCopyable {
public:
    explicit State(sf::RenderWindow &window);
    void update(sf::Time dt);
    void draw();
    void handleEvent(sf::Event &event);
public:
    sf::RenderWindow &mWindow;
    std::array<SceneNode*, 20> mSceneLayers;
    SceneNode mSceneGraph;
    ResourceHolder<sf::Texture, Textures::ID> mTexturesHolder;
    ResourceHolder<sf::Font, Fonts::ID> mFontsHolder;
    CodeHolder mCodeHolder;
private:
    virtual void loadTextures() = 0;
    virtual void loadFonts() = 0;
    virtual void loadCode() = 0;
    virtual void buildScence() = 0;
};

#include <State/DataStructureState.hpp>
#include <State/SettingsState.hpp>


