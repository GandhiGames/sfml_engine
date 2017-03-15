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

void State_Menu::OnCreate()
{
    UI_Manager* ui = GetStateManager().GetContext().GetUIManager();

    ui->LoadInterface(StateType::MainMenu, "MainMenu.interface", "MainMenu");
    ui->GetInterface(StateType::MainMenu, "MainMenu")->SetPosition(sf::Vector2f(250.0f, 168.0f));

    EventManager* evtMgr = GetStateManager().GetContext().GetEventManager();
    evtMgr->AddCallback(StateType::MainMenu, "MainMenu_Play", &State_Menu::Play, this);
    evtMgr->AddCallback(StateType::MainMenu, "MainMenu_Quit", &State_Menu::Quit, this);       
}

void State_Menu::OnDestroy()
{
    GetStateManager().GetContext().GetUIManager()->RemoveInterface(
        StateType::MainMenu, "MainMenu");

    EventManager* evtMgr = GetStateManager().GetContext().GetEventManager();
    evtMgr->RemoveCallback(StateType::MainMenu, "MainMenu_Play");
    evtMgr->RemoveCallback(StateType::MainMenu, "MainMenu_Quit");
}

void State_Menu::Activate()
{
    auto& play = *GetStateManager().GetContext().GetUIManager()->GetInterface(
        StateType::MainMenu, "MainMenu")->GetElement("Play");

    if(GetStateManager().HasState(StateType::Game))
    {
        play.SetText("Resume");
    }
    else
    {
        play.SetText("Play");
    }
}

void State_Menu::Deactivate(){}
void State_Menu::Update(const sf::Time &l_time){}

void State_Menu::Draw(){}

void State_Menu::Play(EventDetails* l_details)
{
    GetStateManager().SwitchTo(StateType::Game);
}

void State_Menu::Quit(EventDetails* l_Details)
{
    GetStateManager().GetContext().GetWindow()->Close();
}

/*
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
        GetStateManager().SwitchTo(StateType::Game);
    } else if (m_selectedIndex == 1) {
        // Load info.
    } else if (m_selectedIndex == 2) {
        GetStateManager().GetContext().GetWindow()->Close();
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
*/
