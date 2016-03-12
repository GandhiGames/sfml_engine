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
    EventManager* evMgr = m_stateManager.GetContext().GetEventManager();
    
    evMgr->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
    evMgr->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
    evMgr->AddCallback(StateType::Game, "Key_O", &State_Game::ToggleOverlay, this);
    
    sf::Vector2u size = m_stateManager.GetContext().GetWindow()->GetWindowSize();
    m_view.setSize(size.x,size.y);
    m_view.setCenter(size.x/2,size.y/2);
    m_view.zoom(0.6f);
    m_stateManager.GetContext().GetWindow()->GetRenderWindow()->setView(m_view);
    
    m_gameMap = new Map(m_stateManager.GetContext(), *this);
    m_gameMap->LoadMap("media/Maps/map1.map");
}

void State_Game::OnDestroy()
{
    EventManager *evMgr = GetStateManager().GetContext().GetEventManager();
    

    evMgr->RemoveCallback(StateType::Game, "Key_Escape");
    evMgr->RemoveCallback(StateType::Game, "Key_P");
    evMgr->RemoveCallback(StateType::Game, "Key_O");
    
    delete m_gameMap;
    m_gameMap = nullptr;
}

void State_Game::Activate(){}
void State_Game::Deactivate(){}

void State_Game::Update(const sf::Time &l_time)
{
    SharedContext &context = m_stateManager.GetContext();
    EntityBase *player = context.GetEntityManager()->Find("Player");
    if(!player){
        std::cout << "Respawning player..." << std::endl;
        context->m_entityManager->Add(EntityType::Player,"Player");
        player = context->m_entityManager->Find("Player");
        player->SetPosition(m_gameMap->GetPlayerStart());
    } else {
        m_view.setCenter(player->GetPosition());
        context->m_wind->GetRenderWindow()->setView(m_view);
    }
    
    sf::FloatRect viewSpace = context->m_wind->GetViewSpace();
    if(viewSpace.left <= 0){
        m_view.setCenter(viewSpace.width / 2,m_view.getCenter().y);
        context->m_wind->GetRenderWindow()->setView(m_view);
    } else if (viewSpace.left + viewSpace.width > (m_gameMap->GetMapSize().x + 1) * Sheet::Tile_Size){
        m_view.setCenter(((m_gameMap->GetMapSize().x + 1) * Sheet::Tile_Size) - (viewSpace.width / 2), m_view.getCenter().y);
        context->m_wind->GetRenderWindow()->setView(m_view);
    }
    
    m_gameMap->Update(l_time.asSeconds());
    m_stateManager.GetContext().GetEntityManager()->Update(l_time.asSeconds());
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

// Test/debug methods.
void State_Game::ToggleOverlay(EventDetails* l_details){
    m_stateManager.GetContext().GetDebugOverlay()->SetDebug(!m_stateManager.GetContext().GetDebugOverlay()->Debug());
}