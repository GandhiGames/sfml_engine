//
//  BaseState.h
//  sfml_engine
//
//  Created by Robert Wells on 01/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef BaseState_h
#define BaseState_h

//#include "StateManager.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>

class StateManager;

class BaseState {
    friend class StateManager;
    
public:
    BaseState(StateManager &l_stateManager):m_stateManager(l_stateManager), m_transparent(false), m_trancendent(false){};
    virtual ~BaseState(){};
    
    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;
    
    virtual void Activate() = 0;
    virtual void Deactivate() = 0;
    
    virtual void Update(const sf::Time &l_time) = 0;
    virtual void Draw() = 0;
    
    void SetTransparent(const bool &l_transparent)
    {
        m_transparent = l_transparent;
    }
    
    const bool& IsTransparent() const
    {
        return m_transparent;
    }
    
    void SetTrancendent(const bool &l_trancendent)
    {
        m_trancendent = l_trancendent;
    }
    
    const bool &IsTrancendent() const
    {
        return m_trancendent;
    }
    
    StateManager &GetStateManager()
    {
        return m_stateManager;
    }
    
    sf::View &GetView()
    {
        return m_view;
    }

protected:
    StateManager &m_stateManager;
    sf::View m_view;
    bool m_transparent;
    bool m_trancendent;
};




#endif /* BaseState_h */
