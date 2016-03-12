//
//  State_GameOver.hpp
//  sfml_engine
//
//  Created by Robert Wells on 12/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef State_GameOver_hpp
#define State_GameOver_hpp

#include "BaseState.h"

class State_GameOver : public BaseState {
public:
    State_GameOver(StateManager &l_stateManager);
    ~State_GameOver();
    
    void OnCreate();
    void OnDestroy();
    
    void Activate();
    void Deactivate();
    
    void Update(const sf::Time& l_time);
    void Draw();
private:
    sf::Font m_font;
    sf::Text m_text;
    float m_elapsed;
};

#endif /* State_GameOver_hpp */
