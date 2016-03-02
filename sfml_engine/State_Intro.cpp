//
//  Intro_State.cpp
//  sfml_engine
//
//  Created by Robert Wells on 02/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "State_Intro.hpp"
#include "StateManager.hpp"

State_Intro::State_Intro(StateManager &l_stateManager):BaseState(l_stateManager){}

State_Intro::~State_Intro(){}

void State_Intro::OnCreate()
{
    printf("Here");
    m_timePassed = 0.0f;
    
    sf::Vector2u windowSize = GetStateManager().GetContext().GetWindow()->GetRenderWindow().getSize();
    
    m_introTexture.loadFromFile(resourcePath() + "intro.png");
    m_introSprite.setTexture(m_introTexture);
    m_introSprite.setOrigin(m_introTexture.getSize().x / 2.0f,
                            m_introTexture.getSize().y / 2.0f);
    
    m_introSprite.setPosition(windowSize.x / 2.0f, 0);
    
    m_font.loadFromFile(resourcePath() + "arial.ttf");
    m_text.setFont(m_font);
    m_text.setString({ "Press SPACE to continue" });
    m_text.setCharacterSize(15);
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f,
                     textRect.top + textRect.height / 2.0f);
    m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
    
    EventManager* evMgr = GetStateManager().GetContext().GetEventManager();
    evMgr->AddCallback(StateType::Intro,"Intro_Continue",&State_Intro::Continue,this);
}

void State_Intro::OnDestroy()
{
    GetStateManager().GetContext().GetEventManager()->RemoveCallback(StateType::Intro, "Intro_continue");
}

void State_Intro::Activate(){}

void State_Intro::Deactivate(){}

void State_Intro::Update(const sf::Time &l_time)
{
    if (m_timePassed < 5.0f) {
        m_timePassed += l_time.asSeconds();
        
        m_introSprite.setPosition(m_introSprite.getPosition().x, m_introSprite.getPosition().y + (48 * l_time.asSeconds()));
    }
}

void State_Intro::Draw()
{
    sf::RenderWindow window = GetStateManager().GetContext().GetWindow()->GetRenderWindow();
    
    window.draw(m_introSprite);
    
    if (m_timePassed >= 5.0f) {
        window.draw(m_text);
    }
}

void State_Intro::Continue(EventDetails *l_details)
{
    if (m_timePassed >= 5.0f) {
        GetStateManager().SwitchTo(StateType::MainMenu);
        GetStateManager().Remove(StateType::Intro);
    }
}