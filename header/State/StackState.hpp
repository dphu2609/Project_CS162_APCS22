#include <State/DataStructureState.hpp>

class StackState : public DataStructureState {
public: 
    virtual void createDataStructure(std::vector<int> list);
    virtual void insertAnimation(sf::Time dt, double speed, int insertIndex, int insertValue);
    virtual void insertAnimationReversed(sf::Time dt, double speed, int insertIndex, int insertValue);
    virtual void deleteAnimation(sf::Time dt, double speed, int deleteIndex);
    virtual void deleteAnimationReversed(sf::Time dt, double speed, int deleteIndex, int deleteValue);
}