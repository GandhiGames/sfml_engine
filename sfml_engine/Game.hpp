//
//  Game.hpp
//  sfml_engine
//
//  Created by Robert Wells on 23/02/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Window.hpp"
#include "World.hpp"
#include "Snake.hpp"

class Game {
public:
    Game();
    ~Game();
    
    void HandleInput();
    void Update();
    void Render();
    
    const Window & GetWindow();
    
    sf::Time GetElapsed();
    void RestartClock();
    
private:
    Window m_window;
    World m_world;
    Snake m_snake;
    sf::Vector2i m_increment;
    sf::Clock m_clock;
    float m_elapsed;
    
};

#endif /* Game_hpp */
