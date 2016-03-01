//
//  Game.cpp
//  sfml_engine
//
//  Created by Robert Wells on 23/02/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "Game.hpp"


Game::Game():m_window("engine_test", sf::Vector2u(800, 600)), m_snake(m_world.GetBlockSize()), m_world(sf::Vector2u(800, 600))
{
   // m_clock.restart();
    
   // m_elapsed = 0.0f;
    
    //	srand(time(nullptr));
    
   // m_textbox.Setup(5, 14, 350, sf::Vector2f(50, 50));
   // m_textbox.Add("Seeded random number generator with: " + std::to_string(time(nullptr)));
    m_mushroomTexture.loadFromFile(resourcePath() + "Mushroom.png");
    m_mushroomSprite.setTexture(m_mushroomTexture);
    m_mushroomSprite.setOrigin(m_mushroomTexture.getSize().x * 0.5f, m_mushroomTexture.getSize().y * 0.5f);
    
    m_window.GetEventManager().AddCallback("Move", &Game::MoveSprite, this);
}

Game::~Game(){}

void Game::Update()
{
    m_window.Update();

   /* float timeStep = 1.0f / m_snake.GetSpeed();
    
    if (m_elapsed >= timeStep) {
        m_snake.Tick();
        m_world.Update(m_snake);
        
        m_elapsed -= timeStep;
        
        if (m_snake.HasLost()) {
            m_textbox.Add("Game Over");
            m_snake.Reset();
        }
    } */
}

void Game::MoveSprite(EventDetails *l_details)
{
    sf::Vector2i mousePos = m_window.GetEventManager().GetMousePosition(&m_window.GetRenderWindow());
    m_mushroomSprite.setPosition(mousePos.x, mousePos.y);
    
}

void Game::Render()
{
    m_window.BeginDraw();
   /* m_world.Render(m_window.GetRenderWindow());
    m_snake.Render(m_window.GetRenderWindow()); */
    m_window.Draw(m_mushroomSprite);
    m_textbox.Render(m_window.GetRenderWindow());
    m_window.EndDraw();
}

const Window & Game::GetWindow()
{
    return m_window;
}

void Game::HandleInput()
{
   /* Direction l_dir = m_snake.GetPhysicalDirection();
    
   	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
       && l_dir != Direction::Down){
        m_snake.SetDirection(Direction::Up);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
              && l_dir != Direction::Up){
        m_snake.SetDirection(Direction::Down);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
              && l_dir != Direction::Right){
        m_snake.SetDirection(Direction::Left);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
              && l_dir!= Direction::Left){
        m_snake.SetDirection(Direction::Right);
    } */
}

sf::Time Game::GetElapsed()
{
    return m_clock.getElapsedTime();
}

void Game::RestartClock()
{
    m_elapsed += m_clock.restart().asSeconds();
}
