//
//  EventManager.hpp
//  sfml_engine
//
//  Created by Robert Wells on 28/02/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef EventManager_hpp
#define EventManager_hpp

#pragma clang diagnostic ignored "-Wswitch"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <assert.h>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ResourcePath.hpp"
#include "UI_Event.h"

enum class EventType {
    KeyDown = sf::Event::KeyPressed,
    KeyUp = sf::Event::KeyReleased,
    MButtonDown = sf::Event::MouseButtonPressed,
    MButtonUp = sf::Event::MouseButtonReleased,
    MouseWheel = sf::Event::MouseWheelMoved,
    WindowResized = sf::Event::Resized,
    GainedFocus = sf::Event::GainedFocus,
    LostFocus = sf::Event::LostFocus,
    MouseEntered = sf::Event::MouseEntered,
    MouseLeft = sf::Event::MouseLeft,
    Closed = sf::Event::Closed,
    TextEntered = sf::Event::TextEntered,
    Keyboard = sf::Event::Count + 1,
    Mouse,
    Joystick,
    UI_Click, UI_Release, UI_Hover, UI_Leave
};

//TODO(robert): Convert to boost library? boost::variant<int, UI_Event>
struct EventInfo {
    EventInfo() {m_code = 0;}
    EventInfo(int l_event) { m_code = l_event;}
    EventInfo(UI_Event l_uiEvent) { m_ui = l_uiEvent; }

    union
    {
        int m_code;
        UI_Event m_ui;
    };
    
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails {
    EventDetails(const std::string & l_bindName):m_name(l_bindName)
    {
        Clear();
    }
    
    const int GetKeyCode() const
    {
        return m_keyCode;
    }
    
    void SetKeyCode (int code)
    {
        m_keyCode = code;
    }
    
    const sf::Vector2i& GetMousePos()
    {
        return m_mouse;
    }
    
    void SetMouseX(int x)
    {
        m_mouse.x = x;
    }
    
    void SetMouseY(int y)
    {
        m_mouse.y = y;
    }
    
    void SetSizeX(int x)
    {
        m_size.x = x;
    }
    
    void SetSizeY(int y)
    {
        m_size.y = y;
    }
    
    const int& GetMouseDelta()
    {
        return m_mouseWheelDelta;
    }
    
    void SetMouseDelta(int l_mouseDelta)
    {
        m_mouseWheelDelta = l_mouseDelta;
    }
    
    const sf::Uint32& GetTextEntered()
    {
        return m_textEntered;
    }
    
    void SetTextEntered (sf::Uint32 l_textEntered)
    {
        m_textEntered = l_textEntered;
    }
    
    const std::string& GetName()
    {
        return m_name;
    }
    
    void SetName(const std::string& l_name)
    {
        m_name = l_name;
    }

    void SetUIInterface(const std::string& l_name)
    {
        m_uiInterface = l_name;
    }

    const std::string& GetUIInterface()
    {
        return m_uiInterface;
    }
    
    void SetUIElement(const std::string& l_name)
    {
        m_uiElement = l_name;
    }

    const std::string& GetUIElement()
    {
        return m_uiElement;
    }

    void SetUIEvent(UI_EventType l_type)
    {
        m_uiEvent = l_type;
    }

    const UI_EventType& GetUIEvent()
    {
        return m_uiEvent;
    }
     
    void Clear()
    {
        m_size = sf::Vector2i(0, 0);
        m_textEntered = 0;
        m_mouse = sf::Vector2i(0, 0);
        m_mouseWheelDelta = 0;
        m_keyCode = -1;
        m_uiInterface= "";
        m_uiElement = "";
        m_uiEvent = UI_EventType::None;
    }
    
private:
    std::string m_name;
    sf::Vector2i m_size;
    sf::Uint32 m_textEntered;
    sf::Vector2i m_mouse;
    int m_mouseWheelDelta;
    int m_keyCode;
    std::string m_uiInterface;
    std::string m_uiElement;
    UI_EventType m_uiEvent;
};

struct Binding {
    Binding(const std::string & l_name):
            m_name(l_name), m_details(l_name), m_eventCount(0)
    {
    }

    ~Binding()
    {
        for(auto itr = m_events.begin(); itr != m_events.end(); ++itr)
        {
            if (itr->first == EventType::UI_Click ||
                itr->first == EventType::UI_Release ||
                itr->first == EventType::UI_Hover ||
                itr->first == EventType::UI_Leave)
            {
                delete [] itr->second.m_ui.m_interface;
                delete [] itr->second.m_ui.m_element;
            }
        }
    }

    void BindEvent(EventType l_type, EventInfo l_info = EventInfo())
    {
        m_events.emplace_back(l_type, l_info);
    }
    
    const std::string & GetName() const
    {
        return m_name;
    }
    
    const Events& GetEvents() const
    {
        return m_events;
    }
    
    EventDetails &GetDetails()
    {
        return m_details;
    }
    
    void IncrementEventCount ()
    {
        m_eventCount++;
    }
    
    const int& GetEventCount () const
    {
        return m_eventCount;
    }
    
    void SetEventCount(int l_count)
    {
        m_eventCount = l_count;
    }
    
    
private:
    std::string m_name;
    Events m_events;
    int m_eventCount; //c
    EventDetails m_details;
};

// unordered_map guarantees only one binding per action
using Bindings = std::unordered_map<std::string, Binding*>;

using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails *)>>;

enum class StateType;

using Callbacks = std::unordered_map<StateType, CallbackContainer>;

class EventManager {
public:
    EventManager();
    ~EventManager();
    
    bool AddBinding(Binding &l_binding);
    bool RemoveBinding(const std::string & l_name);
    
    void SetCurrentState(const StateType &l_state);
    void SetFocus(const bool & l_focus);
    
    //TODO: needs to be defined in header?
    template<class T>
    bool AddCallback(const StateType &l_state, const std::string & l_name, void(T::*l_func)(EventDetails*), T* l_instance)
    {
        auto itr = m_callbacks.emplace(l_state, CallbackContainer()).first;
        auto tmp = std::bind(l_func, l_instance, std::placeholders::_1);
        return itr->second.emplace(l_name, tmp).second;
    }
    
    bool RemoveCallback(const StateType &l_state, const std::string & l_name);
    
    void HandleEvent(sf::Event& l_event);
    void HandleEvent(UI_Event& l_event);
    void Update();
    
    sf::Vector2i GetMousePosition(const sf::RenderWindow * l_window = nullptr);
    
private:
    Callbacks m_callbacks;
    Bindings m_bindings;
    StateType m_currentState;
    bool m_hasFocus;
    
    void LoadBindings();
};

#endif /* EventManager_hpp */
