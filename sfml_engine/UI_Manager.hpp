//
//  UI_Manager.hpp
//  sfml_engine
//
//  Created by Robert Wells on 24/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef UI_Manager_hpp
#define UI_Manager_hpp

#include <SFML/Graphics.hpp>
#include "EventManager.hpp"

#include "UI_Interface.hpp"
#include "UI_Event.h"
#include "UI_Label.h"
#include "UI_Scrollbar.h"
#include "UI_Textfield.h"

#include <unordered_map>
#include <functional>
#include <fstream>

using UI_Interfaces = std::unordered_map<std::string, UI_Interface*>;
using UI_Container = std::unordered_map<StateType, UI_Interfaces>;
using UI_Events = std::unordered_map<StateType, std::vector<UI_Event>>;
using UI_Factory = std::unordered_map<UI_ElementType, std::function<UI_Element*(UI_Interface*)>>;
using UI_ElemTypes = std::unordered_map <std::string,UI_ElementType>;

struct SharedContext;
class UI_Manager{
    friend class UI_Interface;
public:
    UI_Manager(EventManager* l_evMgr, SharedContext* l_shared);
    ~UI_Manager();
    
    bool AddInterface(const StateType& l_state,
                      const std::string& l_name);
    UI_Interface* GetInterface(const StateType& l_state,
                                const std::string& l_name);
    bool RemoveInterface(const StateType& l_state,
                         const std::string& l_name);
    
    bool LoadInterface(const StateType& l_state,
                       const std::string& l_interface, const std::string& l_name);
    
    void SetCurrentState(const StateType& l_state);
    
    SharedContext* GetContext();
    
    void DefocusAllInterfaces();
    
    void HandleClick(EventDetails* l_details);
    void HandleRelease(EventDetails* l_details);
    void HandleTextEntered(EventDetails* l_details);
    
    void AddEvent(UI_Event l_event);
    bool PollEvent(UI_Event& l_event);
    
    void Update(float l_dT);
    void Render(sf::RenderWindow* l_wind);
    
    template<class T>
    void RegisterElement(const GUI_ElementType& l_id){
        m_factory[l_id] = [](GUI_Interface* l_owner) -> GUI_Element*
        { return new T("",l_owner); };
    }
private:
    UI_Element* CreateElement(const UI_ElementType& l_id, GUI_Interface* l_owner);
    UI_ElementType StringToType(const std::string& l_string);
    bool LoadStyle(const std::string& l_file, UI_Element* l_element);
    
    UI_Container m_interfaces;
    UI_Events m_events;
    SharedContext* m_context;
    EventManager* m_eventMgr;
    StateType m_currentState;
    UI_Factory m_factory;
    UI_ElemTypes m_elemTypes;
};


#endif /* UI_Manager_hpp */
