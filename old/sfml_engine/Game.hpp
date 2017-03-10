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
#include "Entity_Manager.hpp"
#include "Textbox.hpp"
#include "Console.hpp"
#include "SystemManager.hpp"
#include "FPS.hpp"
#include "UI_Manager.hpp"
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
    SystemManager m_systemManager;
    TextureManager m_textureManager;
    FontManager m_fontManager;
    StateManager m_stateManager;
    DebugOverlay m_debugOverlay;
    Textbox m_debugText;
    FPS m_fps;
    UI_Manager m_uiManager;
};

#endif /* Game_hpp */
