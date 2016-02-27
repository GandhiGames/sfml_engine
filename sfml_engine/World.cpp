//
//  World.cpp
//  sfml_engine
//
//  Created by Robert Wells on 25/02/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "World.hpp"


World::World(const sf::Vector2u &l_windowSize)
{
    m_blockSize = 16;
    
    m_windowSize = l_windowSize;
    
    RespawnApple();
    
    m_appleShape.setFillColor(sf::Color::Red);
    m_appleShape.setRadius(m_blockSize * 0.5f);
    
    for (int i = 0; i< 4; i++) {
        m_bounds[i].setFillColor(sf::Color::Black);
 
        if (!((i + 1) % 2)) {
            m_bounds[i].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
        } else {
            m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
        }
        
        if (i < 2) {
            m_bounds[i].setPosition(0, 0);
        } else {
            m_bounds[i].setOrigin(m_bounds[i].getSize());
            
            m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
        }
    }
    
}

World::~World()
{
    
}

void World::RespawnApple()
{
    int maxX = (m_windowSize.x / m_blockSize) - 2;
    int maxY = (m_windowSize.y / m_blockSize) - 2;
    m_item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
    
    m_appleShape.setPosition(m_item.x * m_blockSize,
                             m_item.y * m_blockSize);
}

void World::Update(Snake &l_player)
{
    const sf::Vector2i playPos = l_player.GetPositon();
    int gridSize_x = m_windowSize.x / m_blockSize;
    int gridSize_y = m_windowSize.y / m_blockSize;
    
    if (playPos.x <= 0 || playPos.y <= 0 || playPos.x >= gridSize_x - 1 || playPos.y >= gridSize_y - 1) {
        l_player.Lose();
        return;
    }
    
    if (playPos == m_item) {
        l_player.Grow();
        l_player.IncreaseScore();
        RespawnApple();
    }
}

void World::Render(sf::RenderWindow &l_window)
{
    for (int i = 0; i < 4; i++) {
        l_window.draw(m_bounds[i]);
    }
    
    l_window.draw(m_appleShape);
}

int World::GetBlockSize()
{
    return m_blockSize;
}


