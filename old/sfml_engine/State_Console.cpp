//
//  State_Console.cpp
//  sfml_engine
//
//  Created by Robert Wells on 06/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#include "State_Console.hpp"
#include "StateManager.hpp"

State_Console::State_Console(StateManager& l_stateManager) : BaseState(l_stateManager), m_console(l_stateManager.GetContext().GetWindow()->GetRenderWindow(), *l_stateManager.GetContext().GetFontManager()){}

State_Console::~State_Console(){}

void State_Console::OnCreate()
{
    SetTrancendent(true);
    SetTransparent(true);
    
    
    m_console.Add("get_player", [this](std::vector<std::string> l) -> std::string{
        if(l[0] == "make"){
            
            /*
            Character* player = (Character*)GetStateManager().GetContext().GetEntityManager()->Find("Player");
            
            if(player){
                if(l[1] == "jump"){
                    player->Jump();
                    return "character jumped!";
                } else if(l[1] == "attack"){
                    player->Attack();
                    return "character attacked!";
                }
            }else{
                return "player not found";
            }
             */
            
        }
        
        return "get_player: invalid parameters";
        
    }, 2, 2, "make 'jump' 'attack'");

    EventManager* evMgr = GetStateManager().GetContext().GetEventManager();
    evMgr->AddCallback(StateType::Console, "Key_Tilde", &State_Console::Close, this);
    evMgr->AddCallback(StateType::Console, "Text_Entered", &Console::HandleTextInput, &m_console);
    evMgr->AddCallback(StateType::Console, "Key_Return", &Console::ValidateInput, &m_console);
    evMgr->AddCallback(StateType::Console, "Key_Backspace", &Console::Backspace, &m_console);
    evMgr->AddCallback(StateType::Console, "Key_Up", &Console::CycleInputUp, &m_console);
    evMgr->AddCallback(StateType::Console, "Key_Down", &Console::CycleInputDown, &m_console);
    evMgr->AddCallback(StateType::Console, "Key_Left", &Console::MoveCursorLeft, &m_console);
    evMgr->AddCallback(StateType::Console, "Key_Right", &Console::MoveCursorRight, &m_console);
    evMgr->AddCallback(StateType::Console, "Key_PageUp", &Console::ScrollOutputUp, &m_console);
    evMgr->AddCallback(StateType::Console, "Key_PageDown", &Console::ScrollOutputDown, &m_console);
    //evMgr->AddCallback(StateType::Console, "Key_Shift", &State_Console::OpenFull, this);
}

void State_Console::OnDestroy()
{
    EventManager* evMgr = GetStateManager().GetContext().GetEventManager();
    evMgr->RemoveCallback(StateType::Console, "Key_Tilde");
    evMgr->RemoveCallback(StateType::Console, "Text_Entered");
    evMgr->RemoveCallback(StateType::Console, "Key_Return");
    evMgr->RemoveCallback(StateType::Console, "Key_Up");
    evMgr->RemoveCallback(StateType::Console, "Key_Down");
    evMgr->RemoveCallback(StateType::Console, "Key_Left");
    evMgr->RemoveCallback(StateType::Console, "Key_Right");
    evMgr->RemoveCallback(StateType::Console, "Key_PageUp");
    evMgr->RemoveCallback(StateType::Console, "Key_PageDown");
    //evMgr->RemoveCallback(StateType::Console, "Key_Shift");
}

void State_Console::Activate()
{
    // Start showing console
    
    OpenHalf();
}

void State_Console::Deactivate()
{
   
}

void State_Console::Close(EventDetails* l_details)
{
     m_console.Close(2200);
}

void State_Console::Update(const sf::Time& l_time)
{
    // Update console loc
    
    m_console.Update(l_time.asSeconds());
    
    if(!m_console.IsOpen()){
        GetStateManager().SwitchTo(StateType::Game);
    }
}

void State_Console::Draw()
{
    m_console.Draw(GetStateManager().GetContext().GetWindow()->GetRenderWindow());
}

void State_Console::OpenHalf()
{
   m_console.Open(0.5, 1800);
}

void State_Console::OpenFull(EventDetails* l_details)
{
    m_console.Open(0.9, 1800);
}


