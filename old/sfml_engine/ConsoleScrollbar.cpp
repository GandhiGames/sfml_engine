//
//  ConsoleScrollbar.cpp
//  sfml_engine
//
//  Created by Robert Wells on 07/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#include "ConsoleScrollbar.hpp"


ConsoleScrollbar::ConsoleScrollbar()
{
    m_background.setFillColor(sf::Color(90, 90, 90, 90));
    m_scrollbar.setFillColor(sf::Color(90, 90, 90, 180));
}

ConsoleScrollbar::~ConsoleScrollbar(){}


void ConsoleScrollbar::Setup(const sf::Vector2f& l_topRight, const sf::Vector2f& l_size)
{
    m_background.setSize(l_size);
    m_background.setOrigin(m_background.getSize().x, 0);
    m_background.setPosition(l_topRight);
    
    m_scrollbar.setSize(sf::Vector2f(l_size.x, 40));
    m_scrollbar.setOrigin(0, m_scrollbar.getSize().y * 0.5);
    m_scrollbar.setPosition(m_background.getPosition().x - m_scrollbar.getSize().x, m_background.getPosition().y + m_background.getSize().y - m_scrollbar.getSize().y * 0.5);
}

void ConsoleScrollbar::Draw(sf::RenderWindow* l_wind)
{
    l_wind->draw(m_background);
    l_wind->draw(m_scrollbar);
}

void ConsoleScrollbar::SetScrollPercent(const float& l_perc)
{
    std::cout << "perc:" << l_perc << std::endl;
    assert(l_perc >= 0 && l_perc <= 100);
    
    if(l_perc == 0){
        m_scrollbar.setPosition(m_scrollbar.getPosition().x, m_background.getPosition().y + m_scrollbar.getSize().y * 0.5);
        return;
    }else if(l_perc == 100){
         m_scrollbar.setPosition(m_scrollbar.getPosition().x, m_background.getPosition().y + m_background.getSize().y - m_scrollbar.getSize().y * 0.5);
        return;
    }
    
    float min = m_background.getPosition().y;
    float max = m_background.getPosition().y + m_background.getSize().y;

    
    float y = ((max - min) * (l_perc / 100.0)) + min;
    
    
    // Clamp
    if(m_background.getPosition().y + y < m_scrollbar.getSize().y * 0.5){
        y = m_background.getPosition().y + m_scrollbar.getSize().y * 0.5;
    }else if(m_background.getPosition().y + m_background.getSize().y - y < m_scrollbar.getSize().y * 0.5){
        y = m_background.getPosition().y + m_background.getSize().y - m_scrollbar.getSize().y * 0.5;
    }
    
    m_scrollbar.setPosition(m_scrollbar.getPosition().x, y);
}
