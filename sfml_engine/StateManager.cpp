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
   /* RegisterState<State_Intro>(StateType::Intro);
    RegisterState<State_MainMenu>(StateType::MainMenu);
    RegisterState<State_Game>(StateType::Game);
    RegisterState<State_Paused>(StateType::Paused); */
}

StateManager::~StateManager()
{
    for(auto &itr : m_states){
        itr.second->OnDestroy();
        delete itr.second;
    }
}

void StateManager::ProcessRequests()
{
    
}