//
//  State_Console.cpp
//  sfml_engine
//
//  Created by Robert Wells on 06/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#include "State_Console.hpp"
#include "StateManager.hpp"

State_Console::State_Console(StateManager& l_stateManager) : BaseState(l_stateManager), m_console(l_stateManager.GetContext().GetWindow()->GetRenderWindow()){}

State_Console::~State_Console(){}

void State_Console::OnCreate()
{
    SetTrancendent(true);
    SetTransparent(true);
    
    m_stateManager.GetContext().SetConsole(&m_console);
    
    EventManager* evMgr = m_stateManager.GetContext().GetEventManager();
    
    
    evMgr->AddCallback(StateType::Console, "Key_Tilde", &State_Console::Close, this);
    evMgr->AddCallback(StateType::Console, "Text_Entered", &Console::HandleTextInput, &m_console);
    evMgr->AddCallback(StateType::Console, "Key_Return", &Console::ValidateInput, &m_console);
    evMgr->AddCallback(StateType::Console, "Key_Backspace", &Console::Backspace, &m_console);
    evMgr->AddCallback(StateType::Console, "Key_Up", &Console::CycleInputUp, &m_console);
    evMgr->AddCallback(StateType::Console, "Key_Down", &Console::CycleInputDown, &m_console);
}

void State_Console::OnDestroy()
{
    EventManager* evMgr = m_stateManager.GetContext().GetEventManager();
    evMgr->RemoveCallback(StateType::Console, "Key_Tilde");
    evMgr->RemoveCallback(StateType::Console, "Text_Entered");
    evMgr->RemoveCallback(StateType::Console, "Key_Return");
    evMgr->RemoveCallback(StateType::Console, "Key_Up");
    evMgr->RemoveCallback(StateType::Console, "Key_Down");
    
    m_stateManager.GetContext().SetConsole(nullptr);
}

void State_Console::Activate()
{
    // Start showing console
    
    m_console.Open();
}

void State_Console::Deactivate()
{

}

void State_Console::Close(EventDetails* l_details)
{
    m_console.Close();
}

void State_Console::Update(const sf::Time& l_time)
{
    // Update console loc
    
    m_console.Update(l_time.asSeconds());
    
    if(!m_console.IsOpen()){
        m_stateManager.SwitchTo(StateType::Game);
    }
}

void State_Console::Draw()
{
    sf::RenderWindow* wind = m_stateManager.GetContext().GetWindow()->GetRenderWindow();
    

    
    m_console.Draw(wind);

}


