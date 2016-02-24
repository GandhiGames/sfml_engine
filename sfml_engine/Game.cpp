//
//  Game.cpp
//  sfml_engine
//
//  Created by Robert Wells on 23/02/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "Game.hpp"

Game::Game() : m_window("engine_test", sf::Vector2u(800, 600))
{
    m_mushroomTexture.loadFromFile(resourcePath() + "mushroom.png");
    
    m_mushroom.setTexture(m_mushroomTexture);
    
    m_increment = sf::Vector2i(4, 4);
}

Game::~Game(){}

void Game::Update()
{
    m_window.Update();
    MoveMushroom();
}

void Game::MoveMushroom()
{
    const sf::Vector2u *l_windSize = m_window.GetWindowSize();
    sf::Vector2u l_size = m_mushroomTexture.getSize();
    
    if((m_mushroom.getPosition().x + (l_size.x / 2) > l_windSize->x && m_increment.x > 0)
       || (m_mushroom.getPosition().x - (l_size.x / 2) < 0 && m_increment.x < 0)){
        // Reverse the direction on X axis.
        m_increment.x = -m_increment.x;
    }
    
    if((m_mushroom.getPosition().y + (l_size.y / 2) > l_windSize->y && m_increment.y > 0)
       || (m_mushroom.getPosition().y - (l_size.y / 2) < 0 && m_increment.y < 0)){
        // Reverse the direction on Y axis.
        m_increment.y = -m_increment.y;
    }
    
    m_mushroom.setPosition(m_mushroom.getPosition().x + m_increment.x, m_mushroom.getPosition().y + m_increment.y);
}

void Game::Render()
{
    m_window.BeginDraw();
    m_window.Draw(m_mushroom);
    m_window.EndDraw();
}
