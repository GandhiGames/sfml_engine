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

void ConsoleScrollbar::SetSize(const sf::Vector2f& l_backSize, const sf::Vector2f& l_scrollSize)
{
    m_background.setSize(l_backSize);
    m_scrollbar.setSize(l_scrollSize);
}

void ConsoleScrollbar::Draw(sf::RenderWindow* l_wind)
{
    l_wind->draw(m_background);
    l_wind->draw(m_scrollbar);
}
