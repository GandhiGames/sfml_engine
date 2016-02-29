//
//  EventManager.cpp
//  sfml_engine
//
//  Created by Robert Wells on 28/02/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "EventManager.hpp"

EventManager::EventManager():m_hasFocus(true)
{
    LoadBindings();
}

EventManager::~EventManager()
{
    for (auto &itr : m_bindings) {
        delete itr.second;
        itr.second = nullptr;
    }
}

void EventManager::Update()
{
    if (!m_hasFocus){ return; }
    for (auto &b_itr : m_bindings){
        Binding* bind = b_itr.second;
        for (auto &e_itr : bind->GetEvents()){
            switch (e_itr.first){
                case(EventType::Keyboard) :
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.m_code))){
                        if (bind->GetDetails().GetKeyCode() != -1){
                            bind->GetDetails().SetKeyCode(e_itr.second.m_code);
                        }
                        bind->IncrementEventCount();
                    }
                    break;
                case(EventType::Mouse) :
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second.m_code))){
                        if (bind->GetDetails().GetKeyCode() != -1){
                            bind->GetDetails().SetKeyCode(e_itr.second.m_code);
                        }
                        bind->IncrementEventCount();
                    }
                    break;
                case(EventType::Joystick) :
                    // Up for expansion.
                    break;
            }
        }
        
        if (bind->GetEvents().size() == bind->GetEventCount()){
            auto callItr = m_callbacks.find(bind->GetName());
            
            if (callItr != m_callbacks.end()){
                callItr->second(&bind->GetDetails());
            }
        }
        bind->SetEventCount(0);
        bind->GetDetails().Clear();
    }
}

void EventManager::HandleEvent(sf::Event &l_event)
{
   	for (auto &b_itr : m_bindings){
        Binding* bind = b_itr.second;
        for (auto &e_itr : bind->GetEvents()){
            EventType sfmlEvent = (EventType)l_event.type;
            if (e_itr.first != sfmlEvent){ continue; }
            if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp){
                if (e_itr.second.m_code == l_event.key.code){
                    // Matching event/keystroke.
                    // Increase count.
                    if (bind->GetDetails().GetKeyCode() != -1){
                        bind->GetDetails().SetKeyCode(e_itr.second.m_code);
                    }
                    bind->IncrementEventCount();
                    break;
                }
            } else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp){
                if (e_itr.second.m_code == l_event.mouseButton.button){
                    // Matching event/keystroke.
                    // Increase count.
                    bind->GetDetails().SetMouseX(l_event.mouseButton.x);
                    bind->GetDetails().SetMouseY(l_event.mouseButton.y);
                    if (bind->GetDetails().GetKeyCode() != -1){
                        bind->GetDetails().SetKeyCode(e_itr.second.m_code);
                    }
                    bind->IncrementEventCount();
                    break;
                }
            } else {
                // No need for additional checking.
                if (sfmlEvent == EventType::MouseWheel){
                    bind->GetDetails().SetMouseDelta(l_event.mouseWheel.delta);
                } else if (sfmlEvent == EventType::WindowResized){
                    bind->GetDetails().SetSizeX(l_event.size.width);
                    bind->GetDetails().SetSizeY(l_event.size.height);
                } else if (sfmlEvent == EventType::TextEntered){
                    bind->GetDetails().SetTextEntered(l_event.text.unicode);
                }
                bind->IncrementEventCount();
            }
        }
    }
}

// returns false if binding found with same name.
bool EventManager::AddBinding(Binding &l_binding)
{
    if (m_bindings.find(l_binding.GetName()) != m_bindings.end()) {
        return false;
    }
    
    return m_bindings.emplace(l_binding.GetName(), &l_binding).second;
}

bool EventManager::RemoveBinding(const std::string &l_name)
{
    auto itr = m_bindings.find(l_name);
    
    if (itr == m_bindings.end()) {
        return false;
    }
    
    delete itr->second;
    m_bindings.erase(itr);
    return true;
}

void EventManager::RemoveCallback(const std::string &l_name)
{
    m_callbacks.erase(l_name);
}

sf::Vector2i EventManager::GetMousePosition(const sf::RenderWindow * l_window)
{
    return l_window ? sf::Mouse::getPosition(*l_window) : sf::Mouse::getPosition();
}

void EventManager::LoadBindings()
{
    
    
}