//
//  StateManager.hpp
//  sfml_engine
//
//  Created by Robert Wells on 01/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef StateManager_hpp
#define StateManager_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include "BaseState.h"
#include "SharedContext.h"


enum class StateType {
    Intro = 1,
    MainMenu,
    Game,
    Paused,
    GameOver,
    Credits
};

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;

using TypeContainer = std::vector<StateType>;

using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager{
public:
    StateManager(SharedContext &l_sharedContext);
    ~StateManager();
    
    void Update(sf::Time &l_time);
    void Draw();
    
    void ProcessRequests();
    
    SharedContext &GetContext();
    
    const bool &HasState(const StateType &l_type) const;
    
    void SwitchTo(const StateType &l_type);
    void Remove(const StateType &l_type);
    
private:
    void CreateState(const StateType &l_type);
    void RemoveState(const StateType &l_type);
    
    template<class T>
    void RegisterState(const StateType &l_type)
    {
        m_stateFactory[l_type] = [this]()->BaseState*
        {
            return new T(this);
        }
    }
    
    SharedContext &m_sharedContext;
    StateContainer m_states;
    TypeContainer m_toRemove;
    StateFactory m_stateFactory;
};





#endif /* StateManager_hpp */
