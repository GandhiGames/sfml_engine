//
//  Window.cpp
//  sfml_engine
//
//  Created by Robert Wells on 23/02/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "Window.hpp"

Window::Window()
{
    Setup("Window", sf::Vector2u(640, 800));
}

Window::Window (const std::string &l_title, const sf::Vector2u &l_size)
{
    Setup(l_title, l_size);
}

Window::~Window()
{
    Destroy();
}

void Window::Setup(const std::string &l_title, const sf::Vector2u &l_size)
{
    m_windowTitle = l_title;
    m_windowSize = l_size;
    m_isFullScreen = false;
    m_isDone = false;
    m_isFocused = true;
    
    m_eventManager.AddCallback("Fullscreen_toggle", &Window::ToggleFullScreen, this);
    m_eventManager.AddCallback("Window_close", &Window::Close, this);
    
    Create();
}

void Window::Create()
{
    auto style = (m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
    
    m_window.create({m_windowSize.x, m_windowSize.y, 32}, m_windowTitle, style);
}

void Window::Destroy()
{
    m_window.close();
}

void Window::Update()
{
   	sf::Event event;
    
    while(m_window.pollEvent(event)){
        if (event.type == sf::Event::LostFocus){ m_isFocused = false; m_eventManager.SetFocus(false); }
        else if (event.type == sf::Event::GainedFocus){ m_isFocused = true; m_eventManager.SetFocus(true); }
        m_eventManager.HandleEvent(event);
    }
    
    m_eventManager.Update();
}

void Window::ToggleFullScreen(EventDetails *l_details)
{
    m_isFullScreen = !m_isFullScreen;
    Destroy();
    Create();
}

void Window::Close(EventDetails *l_details)
{
    m_isDone = true;
}

void Window::BeginDraw()
{
    m_window.clear(sf::Color::White);
}

void Window::EndDraw()
{
    m_window.display();
}

const bool& Window::IsDone() const
{
    return m_isDone;
}

const bool& Window::IsFullScreen() const
{
    return m_isFullScreen;
}

const bool& Window::IsFocused() const
{
    return m_isFocused;
}

const sf::Vector2u & Window::GetWindowSize() const
{
    return m_windowSize;
}

sf::RenderWindow & Window::GetRenderWindow()
{
    return m_window;
}

EventManager &Window::GetEventManager()
{
    return  m_eventManager;
}

void Window::Draw(const sf::Drawable &l_drawable)
{
    m_window.draw(l_drawable);
}


