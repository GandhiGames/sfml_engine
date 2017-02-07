//
//  State_Console.hpp
//  sfml_engine
//
//  Created by Robert Wells on 06/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef State_Console_hpp
#define State_Console_hpp

#include "BaseState.h"
#include "EventManager.hpp"
#include "Console.hpp"

class State_Console : public BaseState {
public:
    State_Console(StateManager& l_stateManager);
    ~State_Console();
    
    void OnCreate();
    void OnDestroy();
    
    void Activate();
    void Deactivate();
    
    void Update(const sf::Time &l_time);
    void Draw();
    
    void OpenFull(EventDetails* l_details);
    void Close(EventDetails* l_details);

private:
    void OpenHalf();

    
    Console* m_console;
};

#endif /* State_Console_hpp */
