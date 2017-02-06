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
#include "EntityManager.hpp"
#include "Textbox.hpp"
#include "Console.hpp"
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
    void RestartClock();
    
    sf::Clock m_clock;
    sf::Time m_elapsed;
    SharedContext m_context;
    Window m_window;
    EntityManager m_entityManager;
    TextureManager m_textureManager;
    StateManager m_stateManager;
    DebugOverlay m_debugOverlay;
    Textbox m_debugText;
    Console m_console;
};

#endif /* Game_hpp */
