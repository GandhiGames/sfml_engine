//
//  State_Game.cpp
//  sfml_engine
//
//  Created by Robert Wells on 03/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "State_Game.hpp"
#include "StateManager.hpp"


State_Game::State_Game(StateManager &l_stateManager):BaseState(l_stateManager){}

State_Game::~State_Game(){}

void State_Game::OnCreate()
{
    m_texture.loadFromFile(resourcePath() + "Mushroom.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(0, 0);
    
    m_increment = sf::Vector2f(400.0f, 400.0f);
    
    EventManager* evMgr = GetStateManager().GetContext().GetEventManager();
    
    evMgr->AddCallback(StateType::Game, "Key_escape", &State_Game::MainMenu, this);
    evMgr->AddCallback(StateType::Game, "Key_p", &State_Game::Pause, this);
}

void State_Game::OnDestroy()
{
    EventManager *evMgr = GetStateManager().GetContext().GetEventManager();
    
    evMgr->RemoveCallback(StateType::Game, "Key_escape");
    evMgr->RemoveCallback(StateType::Game, "Key_p");
}

void State_Game::Activate(){}
void State_Game::Deactivate(){}

void State_Game::Update(const sf::Time &l_time)
{
    sf::Vector2u l_windSize = GetStateManager().GetContext().GetWindow()->GetWindowSize();
    sf::Vector2u l_textSize = m_texture.getSize();
    
    if((m_sprite.getPosition().x > l_windSize.x - l_textSize.x && m_increment.x > 0) ||
       (m_sprite.getPosition().x < 0 && m_increment.x < 0))
    {
        m_increment.x = -m_increment.x;
    }
    
    if((m_sprite.getPosition().y > l_windSize.y - l_textSize.y && m_increment.y > 0) ||
       (m_sprite.getPosition().y < 0 && m_increment.y < 0))
    {
        m_increment.y = -m_increment.y;
    }
    
    m_sprite.setPosition(m_sprite.getPosition().x + (m_increment.x * l_time.asSeconds()),
                         m_sprite.getPosition().y + (m_increment.y * l_time.asSeconds()));
}

void State_Game::Draw()
{
    GetStateManager().GetContext().GetWindow()->GetRenderWindow()->draw(m_sprite);
}

void State_Game::MainMenu(EventDetails *l_detals)
{
    GetStateManager().SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails *l_details)
{
    GetStateManager().SwitchTo(StateType::Paused);
}