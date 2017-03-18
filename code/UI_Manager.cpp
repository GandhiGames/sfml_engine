//
//  UI_Manager.cpp
//  sfml_engine
//
//  Created by Robert Wells on 24/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#include "UI_Manager.hpp"
#include "SharedContext.h"

UI_Manager::UI_Manager(EventManager* l_evMgr, SharedContext* l_shared)
: m_eventMgr(l_evMgr), m_context(l_shared), m_currentState(StateType(0))
{
    RegisterElement<UI_Label>(UI_ElementType::Label);
    RegisterElement<UI_Scrollbar>(UI_ElementType::Scrollbar);
    RegisterElement<UI_Textfield>(UI_ElementType::Textfield);
    m_elemTypes.emplace("Label", UI_ElementType::Label);
    m_elemTypes.emplace("Button", UI_ElementType::Button);
    m_elemTypes.emplace("Scrollbar", UI_ElementType::Scrollbar);
    m_elemTypes.emplace("TextField", UI_ElementType::Textfield);
    m_elemTypes.emplace("Interface", UI_ElementType::Window);
    
    m_eventMgr->AddCallback(StateType(0), "Mouse_Left", &UI_Manager::HandleClick, this);
    m_eventMgr->AddCallback(StateType(0), "Mouse_Left_Release", &UI_Manager::HandleRelease, this);
    m_eventMgr->AddCallback(StateType(0), "Text_Entered", &UI_Manager::HandleTextEntered, this);
}

UI_Manager::~UI_Manager()
{
    m_eventMgr->RemoveCallback(StateType(0), "Mouse_Left");
    m_eventMgr->RemoveCallback(StateType(0), "Mouse_Left_Release");
    m_eventMgr->RemoveCallback(StateType(0), "Text_Entered");

    for (auto &itr : m_interfaces){
        for (auto &itr2 : itr.second){
            delete itr2.second;
        }
    }

    m_context->SetUIManager(nullptr);
}

UI_Interface* UI_Manager::GetInterface(const StateType& l_state,
                                         const std::string& l_name)
{
    auto s = m_interfaces.find(l_state);
    if (s == m_interfaces.end()){ return nullptr; }
    auto i = s->second.find(l_name);
    return (i != s->second.end() ? i->second : nullptr);
}

bool UI_Manager::RemoveInterface(const StateType& l_state,
                                  const std::string& l_name)
{
    auto s = m_interfaces.find(l_state);
    if (s == m_interfaces.end()){ return false; }
    auto i = s->second.find(l_name);
    if (i == s->second.end()){ return false; }
    delete i->second;
    return s->second.erase(l_name);
}

void UI_Manager::SetCurrentState(const StateType& l_state){
    if (m_currentState == l_state){ return; }
    HandleRelease(nullptr);
    m_currentState = l_state;
}

SharedContext* UI_Manager::GetContext(){ return m_context; }

void UI_Manager::DefocusAllInterfaces()
{
    auto state = m_interfaces.find(m_currentState);
    if (state == m_interfaces.end()){ return; }
    for (auto &itr : state->second){
        itr.second->Defocus();
    }
}

void UI_Manager::HandleClick(EventDetails* l_details)
{
    auto state = m_interfaces.find(m_currentState);
    if (state == m_interfaces.end()){ return; }
    sf::Vector2i mousePos = m_eventMgr->GetMousePosition(m_context->GetWindow()->GetRenderWindow());
    for (auto itr = state->second.rbegin(); itr != state->second.rend(); ++itr){
        if (!itr->second->IsInside(sf::Vector2f(mousePos))){ continue; }
        if (!itr->second->IsActive()){ return; }
        itr->second->OnClick(sf::Vector2f(mousePos));
        itr->second->Focus();
        if (itr->second->IsBeingMoved()){ itr->second->BeginMoving(); }
        return;
    }
}

void UI_Manager::HandleRelease(EventDetails* l_details)
{
    auto state = m_interfaces.find(m_currentState);
    if (state == m_interfaces.end()){ return; }
    for (auto &itr : state->second){
        UI_Interface* i = itr.second;
        if (!i->IsActive()){ continue; }
        if (i->GetState() == UI_ElementState::Clicked)
        {
            i->OnRelease();
        }
        if (i->IsBeingMoved()){ i->StopMoving(); }
    }
}

