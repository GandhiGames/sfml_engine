//
//  Game.cpp
//  sfml_engine
//
//  Created by Robert Wells on 23/02/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "Game.hpp"

//TODO(robert): Seperate media files and data files in asset folder i.e. assets/media and assets/data
Game::Game():
    m_window("engine_test", sf::Vector2u(800, 600)),m_stateManager(m_context),
        m_entityManager(&m_systemManager, &m_textureManager),
        m_debugText(m_fontManager),
        m_uiManager(m_window.GetEventManager(), &m_context)
{
    m_clock.restart();
    srand((unsigned)time(nullptr));
    
    m_context.SetWindow(&m_window);
    m_context.SetEventManager(m_window.GetEventManager());
    m_context.SetTextureManager(&m_textureManager);
    m_context.SetFontManager(&m_fontManager);
    m_context.SetEntityManager(&m_entityManager);
    m_systemManager.SetEntityManager(&m_entityManager);
    m_context.SetSystemManager(&m_systemManager);
    m_debugOverlay.SetDebug(true);
    m_context.SetDebugOverlay(&m_debugOverlay);
    m_context.SetDebugText(&m_debugText);
    m_context.SetUIManager(&m_uiManager);
    
    m_stateManager.SwitchTo(StateType::Intro);
    
    GetWindow()->GetRenderWindow()->setFramerateLimit(120);

    //TODO(robert): Implement font acquisition in UI_Manager when font loaded.
    m_fontManager.RequireResource("Default");
}

Game::~Game()
{
    m_fontManager.ReleaseResource("Default");
}

sf::Time Game::GetElapsed(){ return m_clock.getElapsedTime(); }
void Game::RestartClock(){ m_elapsed = m_clock.restart(); }
Window* Game::GetWindow(){ return &m_window; }

void Game::Update(){
    m_window.Update();
    m_stateManager.Update(m_elapsed);
    
    m_context.GetUIManager()->Update(m_elapsed.asSeconds());
    
    UI_Event uiEvent;
    
    while(m_context.GetUIManager()->PollEvent(uiEvent)){
        m_window.GetEventManager()->HandleEvent(uiEvent);
    }
}

void Game::Render(){
    m_window.BeginDraw();
    
    // Render here.
    m_stateManager.Draw();
    
    // UI.
    sf::View currentView = m_window.GetRenderWindow()->getView();
    m_window.GetRenderWindow()->setView(m_window.GetRenderWindow()->getDefaultView());
    m_context.GetUIManager()->Render(m_window.GetRenderWindow());
    m_window.GetRenderWindow()->setView(currentView);
    
    
    // Debug.
    if(m_context.GetDebugOverlay()->Debug()){
        m_context.GetDebugOverlay()->Draw(m_window.GetRenderWindow());
    }
    
    m_context.GetDebugText()->Render(m_window.GetRenderWindow());
    
    
    m_window.EndDraw();
}

void Game::LateUpdate(){
    m_stateManager.ProcessRequests();
    RestartClock();
    
    //m_fps.Update();
    //m_debugText.Add(std::to_string(m_fps.getFPS()));
}
