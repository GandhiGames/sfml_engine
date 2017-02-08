//
//  State_Menu.cpp
//  sfml_engine
//
//  Created by Robert Wells on 03/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "State_Menu.hpp"
#include "StateManager.hpp"

State_Menu::State_Menu(StateManager& l_stateManager):BaseState(l_stateManager){}

State_Menu::~State_Menu(){}

//TODO: use resource manager to load fonts.
void State_Menu::OnCreate()
{
    
    FontManager* fntMngr = GetStateManager().GetContext().GetFontManager();
    
    if(fntMngr->RequireResource("Default")){
        m_text.setFont(*fntMngr->GetResource("Default"));
    }
    
    m_text.setString(sf::String("Main Menu"));
    m_text.setCharacterSize(24);
    
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f,
                     textRect.top + textRect.height / 2.0f);
    
    const sf::Vector2u& windSize = m_stateManager.GetContext().GetWindow()->GetRenderWindow()->getSize();
    
    m_text.setPosition(windSize.x * 0.5, 100);
    m_text.setFillColor(sf::Color::Black);
    
    m_buttonSize = sf::Vector2f(300.0f, 32.0f);
    m_buttonPos = sf::Vector2f(windSize.x * 0.5, 200);
    m_buttonPadding = 4; // 4px.
    
    std::string str[3];
    str[0] = "PLAY";
    str[1] = "CREDITS";
    str[2] = "EXIT";
    
    for(int i = 0; i < 3; ++i){
        sf::Vector2f buttonPosition(m_buttonPos.x,m_buttonPos.y +
                                    (i * (m_buttonSize.y + m_buttonPadding)));
        m_rects[i].setSize(m_buttonSize);
        m_rects[i].setFillColor(sf::Color::Red);
        
        m_rects[i].setOrigin(m_buttonSize.x / 2.0f, m_buttonSize.y / 2.0f);
        m_rects[i].setPosition(buttonPosition);
        
        m_labels[i].setFont(*GetStateManager().GetContext().GetFontManager()->GetResource("Default"));
        m_labels[i].setString(sf::String(str[i]));
        m_labels[i].setCharacterSize(16);
        
        sf::FloatRect rect = m_labels[i].getLocalBounds();
        m_labels[i].setOrigin(rect.left + rect.width / 2.0f,
                              rect.top + rect.height / 2.0f);
        
        m_labels[i].setPosition(buttonPosition);
    }

    m_selectedIndex = 0;
    m_labels[m_selectedIndex].setFillColor(sf::Color::Black);
    m_labels[m_selectedIndex].setStyle(sf::Text::Bold);
    
    EventManager* evtMgr = GetStateManager().GetContext().GetEventManager();
    evtMgr->AddCallback(StateType::MainMenu, "Key_Up", &State_Menu::MenuSelectionUp, this);
    evtMgr->AddCallback(StateType::MainMenu, "Key_Down", &State_Menu::MenuSelectionDown, this);
    evtMgr->AddCallback(StateType::MainMenu, "Key_Return", &State_Menu::ValidateSelection, this);
    
}

void State_Menu::OnDestroy()
{
    EventManager* evtMgr = GetStateManager().GetContext().GetEventManager();
    evtMgr->RemoveCallback(StateType::MainMenu, "Key_Up");
    evtMgr->RemoveCallback(StateType::MainMenu, "Key_Down");
    evtMgr->RemoveCallback(StateType::MainMenu, "Key_Return");
    
    GetStateManager().GetContext().GetFontManager()->ReleaseResource("Default");
}

void State_Menu::Activate()
{
    if (m_stateManager.HasState(StateType::Game)
        && m_labels[0].getString() != "RESUME")
    {
        m_labels[0].setString(sf::String("RESUME"));
    } else {
        m_labels[0].setString(sf::String("PLAY"));
    }
    
    sf::FloatRect rect = m_labels[0].getLocalBounds();
    m_labels[0].setOrigin(rect.left + rect.width / 2.0f,
                          rect.top + rect.height / 2.0f);
}

void State_Menu::Deactivate(){}
void State_Menu::Update(const sf::Time &l_time){}

void State_Menu::Draw()
{
    sf::RenderWindow *window = GetStateManager().GetContext().GetWindow()->GetRenderWindow();
    
    window->draw(m_text);
    
    for(int i = 0; i < 3; ++i){
        window->draw(m_rects[i]);
        window->draw(m_labels[i]);
    }
}

void State_Menu::MenuSelectionUp(EventDetails* l_details)
{
    IncrementSelect(-1);
}

void State_Menu::MenuSelectionDown(EventDetails* l_details)
{
    IncrementSelect(1);
}

void State_Menu::ValidateSelection(EventDetails* l_details)
{
    if(m_selectedIndex == 0) {
        m_stateManager.SwitchTo(StateType::Game);
    } else if (m_selectedIndex == 1) {
        // Load info.
    } else if (m_selectedIndex == 2) {
        m_stateManager.GetContext().GetWindow()->Close();
    }
}

void State_Menu::IncrementSelect(const sf::Int8& l_increment)
{
    assert(l_increment == -1 || l_increment == 1);
    
    m_labels[m_selectedIndex].setStyle(sf::Text::Regular);
    m_labels[m_selectedIndex].setFillColor(sf::Color::White);
    
    if(l_increment < 0){
        if(m_selectedIndex > 0) {
            m_selectedIndex += l_increment;
        } else {
            m_selectedIndex = 2;
        }
    }else{
        m_selectedIndex = (m_selectedIndex + l_increment) % 3;
    }
    
    m_labels[m_selectedIndex].setFillColor(sf::Color::Black);
    m_labels[m_selectedIndex].setStyle(sf::Text::Bold);
}
