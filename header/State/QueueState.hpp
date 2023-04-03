#pragma once
#include <State/DataStructureState.hpp>

class QueueState : public DataStructureState {
public: 
    QueueState(sf::RenderWindow &window) : DataStructureState(window) {}
    virtual void createDataStructure(std::vector<int> list);
    virtual void insertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue);
    virtual void insertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue);
    virtual void deleteAnimation(sf::Time dt, double speed, int deleteIndex);
    virtual void deleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue);
};