//
//  Game.hpp
//  sfml_engine
//
//  Created by Robert Wells on 23/02/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "Window.hpp"
#include "EventManager.hpp"
#include "StateManager.hpp"
#include "SharedContext.h"
#include <iostream>

class Game {
public:
    Game();
    ~Game();
    
    void Update();
    void Render();
    void LateUpdate();
    
    sf::Time GetElapsed();
    
    Window* GetWindow();
private:
    SharedContext m_context;
    Window m_window;
    StateManager m_stateManager;
    sf::Clock m_clock;
    sf::Time m_elapsed;
    void RestartClock();
};

#endif /* Game_hpp */
