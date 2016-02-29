//
//  EventManager.hpp
//  sfml_engine
//
//  Created by Robert Wells on 28/02/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef EventManager_hpp
#define EventManager_hpp

#include <unordered_map>
#include <functional>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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
    Joystick
};

struct EventInfo {
    EventInfo() {m_code = 0;}
    EventInfo(int l_event) { m_code = l_event;}
    union {int m_code;};
    
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails {
    EventDetails(const std::string & l_bindName):m_bindName(l_bindName)
    {
        Clear();
    }
    
private:
    std::string m_bindName;
    sf::Vector2i m_size;
    sf::Uint32 m_textEntered;
    sf::Vector2i m_mouse;
    int m_mouseWheelDelta;
    int m_keyCode;
    
    void Clear()
    {
        m_size = sf::Vector2i(0, 0);
        m_textEntered = 0;
        m_mouse = sf::Vector2i(0, 0);
        m_mouseWheelDelta = 0;
        m_keyCode = -1;
    }
 
};

struct Binding {
    Binding(const std::string & l_name):m_name(l_name), m_details(l_name), m_eventCount(0){}
    void BindEvent(EventType l_type, EventInfo l_info = EventInfo())
    {
        m_events.emplace_back(l_type, l_info);
    }

private:
    std::string m_name;
    Events m_events;
    int m_eventCount;
    EventDetails m_details;
};

// unordered_map guarantees only one binding per action
using Bindings = std::unordered_map<std::string, Binding*>;

using Callbacks = std::unordered_map<std::string, std::function<void(EventDetails*)>>;



#endif /* EventManager_hpp */
