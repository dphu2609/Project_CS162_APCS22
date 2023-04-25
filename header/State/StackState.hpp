#pragma once
#include <State/DataStructureState.hpp>

class StackState : public DataStructureState {
public: 
    StackState(sf::RenderWindow &window) : DataStructureState(window) {}
    virtual void createDataStructure(SinglyLinkedList<int> &list);
    virtual void insertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue);
    virtual void insertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue);
    virtual void deleteAnimation(sf::Time dt, double speed, int deleteIndex);
    virtual void deleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue);
};