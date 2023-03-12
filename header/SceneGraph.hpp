#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "DataStructure.h"


class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable{
public:
    typedef std::unique_ptr<SceneNode> Ptr;
    SceneNode();
    void attachChild(Ptr child);
    Ptr detachChild(const SceneNode& node);
    void update (sf::Time dt);
    std::vector<std::unique_ptr<SceneNode>>& getChildren() { return mChildren; }
    virtual void triggerMoveAnimation(sf::Time dt, double speed, double distance, double angleMovement);
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
    void updateChildren(sf::Time dt);
private:
    std::vector<Ptr> mChildren;
    SceneNode* mParent;
public:
    std::map<std::string, bool> mAnimationType;
    //move animation variables
    sf::Vector2f mStartPos;
    sf::Vector2f mEndPos;
    double mCurrentPos;
    double mMovingAnimationStep;
    double mAngleMovement;
    //--------------------------
    //rotate animation variables
    double mStartAngle;
    double mEndAngle;
    double mCurrentAngle;
    double mRotatingAnimationStep;
    //-----------------------------
};

class LinkedListNode : public SceneNode {
public: 
    LinkedListNode(int val, sf::Font &font, sf::Vector2f pos, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor);
    virtual void triggerMoveAnimation(sf::Time dt, double speed, double distance, double angleMovement);
public:
    GraphicalNode mNode;
private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
};