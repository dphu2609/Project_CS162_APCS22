#pragma once
#include <State/DataStructureState.hpp>

class SLLState : public DataStructureState {
public: 
    SLLState(sf::RenderWindow &window) : DataStructureState(window) {}
    virtual void createDataStructure(std::vector<int> list);
    virtual void insertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue);
    virtual void insertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue);
    virtual void deleteAnimation(sf::Time dt, double speed, int deleteIndex);
    virtual void deleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue);
    virtual void updateAnimation(sf::Time dt, double speed, int updateIndex, int updateValue);
    virtual void updateAnimationReversed(sf::Time dt, double speed, int updateIndex, int prevValue);
    virtual void searchAnimation(sf::Time dt, double speed, int searchValue);
    virtual void searchAnimationReversed(sf::Time dt, double speed, int searchValue);
};