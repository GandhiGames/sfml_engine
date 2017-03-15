//
//  EventManager.cpp
//  sfml_engine
//
//  Created by Robert Wells on 28/02/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "EventManager.hpp"
#include "StateManager.hpp"

EventManager::EventManager():m_currentState(StateType(0)), m_hasFocus(true)
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
            auto stateCallbacks = m_callbacks.find(m_currentState);
            auto otherCallbacks = m_callbacks.find(StateType(0));
            
            if (stateCallbacks != m_callbacks.end()){
                auto callItr = stateCallbacks->second.find(bind->GetName());
                if (callItr != stateCallbacks->second.end()){
                    // Pass in information about events.
                    callItr->second(&bind->GetDetails());
                }
            }
            
            if (otherCallbacks != m_callbacks.end()){
                auto callItr = otherCallbacks->second.find(bind->GetName());
                if (callItr != otherCallbacks->second.end()){
                    // Pass in information about events.
                    callItr->second(&bind->GetDetails());
                }
            }
        }
        bind->SetEventCount(0);
        bind->GetDetails().Clear();
    }
}

void EventManager::HandleEvent(sf::Event& l_event)
{
    for (auto &b_itr : m_bindings){
        Binding* bind = b_itr.second;
        for (auto &e_itr : bind->GetEvents()){
            EventType sfmlEvent = (EventType)l_event.type;
            if (e_itr.first != sfmlEvent){ continue; }
            if (e_itr.first == EventType::UI_Click ||
                e_itr.first == EventType::UI_Release ||
                e_itr.first == EventType::UI_Hover ||
                e_itr.first == EventType::UI_Leave)
            {
                continue;
            }
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

void EventManager::HandleEvent(UI_Event& l_event)
{
    for (auto &b_itr : m_bindings)
    {
        Binding* bind = b_itr.second;

        for (auto &e_itr : bind->GetEvents())
        {
            if (e_itr.first != EventType::UI_Click &&
                e_itr.first != EventType::UI_Release &&
                e_itr.first != EventType::UI_Hover &&
                e_itr.first != EventType::UI_Leave)
                {
                    continue;
                }

            if ((e_itr.first == EventType::UI_Click && l_event.m_type != UI_EventType::Click) ||
                (e_itr.first == EventType::UI_Release && l_event.m_type != UI_EventType::Release) ||
                (e_itr.first == EventType::UI_Hover && l_event.m_type != UI_EventType::Hover) ||
                (e_itr.first == EventType::UI_Leave && l_event.m_type != UI_EventType::Leave))
            {
                continue;
            }

            if (strcmp(e_itr.second.m_ui.m_interface, l_event.m_interface) ||
                strcmp(e_itr.second.m_ui.m_element, l_event.m_element))
            {
                continue;
            }

            bind->GetDetails().SetUIInterface(l_event.m_interface);
            bind->GetDetails().SetUIElement(l_event.m_element);

            bind->IncrementEventCount();
            
        }
    }
}

// returns false if binding found with same name.
bool EventManager::AddBinding(Binding& l_binding)
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

bool EventManager::RemoveCallback(const StateType &l_state,const std::string &l_name)
{
    auto itr = m_callbacks.find(l_state);
    if (itr == m_callbacks.end()){ return false; }
    auto itr2 = itr->second.find(l_name);
    if (itr2 == itr->second.end()){ return false; }
    itr->second.erase(l_name);
    return true;
}

sf::Vector2i EventManager::GetMousePosition(const sf::RenderWindow * l_window)
{
    return l_window ? sf::Mouse::getPosition(*l_window) : sf::Mouse::getPosition();
}

//TODO(robert): error handling, refractor (see commented out lines)
void EventManager::LoadBindings()
{
    const std::string delimiter = ":";
    const std::string bindings_file_name = "keys.cfg";
    
    std::ifstream bindings;
    
    bindings.open(resourcePath() + bindings_file_name);
    
    if (!bindings.is_open()) {
        printf("Failed to load file %s", bindings_file_name.c_str());
        return;
    }
    
    std::string line;
    while (std::getline(bindings, line)) {
        std::stringstream keystream(line);
        std::string callbackName;
        keystream >> callbackName;
        Binding *bind = new Binding(callbackName);
        
        while (!keystream.eof()) {
            std::string keyval;
            keystream >> keyval;
            
            int start = 0;
            unsigned long end = keyval.find(delimiter);
            if (end == std::string::npos) {
                //delete bind;
                //bind = nullptr;
                break;
            }
            
            EventType type = EventType(stoi(keyval.substr(start, end - start)));

            EventInfo eventInfo;
            if (type==EventType::UI_Click || type==EventType::UI_Release ||
                type == EventType::UI_Hover || type == EventType::UI_Leave)
            {
                start = end + delimiter.length();
                end = keyval.find(delimiter, start);
                std::string window = keyval.substr(start, end - start);
                std::string element;
                if (end != std::string::npos)
                {
                    start = end + delimiter.length();
                    end = keyval.length();
                    element = keyval.substr(start, end);
                }

                char* w = new char[window.length() + 1]; // +1 for \0
                char* e = new char[element.length() + 1]; // Size in bytes is the same as character length.1 char = 1B.
                strcpy_s(w, window.length() + 1, window.c_str());
                strcpy_s(e, element.length() + 1, element.c_str());
                eventInfo.m_ui.m_interface = w;
                eventInfo.m_ui.m_element = e;
            }
            else
            {
                int code = stoi(keyval.substr(end + delimiter.length(),
                                              keyval.find(delimiter,end + delimiter.length())));
                eventInfo.m_code = code;
            }

            bind->BindEvent(type, eventInfo);
            
        }
        
        if (bind && !AddBinding(*bind)) {
            delete bind;
        }
        
        bind = nullptr;
    }
    
    bindings.close();
}

void EventManager::SetFocus(const bool &l_focus)
{
    m_hasFocus = l_focus;
}

void EventManager::SetCurrentState(const StateType &l_state)
{
    m_currentState = l_state;
}
