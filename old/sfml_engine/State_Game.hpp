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
#include "Map.hpp"
#include "EventManager.hpp"
#include "S_Movement.hpp"
#include "S_Collision.hpp"

class State_Game : public BaseState{
public:
    State_Game(StateManager& l_stateManager);
    ~State_Game();
    
    void OnCreate();
    void OnDestroy();
    
    void Activate();
    void Deactivate();
    
    void Update(const sf::Time& l_time);
    void Draw();
    
    void MainMenu(EventDetails* l_details);
    void Pause(EventDetails* l_details);
    void PlayerMove(EventDetails* l_details);
    void OpenConsole(EventDetails* l_details);
    
    // Debug:
    void ToggleOverlay(EventDetails* l_details);
private:
    void UpdateCamera();
    
    Map* m_gameMap;
    int m_player;
};

#endif /* State_Game_hpp */
