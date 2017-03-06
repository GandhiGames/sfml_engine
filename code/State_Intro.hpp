//
//  Intro_State.hpp
//  sfml_engine
//
//  Created by Robert Wells on 02/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef Intro_State_hpp
#define Intro_State_hpp

#include "BaseState.h"
#include "EventManager.hpp"

class State_Intro : public BaseState {
public:
    State_Intro(StateManager &l_stateManager);
    ~State_Intro();
    
    void OnCreate();
    void OnDestroy();
    
    void Activate();
    void Deactivate();
    
    void Update(const sf::Time &l_time);
    void Draw();
    
    void Continue(EventDetails *l_details);
    
private:
    sf::Sprite m_introSprite;
    sf::Text m_text;
};

#endif /* Intro_State_hpp */
