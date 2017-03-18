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
    sf::Vector2u windowSize = GetStateManager().GetContext()
    .GetWindow()->GetRenderWindow()->getSize();
    
    TextureManager* textureMgr = GetStateManager().GetContext().GetTextureManager();
    
    textureMgr->RequireResource("Intro");
    sf::Texture* introSprite = textureMgr->GetResource("Intro");
    
    m_introSprite.setTexture(*introSprite);
    m_introSprite.setOrigin(introSprite->getSize().x / 2.0f,
                            introSprite->getSize().y / 2.0f);
    
    m_introSprite.setPosition(windowSize.x * 0.5f, windowSize.y * 0.5f);
    
    
    FontManager* fntMngr = GetStateManager().GetContext().GetFontManager();
    
    if(fntMngr->RequireResource("Default")){
        m_text.setFont(*fntMngr->GetResource("Default"));
    }
    m_text.setFillColor(sf::Color::Black);
    m_text.setString({ "Press SPACE to continue" });
    m_text.setCharacterSize(15);
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f,
                     textRect.top + textRect.height / 2.0f);
    m_text.setPosition(m_introSprite.getPosition().x,
                       m_introSprite.getPosition().y + textureMgr->GetResource("Intro")->getSize().y / 1.5f);
    
   GetStateManager().GetContext().GetEventManager()->AddCallback(StateType::Intro,"Intro_continue",&State_Intro::Continue,this);

   GetStateManager().GetContext().GetSoundManager()->PlayMusic("Electrix", 100.0f, true);
}

void State_Intro::OnDestroy()
{
    GetStateManager().GetContext().GetTextureManager()->ReleaseResource("Intro");
    
    GetStateManager().GetContext().GetEventManager()->RemoveCallback(StateType::Intro, "Intro_continue");
    
    GetStateManager().GetContext().GetFontManager()->ReleaseResource("Default");
}

void State_Intro::Draw()
{
    sf::RenderWindow* window = GetStateManager().
    GetContext().GetWindow()->GetRenderWindow();
    
    window->draw(m_introSprite);
    window->draw(m_text);
}

void State_Intro::Continue(EventDetails *l_details)
{
    GetStateManager().SwitchTo(StateType::MainMenu);
    GetStateManager().Remove(StateType::Intro);
}

void State_Intro::Activate(){}
void State_Intro::Deactivate(){}
void State_Intro::Update(const sf::Time &l_time){}
