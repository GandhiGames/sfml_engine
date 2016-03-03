//
//  State_Game.hpp
//  sfml_engine
//
//  Created by Robert Wells on 03/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef State_Game_hpp
#define State_Game_hpp

#include "BaseState.h"
#include "EventManager.hpp"

class State_Game : public BaseState {
public:
    State_Game(StateManager &l_stateManager);
    ~State_Game();
    
    void OnCreate();
    void OnDestroy();
    
    void Activate();
    void Deactivate();
    
    void Update(const sf::Time &l_time);
    void Draw();

    void MainMenu(EventDetails *l_detals);
    void Pause(EventDetails *l_details);
    
private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Vector2f m_increment;
};

#endif /* State_Game_hpp */
