//
//  Textbox.cpp
//  sfml_engine
//
//  Created by Robert Wells on 27/02/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "Textbox.hpp"


const sf::Vector2f Textbox::OFFSET = sf::Vector2f(2.0f, 2.0f);
const sf::Vector2f Textbox::DEFAULT_POSITION = sf::Vector2f(0, 0);
const sf::Color Textbox::DEFAULT_FONT_COLOUR = sf::Color::White;

Textbox::Textbox(FontManager& l_fontManager) : m_fontManager(l_fontManager)
{
    Setup(DEFAULT_LINES_VISIBLE, DEFAULT_CHAR_SIZE, DEFAULT_WIDTH, DEFAULT_POSITION);
}

Textbox::Textbox(int l_visible, int l_charSize, int l_width, const sf::Vector2f & l_screenPos, FontManager& l_fontManager) : m_fontManager(l_fontManager)
{
    Setup(l_visible, l_charSize, l_width, l_screenPos);
}

Textbox::~Textbox()
{
    m_fontManager.ReleaseResource("Default");
    Clear();
}

//TODO: create correct resource request for font.
void Textbox::Setup(int l_visible, int l_charSize, int l_width, const sf::Vector2f &l_screenPos)
{
    m_numLinesVisible = l_visible;
    
    if(m_fontManager.RequireResource("Default")){
        m_content.setFont(*m_fontManager.GetResource("Default"));
    }

    m_content.setString(" ");
    
    m_content.setCharacterSize(l_charSize);
    m_content.setFillColor(DEFAULT_FONT_COLOUR);
    
    m_content.setPosition(l_screenPos + OFFSET);
    
    m_background.setSize(sf::Vector2f(l_width, (l_visible * (l_charSize * LINE_SPACING))));
    m_background.setFillColor(sf::Color(90, 90, 90, 90));
    m_background.setPosition(l_screenPos);
}

void Textbox::Clear()
{
    m_messages.clear();
}

void Textbox::Render(sf::RenderWindow* l_window)
{
    if (m_messages.size() == 0) {
        return;
    }
    
    l_window->setView(m_view);
    std::string l_content;
    
    for (auto &itr : m_messages)
    {
        l_content.append(itr + "\n");
    }
    m_content.setString(l_content);
    l_window->draw(m_background);
    l_window->draw(m_content);
    
    
}

void Textbox::Add(std::string l_message)
{
    m_messages.push_back(l_message);
    if (m_messages.size() < m_numLinesVisible) {
        return;
    }
    
    m_messages.erase(m_messages.begin());
}
