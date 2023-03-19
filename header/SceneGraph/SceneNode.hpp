#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <DataStructure.h>
#include <Button.hpp>
#include <Event.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable{
public:
    typedef std::unique_ptr<SceneNode> Ptr;
    SceneNode();
    void attachChild(Ptr child);
    Ptr detachChild(const SceneNode& node);
    void update (sf::Time dt);
    std::vector<std::unique_ptr<SceneNode>>& getChildren() { return mChildren; }
    virtual void triggerMoveAnimation(sf::Time dt, double speed, double movingDistance, double angleMovement);
    virtual void triggerRotateAnimation(sf::Time dt, double speed, double rotatingDistance);
    virtual void triggerScaleAnimation(sf::Time dt, double lengthSpeed, double scalingLengthDistance, double widthSpeed, double scalingWidthDistance);
    virtual bool isLeftClicked();
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
    double mMovingDistance;
    double mCurrentPos;
    double mMovingStep;
    double mAngleMovement;
    bool mIsMoving;
    bool mIsDoneMoving;
    //--------------------------
    //rotate animation variables
    double mRotatingDistance;
    double mStartAngle;
    double mCurrentAngle;
    double mRotatingStep;
    bool mIsRotating;
    bool mIsDoneRotating;
    //-----------------------------
    //scale animation variables
    sf::Vector2f mStartScale;
    double mScalingWidthDistance;
    double mCurrentWidthScale;
    double mScalingWidthStep;
    double mScalingLengthDistance;
    double mCurrentLengthScale;
    double mScalingLengthStep;
    bool mIsScaling;
    bool mIsDoneScaling;
    //-----------
};

#include <SceneGraph/ImageButtonNode.hpp>
#include <SceneGraph/DisplayNode.hpp>
#include <SceneGraph/SpriteNode.hpp>
#include <SceneGraph/RectangleButtonNode.hpp>
#include <SceneGraph/ContainerNode.hpp>