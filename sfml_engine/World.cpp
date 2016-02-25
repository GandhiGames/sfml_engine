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
        m_bounds[i].setFillColor(sf::Color(1, 50, 0, 0));
 
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
    
}
