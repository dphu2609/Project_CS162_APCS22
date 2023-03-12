#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "ResourceHolder.hpp"
#include "SceneGraph.hpp"

// namespace Textures {
//     enum ID {
//         menuBackGround,
//         rightArrow,
//         pointerArrow,
//         nextButton,
//         prevButton,
//         playButton,
//         pauseButton
//     };
// };

// namespace Fonts {
//     enum ID {
//         ComfortaaRegular,
//         FiraSansRegular,
//         GreateVibesRegular,
//         TiltWarpRegular
//     };
// };

class State : private sf::NonCopyable {
public:
    explicit State(sf::RenderWindow &window);
    void update(sf::Time dt);
    void draw();
public:
    enum Layers {
        Nodes,
        LayerCount
    };
    std::vector<int> arr;
    std::vector<std::unique_ptr<LinkedListNode>> nodes;
    sf::RenderWindow &mWindow;
    std::array<SceneNode*, LayerCount> mSceneLayers;
    SceneNode mSceneGraph;
    ResourceHolder<sf::Texture, Textures::ID> mTexturesHolder;
    ResourceHolder<sf::Font, Fonts::ID> mFontsHolder;
private:
    void loadTextures();
    void loadFonts();
    void buildScence();
};

class MenuState : public State {
public:
    explicit MenuState(sf::RenderWindow &window);
    void activateAnimation(sf::Time dt, double speed);
private:
    std::vector<int> arr;
    enum Layers {
        Nodes,
        LayerCount
    };
private:
    void loadTextures();
    void loadFonts();
    void buildScence();
};