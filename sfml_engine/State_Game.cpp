//
//  State_Game.cpp
//  sfml_engine
//
//  Created by Robert Wells on 03/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "State_Game.hpp"
#include "StateManager.hpp"

State_Game::State_Game(StateManager& l_stateManager)
: BaseState(l_stateManager){}

State_Game::~State_Game(){}

void State_Game::OnCreate(){
    EventManager* evMgr = m_stateManager.
    GetContext().GetEventManager();
    
    evMgr->AddCallback(StateType::Game,"Key_Escape",&State_Game::MainMenu,this);
    evMgr->AddCallback(StateType::Game, "Key_O", &State_Game::ToggleOverlay, this);
    evMgr->AddCallback(StateType::Game, "Player_MoveLeft", &State_Game::PlayerMove, this);
    evMgr->AddCallback(StateType::Game, "Player_MoveRight", &State_Game::PlayerMove, this);
    evMgr->AddCallback(StateType::Game, "Player_MoveUp", &State_Game::PlayerMove, this);
    evMgr->AddCallback(StateType::Game, "Player_MoveDown", &State_Game::PlayerMove, this);
    evMgr->AddCallback(StateType::Game, "Key_Tilde", &State_Game::OpenConsole, this);
    
    sf::Vector2u size = m_stateManager.GetContext().GetWindow()->GetWindowSize();
    m_view.setSize(size.x,size.y);
    m_view.setCenter(size.x/2,size.y/2);
    m_view.zoom(0.6f);
    m_stateManager.GetContext().GetWindow()->GetRenderWindow()->setView(m_view);
    
    m_gameMap = new Map(&m_stateManager.GetContext()/*, this*/);
    m_gameMap->LoadMap("media/Maps/map1.map");
    
    //EntityManager* entities = m_stateManager.GetContext().GetEntityManager();
    //m_stateMgr->GetContext()->m_systemManager->GetSystem<S_Collision>(System::Collision)->SetMap(m_gameMap);
    m_stateManager.GetContext().GetSystemManager()->GetSystem<S_Movement>(System::Movement)->SetMap(m_gameMap);
    m_player = m_gameMap->GetPlayerId();
}

void State_Game::OnDestroy(){
    EventManager* evMgr = m_stateManager.GetContext().GetEventManager();
    evMgr->RemoveCallback(StateType::Game, "Key_Escape");
    evMgr->RemoveCallback(StateType::Game, "Key_O");
    evMgr->RemoveCallback(StateType::Game, "Player_MoveLeft");
    evMgr->RemoveCallback(StateType::Game, "Player_MoveRight");
   // evMgr->RemoveCallback(StateType::Game, "Player_MoveUp");
   // evMgr->RemoveCallback(StateType::Game, "Player_MoveDown");
    evMgr->RemoveCallback(StateType::Game, "Key_Tilde");
    
    delete m_gameMap;
    m_gameMap = nullptr;
}

void State_Game::Update(const sf::Time& l_time){
    SharedContext* context = &m_stateManager.GetContext();
    UpdateCamera();
    m_gameMap->Update(l_time.asSeconds());
    context->GetSystemManager()->Update(l_time.asSeconds());
}

void State_Game::UpdateCamera(){
    if (m_player == -1){ return; }
    SharedContext* context = &m_stateManager.GetContext();
    C_Position* pos = m_stateManager.GetContext().GetEntityManager()->GetComponent<C_Position>(m_player, Component::Position);
    
    m_view.setCenter(pos->GetPosition());
    context->GetWindow()->GetRenderWindow()->setView(m_view);
    
    sf::FloatRect viewSpace = context->GetWindow()->GetViewSpace();
    if (viewSpace.left <= 0){
        m_view.setCenter(viewSpace.width / 2, m_view.getCenter().y);
        context->GetWindow()->GetRenderWindow()->setView(m_view);
    } else if (viewSpace.left + viewSpace.width > (m_gameMap->GetMapSize().x) * Sheet::Tile_Size){
        m_view.setCenter(((m_gameMap->GetMapSize().x) * Sheet::Tile_Size) - (viewSpace.width / 2), m_view.getCenter().y);
        context->GetWindow()->GetRenderWindow()->setView(m_view);
    }
    
    if (viewSpace.top <= 0){
        m_view.setCenter(m_view.getCenter().x, viewSpace.height / 2);
        context->GetWindow()->GetRenderWindow()->setView(m_view);
    } else if (viewSpace.top + viewSpace.height > (m_gameMap->GetMapSize().y) * Sheet::Tile_Size){
        m_view.setCenter(m_view.getCenter().x, ((m_gameMap->GetMapSize().y) * Sheet::Tile_Size) - (viewSpace.height / 2));
        context->GetWindow()->GetRenderWindow()->setView(m_view);
    }
}

void State_Game::Draw(){
    for(unsigned int i = 0; i < Sheet::Num_Layers; ++i){
        m_gameMap->Draw(i);
        m_stateManager.GetContext().GetSystemManager()->Draw(
                                                        m_stateManager.GetContext().GetWindow(), i);
    }
}

void State_Game::MainMenu(EventDetails* l_details){
    m_stateManager.SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails* l_details){
    m_stateManager.SwitchTo(StateType::Paused);
}

void State_Game::Activate(){}

void State_Game::Deactivate(){}

void State_Game::PlayerMove(EventDetails* l_details){
    Message msg((MessageType)EntityMessage::Move);
    if (l_details->GetName() == "Player_MoveLeft"){
        msg.m_int = (int)Direction::Left;
    } else if (l_details->GetName() == "Player_MoveRight"){
        msg.m_int = (int)Direction::Right;
    } /*else if (l_details->m_name == "Player_MoveUp"){
        msg.m_int = (int)Direction::Up;
    } else if (l_details->m_name == "Player_MoveDown"){
        msg.m_int = (int)Direction::Down;
    }*/
    
    msg.m_receiver = m_player;
    m_stateManager.GetContext().GetSystemManager()->GetMessageHandler()->Dispatch(msg);
}

// Test/debug methods.
void State_Game::ToggleOverlay(EventDetails* l_details)
{
    m_stateManager.GetContext().GetDebugOverlay()->SetDebug(!m_stateManager.GetContext().GetDebugOverlay()->Debug());
}

void State_Game::OpenConsole(EventDetails* l_details)
{
    m_stateManager.SwitchTo(StateType::Console);
}
