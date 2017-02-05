//
//  State_Paused.cpp
//  sfml_engine
//
//  Created by Robert Wells on 03/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "State_Paused.hpp"
#include "StateManager.hpp"

State_Paused::State_Paused(StateManager &l_stateManager):BaseState(l_stateManager){}

State_Paused::~State_Paused(){}

void State_Paused::OnCreate()
{
    SetTransparent(true);
    
    m_font.loadFromFile(resourcePath() + "media/Fonts/arial.ttf");
    m_text.setFont(m_font);
    m_text.setFillColor(sf::Color::Black);
    m_text.setString(sf::String("PAUSED"));
    m_text.setCharacterSize(14);
    m_text.setStyle(sf::Text::Bold);
    
    
    
    sf::Vector2u windowSize = GetStateManager().GetContext().GetWindow()->GetRenderWindow()->getSize();
    
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f,
                     textRect.top + textRect.height / 2.0f);
    m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
    
    m_rect.setSize(sf::Vector2f(windowSize));
    m_rect.setPosition(0,0);
    m_rect.setFillColor(sf::Color(0,0,0,150));
    
    GetStateManager().GetContext().GetEventManager()->AddCallback(StateType::Paused, "Key_P", &State_Paused::UnPause, this);
    
}

void State_Paused::OnDestroy()
{
    GetStateManager().GetContext().GetEventManager()->RemoveCallback(StateType::Paused, "Key_P");
}

void State_Paused::Activate(){}
void State_Paused::Deactivate(){}

void State_Paused::Update(const sf::Time &l_time){}

void State_Paused::Draw()
{
    sf::RenderWindow *window = GetStateManager().GetContext().GetWindow()->GetRenderWindow();
    
    window->draw(m_rect);
    window->draw(m_text);
}

void State_Paused::UnPause(EventDetails *l_details)
{
    GetStateManager().SwitchTo(StateType::Game);
}
