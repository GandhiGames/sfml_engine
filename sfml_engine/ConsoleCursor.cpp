//
//  ConsoleCursor.cpp
//  sfml_engine
//
//  Created by Robert Wells on 06/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#include "ConsoleCursor.hpp"

ConsoleCursor::ConsoleCursor(const float& l_blinkDelay)
{
    m_cursor.setFillColor(sf::Color(40, 40, 90, 120));
    m_blinkDelay = l_blinkDelay;
    
    m_show = true;
}

ConsoleCursor::~ConsoleCursor(){}

void ConsoleCursor::Update(const float& l_dt)
{
    m_timeAccum += l_dt;
    
    if(m_timeAccum >= m_blinkDelay){
        m_timeAccum = 0;
        m_show = !m_show;
    }
}

void ConsoleCursor::Draw(sf::RenderWindow* l_wind)
{
    if(m_show){
        l_wind->draw(m_cursor);
    }
}

void ConsoleCursor::SetPosition(const sf::Vector2f& l_pos)
{
     m_cursor.setPosition(l_pos);
}

const sf::Vector2f& ConsoleCursor::GetPosition()
{
    return m_cursor.getPosition();
}

void ConsoleCursor::SetX(const float& l_x)
{
    m_cursor.setPosition(l_x, m_cursor.getPosition().y);
}

void ConsoleCursor::SetSize(const sf::Vector2f& l_size)
{
    m_cursor.setSize(l_size);
}

const sf::Vector2f& ConsoleCursor::GetSize()
{
    return m_cursor.getSize();
}
