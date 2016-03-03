//
//  State_Paused.hpp
//  sfml_engine
//
//  Created by Robert Wells on 03/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef State_Paused_hpp
#define State_Paused_hpp

#include "BaseState.h"
#include "EventManager.hpp"

class State_Paused : public BaseState {
public:
    State_Paused(StateManager &l_stateManager);
    ~State_Paused();
    
    void OnCreate();
    void OnDestroy();
    
    void Activate();
    void Deactivate();
    
    void Update(const sf::Time &l_time);
    void Draw();
    
    void UnPause(EventDetails *l_details);
    
private:
    sf::Font m_font;
    sf::Text m_text;
    sf::RectangleShape m_rect;
};

#endif /* State_Paused_hpp */
