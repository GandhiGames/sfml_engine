//
//  StateManager.cpp
//  sfml_engine
//
//  Created by Robert Wells on 01/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "StateManager.hpp"

StateManager::StateManager(SharedContext &l_sharedContext):m_sharedContext(l_sharedContext)
{
    RegisterState<State_Intro>(StateType::Intro);
    RegisterState<State_Menu>(StateType::MainMenu);
    RegisterState<State_Game>(StateType::Game);
    RegisterState<State_Paused>(StateType::Paused);
}

StateManager::~StateManager()
{
    for(auto &itr : m_states){
        itr.second->OnDestroy();
        delete itr.second;
    }
}

// if transparent draw functions must be called in correct order - latest stack must be drawn last.
void StateManager::Draw()
{
    if (m_states.empty()) {
        return;
    }
    
    if (m_states.back().second->IsTransparent() && m_states.size() > 1) {
        auto itr = m_states.end();
        while (itr != m_states.begin()) {
            if (itr != m_states.end()) {
                if (!itr->second->IsTransparent()) {
                    break;
                }
            }
            --itr;
        }
        
        for (; itr != m_states.end(); itr++) {
            m_sharedContext.GetWindow()->GetRenderWindow()->setView(itr->second->GetView());
            itr->second->Draw();
        }
    } else {
        m_states.back().second->Draw();
    }
}

void StateManager::Update(sf::Time &l_time)
{
    if (m_states.empty()) {
        return;
    }
    
    if (m_states.back().second->IsTrancendent() && m_states.size() > 1) {
        auto itr = m_states.end();
        while (itr != m_states.begin()) {
            if (itr != m_states.end()) {
                if (!itr->second->IsTrancendent()) {
                    break;
                }
            }
            --itr;
        }
        
        for (; itr != m_states.end(); itr++) {
            itr->second->Update(l_time);
        }
    } else {
        m_states.back().second->Update(l_time);
    }
}

SharedContext& StateManager::GetContext()
{
    return m_sharedContext;
}

bool StateManager::HasState(const StateType &l_type) const
{
    for(auto itr = m_states.begin(); itr != m_states.end(); itr++) {
        if (itr->first == l_type) {
            auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), l_type);
            if (removed == m_toRemove.end()) {
                return true;
            } else {
                return false;
            }
        }
    }
    
    return false;
}

void StateManager::Remove(const StateType &l_type)
{
    m_toRemove.push_back(l_type);
}

void StateManager::ProcessRequests()
{
    while (m_toRemove.begin() != m_toRemove.end()) {
        RemoveState(*m_toRemove.begin());
        m_toRemove.erase(m_toRemove.begin());
    }
}

void StateManager::SwitchTo(const StateType &l_type)
{
    m_sharedContext.GetEventManager()->SetCurrentState(l_type);
    for (auto itr = m_states.begin();
         itr != m_states.end(); ++itr)
    {
        if (itr->first == l_type){
            m_states.back().second->Deactivate();
            StateType tmp_type = itr->first;
            BaseState* tmp_state = itr->second;
            m_states.erase(itr);
            m_states.emplace_back(tmp_type, tmp_state);
            tmp_state->Activate();
            
            m_sharedContext.GetWindow()->GetRenderWindow()->setView(tmp_state->GetView());
            
            return;
        }
    }
    
    // State with l_type wasn't found.
    if (!m_states.empty()){
        m_states.back().second->Deactivate();
    }
    
    CreateState(l_type);
    m_states.back().second->Activate();
    m_sharedContext.GetWindow()->GetRenderWindow()->setView(m_states.back().second->GetView());
}

void StateManager::CreateState(const StateType &l_type)
{
   	auto newState = m_stateFactory.find(l_type);
    if (newState == m_stateFactory.end()){ return; }
    BaseState* state = newState->second();
    state->GetView() = m_sharedContext.GetWindow()->GetRenderWindow()->getDefaultView();
    m_states.emplace_back(l_type, state);
    state->OnCreate();
}

void StateManager::RemoveState(const StateType &l_type)
{
    for (auto itr = m_states.begin(); itr != m_states.end(); itr++) {
        if (itr->first == l_type) {
            itr->second->OnDestroy();
            delete itr->second;
            m_states.erase(itr);
            return;
        }
    }
}