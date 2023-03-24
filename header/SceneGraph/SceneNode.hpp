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
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void update (sf::Time dt);
    void handleEvent(sf::Event &event);
    std::vector<std::unique_ptr<SceneNode>>& getChildren() { return mChildren; }
    virtual void triggerMoveAnimation(sf::Time dt, double speed, double movingDistance, double angleMovement);
    virtual void triggerRotateAnimation(sf::Time dt, double speed, double rotatingDistance);
    virtual void triggerScaleAnimation(sf::Time dt, double lengthSpeed, double scalingLengthDistance, double widthSpeed, double scalingWidthDistance);
    virtual bool isLeftClicked();
    virtual int getClickedIndex(sf::Event &event) {return 0;};
    virtual void resetContent(const std::string &str) {}
    virtual std::string getStringData() {return "";}
    virtual std::vector<int> getIntArrayData() {return {};}
    virtual bool isActivated() {return 0;};
private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
    virtual void handleCurrentEvent(sf::Event &event);
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
    bool mIsMoving = 0;
    bool mIsDoneMoving = 0;
    //--------------------------
    //rotate animation variables
    double mRotatingDistance;
    double mStartAngle;
    double mCurrentAngle;
    double mRotatingStep;
    bool mIsRotating = 0;
    bool mIsDoneRotating = 0;
    //-----------------------------
    //scale animation variables
    sf::Vector2f mStartScale;
    double mScalingWidthDistance;
    double mCurrentWidthScale;
    double mScalingWidthStep;
    double mScalingLengthDistance;
    double mCurrentLengthScale;
    double mScalingLengthStep;
    bool mIsScaling = 0;
    bool mIsDoneScaling = 0;
    //-----------
};

#include <SceneGraph/ImageButtonNode.hpp>
#include <SceneGraph/DisplayNode.hpp>
#include <SceneGraph/SpriteNode.hpp>
#include <SceneGraph/RectangleButtonNode.hpp>
#include <SceneGraph/ContainerNode.hpp>
#include <SceneGraph/DropBoxNode.hpp>
#include <SceneGraph/InputBoxNode.hpp>