void UI_Manager::HandleTextEntered(EventDetails* l_details)
{
    auto state = m_interfaces.find(m_currentState);
    if (state == m_interfaces.end()){ return; }
    for (auto &itr : state->second){
        if (!itr.second->IsActive()){ continue; }
        if (!itr.second->IsFocused()){ continue; }
        itr.second->OnTextEntered(l_details->GetTextEntered());
        return;
    }
}

void UI_Manager::AddEvent(UI_Event l_event)
{
    m_events[m_currentState].push_back(l_event);
}

bool UI_Manager::PollEvent(UI_Event& l_event)
{
    if (m_events[m_currentState].empty()){ return false; }
    l_event = m_events[m_currentState].back();
    m_events[m_currentState].pop_back();
    return true;
}

void UI_Manager::Update(float l_dT)
{
    sf::Vector2i mousePos = m_eventMgr->GetMousePosition(m_context->GetWindow()->GetRenderWindow());
    
    auto state = m_interfaces.find(m_currentState);
    if (state == m_interfaces.end()){ return; }
    for (auto itr = state->second.rbegin(); itr != state->second.rend(); ++itr){
        UI_Interface* i = itr->second;
        if (!i->IsActive()){ continue; }
        i->Update(l_dT);
        if (i->IsBeingMoved()){ continue; }
        if (i->IsInside(sf::Vector2f(mousePos)))
        {
            if (i->GetState() == UI_ElementState::Neutral){
                i->OnHover(sf::Vector2f(mousePos));
            }
            return;
        } else if (i->GetState() == UI_ElementState::Focused){
            i->OnLeave();
        }
    }
}

void UI_Manager::Render(sf::RenderWindow* l_wind)
{ 
    auto state = m_interfaces.find(m_currentState);
    if (state == m_interfaces.end())
    {
        return;
    }
    for (auto &itr : state->second){
        UI_Interface* i = itr.second;

        if (!i->IsActive())
        {
            continue;
        }
        
        if (i->NeedsRedraw()){ i->Redraw(); }
        if (i->NeedsContentRedraw()){ i->RedrawContent(); }
        if (i->NeedsControlRedraw()){ i->RedrawControls(); }
        i->Draw(l_wind);
    }
}

UI_Element* UI_Manager::CreateElement(const UI_ElementType& l_id, UI_Interface* l_owner)
{
    if (l_id == UI_ElementType::Window){ return new UI_Interface("", this); }
    auto f = m_factory.find(l_id);
    return (f != m_factory.end() ? f->second(l_owner) : nullptr);
}

bool UI_Manager::AddInterface(const StateType& l_state,
                               const std::string& l_name)
{
    auto s = m_interfaces.emplace(l_state, UI_Interfaces()).first;
    UI_Interface* temp = new UI_Interface(l_name, this);
    if (s->second.emplace(l_name, temp).second){ return true; }
    delete temp;
    return false;
}

bool UI_Manager::LoadInterface(const StateType& l_state,
                                const std::string& l_interface, const std::string& l_name)
{
    std::ifstream file;
    file.open(resourcePath() + "media/UI_Interfaces/" + l_interface);
    std::string InterfaceName;
    
    if (!file.is_open()){
        std::cout << "! Failed to load: " << l_interface << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(file, line)){
        if (line[0] == '|'){ continue; }
        std::stringstream keystream(line);
        std::string key;
        keystream >> key;
        if (key == "Interface"){
            std::string style;
            keystream >> InterfaceName >> style;
            if (!AddInterface(l_state, l_name)){
                std::cout << "Failed adding interface: " << l_name << std::endl;
                return false;
            }
            UI_Interface* i = GetInterface(l_state, l_name);
            keystream >> *i;
            if (!LoadStyle(style, i)){
                std::cout << "Failed loading style file: " << style << " for interface " << l_name << std::endl;
            }
            i->SetContentSize(i->GetSize());
        } else if (key == "Element"){
            if (InterfaceName == ""){
                std::cout << "Error: 'Element' outside or before declaration of 'Interface'!" << std::endl;
                continue;
            }
            std::string type;
            std::string name;
            sf::Vector2f position;
            std::string style;
            keystream >> type >> name >> position.x >> position.y >> style;
            UI_ElementType eType = StringToType(type);
            if (eType == UI_ElementType::None){
                std::cout << "Unknown element('" << name << "') type: '" << type << "'" << std::endl;
                continue;
            }
            
            UI_Interface* i = GetInterface(l_state, l_name);
            if (!i){ continue; }
            if (!i->AddElement(eType, name)){ continue; }
            UI_Element* e = i->GetElement(name);
            keystream >> *e;
            e->SetPosition(position);
            if (!LoadStyle(style, e)){
                std::cout << "Failed loading style file: " << style << " for element " << name << std::endl;
                continue;
            }
        } else {
            std::cout << "! UI_Manager - Key not found: " << key << std::endl;
        }
    }
    file.close();
    return true;
}

