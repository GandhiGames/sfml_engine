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
    constexpr static float MENU_TIME = 2.0f;
    sf::Texture m_introTexture;
    sf::Sprite m_introSprite;
    sf::Font m_font;
    sf::Text m_text;
    
    float m_timePassed;
};

#endif /* Intro_State_hpp */
