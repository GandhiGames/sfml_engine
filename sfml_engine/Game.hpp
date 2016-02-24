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
#include "ResourcePath.hpp"

class Game {
public:
    Game();
    ~Game();
    
    void HandleInput();
    void Update();
    void Render();
    
    Window* GetWindow();
    
private:
    void MoveMushroom();
    Window m_window;
    sf::Texture m_mushroomTexture;
    sf::Sprite m_mushroom;
    sf::Vector2i m_increment;
    
};

#endif /* Game_hpp */
