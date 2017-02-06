//
//  Game.cpp
//  sfml_engine
//
//  Created by Robert Wells on 23/02/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "Game.hpp"

Game::Game():
    m_window("engine_test", sf::Vector2u(800, 600)),m_stateManager(m_context),
        m_entityManager(&m_context, 100)
{
    m_clock.restart();
    srand(time(nullptr));
    
    m_context.SetWindow(&m_window);
    m_context.SetEventManager(m_window.GetEventManager());
    m_context.SetTextureManager(&m_textureManager);
    m_context.SetEntityManager(&m_entityManager);
    m_debugOverlay.SetDebug(true);
    m_context.SetDebugOverlay(&m_debugOverlay);
    m_context.SetDebugText(&m_debugText);
    
    m_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game(){ }

sf::Time Game::GetElapsed(){ return m_clock.getElapsedTime(); }
void Game::RestartClock(){ m_elapsed = m_clock.restart(); }
Window* Game::GetWindow(){ return &m_window; }

void Game::Update(){
    m_window.Update();
    m_stateManager.Update(m_elapsed);
}

void Game::Render(){
    m_window.BeginDraw();
    
    // Render here.
    m_stateManager.Draw();
    
    // Debug.
    if(m_context.GetDebugOverlay()->Debug()){
        m_context.GetDebugOverlay()->Draw(m_window.GetRenderWindow());
    }
    
    if(m_context.GetDebugText()){
        m_context.GetDebugText()->Render(m_window.GetRenderWindow());
    }
    
    m_window.EndDraw();
}

void Game::LateUpdate(){
    m_stateManager.ProcessRequests();
    RestartClock();
}