bool UI_Manager::LoadStyle(const std::string& l_file, UI_Element* l_element)
{
    std::ifstream file;
    file.open(resourcePath() + "media/UI_Styles/" + l_file);
    
    std::string currentState;
    UI_Style ParentStyle;
    UI_Style TemporaryStyle;
    if (!file.is_open()){
        std::cout << "! Failed to load: " << l_file << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(file, line)){
        if (line[0] == '|'){ continue; }
        std::stringstream keystream(line);
        std::string type;
        keystream >> type;
        if (type == ""){ continue; }
        if (type == "State"){
            if (currentState != ""){
                std::cout << "Error: 'State' keyword found inside another state!" << std::endl;
                continue;
            }
            keystream >> currentState;
        } else if (type == "/State"){
            if (currentState == ""){
                std::cout << "Error: '/State' keyword found prior to 'State'!" << std::endl;
                continue;
            }
            UI_ElementState state = UI_ElementState::Neutral;
            if (currentState == "Hover"){ state = UI_ElementState::Focused; }
            else if (currentState == "Clicked"){ state = UI_ElementState::Clicked; }
            
            if (state == UI_ElementState::Neutral){
                ParentStyle = TemporaryStyle;
                l_element->UpdateStyle(UI_ElementState::Neutral, TemporaryStyle);
                l_element->UpdateStyle(UI_ElementState::Focused, TemporaryStyle);
                l_element->UpdateStyle(UI_ElementState::Clicked, TemporaryStyle);
            } else {
                l_element->UpdateStyle(state, TemporaryStyle);
            }
            TemporaryStyle = ParentStyle;
            currentState = "";
        } else {
            // Handling style information.
            if (currentState == ""){
                std::cout << "Error: '" << type << "' keyword found outside of a state!" << std::endl;
                continue;
            }
            if (type == "Size"){
                keystream >> TemporaryStyle.m_size.x >> TemporaryStyle.m_size.y;
            } else if (type == "BgColor"){
                int r, g, b, a = 0;
                keystream >> r >> g >> b >> a;
                TemporaryStyle.m_backgroundColor = sf::Color(r,g,b,a);
            } else if (type == "BgImage"){
                keystream >> TemporaryStyle.m_backgroundImage;
            } else if (type == "BgImageColor"){
                int r, g, b, a = 0;
                keystream >> r >> g >> b >> a;
                TemporaryStyle.m_backgroundImageColor = sf::Color(r, g, b, a);
            } else if (type == "TextColor"){
                int r, g, b, a = 0;
                keystream >> r >> g >> b >> a;
                TemporaryStyle.m_textColor = sf::Color(r, g, b, a);
            } else if (type == "TextSize"){
                keystream >> TemporaryStyle.m_textSize;
            } else if (type == "TextOriginCenter"){
                TemporaryStyle.m_textCenterOrigin = true;
            } else if (type == "Font"){
                keystream >> TemporaryStyle.m_textFont;
            } else if (type == "TextPadding"){
                keystream >> TemporaryStyle.m_textPadding.x >> TemporaryStyle.m_textPadding.y;
            } else if (type == "ElementColor"){
                int r, g, b, a = 0;
                keystream >> r >> g >> b >> a;
                TemporaryStyle.m_elementColor = sf::Color(r, g, b, a);
            } else if (type == "Glyph"){
                keystream >> TemporaryStyle.m_glyph;
            } else if (type == "GlyphPadding"){
                keystream >> TemporaryStyle.m_glyphPadding.x >> TemporaryStyle.m_glyphPadding.y;
            } else {
                std::cout << "Error: style tag '" << type << "' is unknown!" << std::endl;
            }
        }
    }
    file.close();
    return true;
}

UI_ElementType UI_Manager::StringToType(const std::string& l_string)
{
    auto t = m_elemTypes.find(l_string);
    return (t != m_elemTypes.end() ? t->second : UI_ElementType::None);
}
