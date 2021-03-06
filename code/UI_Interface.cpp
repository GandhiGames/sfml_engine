//
//  UI_Interface.cpp
//  sfml_engine
//
//  Created by Robert Wells on 14/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#include "UI_Interface.hpp"
#include "UI_Manager.hpp"
#include "SharedContext.h"

UI_Interface::UI_Interface(const std::string& l_name, UI_Manager* l_guiManager)
: UI_Element(l_name, UI_ElementType::Window, this), m_parent(nullptr), m_guiManager(l_guiManager),
m_movable(false), m_beingMoved(false), m_showTitleBar(false), m_focused(false), m_scrollHorizontal(0),
m_scrollVertical(0), m_contentRedraw(true), m_controlRedraw(true)
{
    m_backdropTexture = new sf::RenderTexture();
    m_contentTexture = new sf::RenderTexture();
    m_controlTexture = new sf::RenderTexture();
}

UI_Interface::~UI_Interface(){
    delete m_backdropTexture;
    delete m_contentTexture;
    delete m_controlTexture;
    for (auto &itr : m_elements){
        delete itr.second;
    }
}

void UI_Interface::SetPosition(const sf::Vector2f& l_pos){
    UI_Element::SetPosition(l_pos);
    m_backdrop.setPosition(l_pos);
    m_content.setPosition(l_pos);
    m_control.setPosition(l_pos);
    m_titleBar.setPosition(m_position.x, m_position.y - m_titleBar.getSize().y);
    m_visual.m_text.setPosition(m_titleBar.getPosition() + m_style[m_state].m_textPadding);
}

bool UI_Interface::AddElement(const UI_ElementType& l_type,
                               const std::string& l_name)
{
    if (m_elements.find(l_name) != m_elements.end()){ return false; }
    UI_Element* element = nullptr;
    element = m_guiManager->CreateElement(l_type, this);
    if (!element){ return false; }
    element->SetName(l_name);
    element->SetOwner(this);
    m_elements.emplace(l_name, element);
    m_contentRedraw = true;
    m_controlRedraw = true;
    return true;
}

UI_Element* UI_Interface::GetElement(const std::string& l_name) const{
    auto itr = m_elements.find(l_name);
    return(itr != m_elements.end() ? itr->second : nullptr);
}

bool UI_Interface::RemoveElement(const std::string& l_name){
    auto itr = m_elements.find(l_name);
    if (itr == m_elements.end()){ return false; }
    delete itr->second;
    m_elements.erase(itr);
    m_contentRedraw = true;
    m_controlRedraw = true;
    AdjustContentSize();
    return true;
}

bool UI_Interface::HasParent() const{ return m_parent != nullptr; }
UI_Manager* UI_Interface::GetManager() const{ return m_guiManager; }

bool UI_Interface::IsInside(const sf::Vector2f& l_point) const{
    if (UI_Element::IsInside(l_point)){ return true; }
    return m_titleBar.getGlobalBounds().contains(l_point);
}

void UI_Interface::Focus(){ m_focused = true; }
void UI_Interface::Defocus(){ m_focused = false; }
bool UI_Interface::IsFocused(){ return m_focused; }

void UI_Interface::ReadIn(std::stringstream& l_stream){
    std::string movableState;
    std::string titleShow;
    std::string title;
    l_stream >> m_elementPadding.x >> m_elementPadding.y
    >> movableState >> titleShow;
    ReadQuotedString(l_stream, title);
    m_visual.m_text.setString(title);
    if (movableState == "Movable"){ m_movable = true; }
    if (titleShow == "Title"){ m_showTitleBar = true; }
}

void UI_Interface::OnClick(const sf::Vector2f& l_mousePos){
    DefocusTextfields();
    if (m_titleBar.getGlobalBounds().contains(l_mousePos) &&
        m_movable && m_showTitleBar)
    {
        m_beingMoved = true;
    } else {
        UI_Event event;
        event.m_type = UI_EventType::Click;
        event.m_interface = m_name.c_str();
        event.m_element = "";
        event.m_clickCoords.x = l_mousePos.x;
        event.m_clickCoords.y = l_mousePos.y;
        m_guiManager->AddEvent(event);
        for (auto &itr : m_elements){
            if (!itr.second->IsInside(l_mousePos)){ continue; }
            itr.second->OnClick(l_mousePos);
            event.m_element = itr.second->m_name.c_str();
            m_guiManager->AddEvent(event);
        }
        SetState(UI_ElementState::Clicked);
    }
}

void UI_Interface::OnRelease(){
    UI_Event event;
    event.m_type = UI_EventType::Release;
    event.m_interface = m_name.c_str();
    event.m_element = "";
    m_guiManager->AddEvent(event);
    for (auto &itr : m_elements){
        if (itr.second->GetState() != UI_ElementState::Clicked)
        {
            continue;
        }
        itr.second->OnRelease();
        event.m_element = itr.second->m_name.c_str();
        m_guiManager->AddEvent(event);
    }
    SetState(UI_ElementState::Neutral);
}

void UI_Interface::OnHover(const sf::Vector2f& l_mousePos){
    UI_Event event;
    event.m_type = UI_EventType::Hover;
    event.m_interface = m_name.c_str();
    event.m_element = "";
    event.m_clickCoords.x = l_mousePos.x;
    event.m_clickCoords.y = l_mousePos.y;
    m_guiManager->AddEvent(event);
    
    SetState(UI_ElementState::Focused);
}

void UI_Interface::OnLeave(){
    UI_Event event;
    event.m_type = UI_EventType::Leave;
    event.m_interface = m_name.c_str();
    event.m_element = "";
    m_guiManager->AddEvent(event);
    
    SetState(UI_ElementState::Neutral);
}

void UI_Interface::OnTextEntered(const char& l_char){
    for (auto &itr : m_elements){
        if (itr.second->GetType() != UI_ElementType::Textfield){ continue; }
        if (itr.second->GetState() != UI_ElementState::Clicked){ continue; }
        if (l_char == 8){
            // Backspace.
            const auto& text = itr.second->GetText();
            itr.second->SetText(text.substr(0, text.length() -1));
            return;
        }
        if (l_char < 32 || l_char > 126){ return; }
        std::string text = itr.second->GetText();
        text.push_back(l_char);
        itr.second->SetText(text);
        return;
    }
}

const sf::Vector2f& UI_Interface::GetPadding() const{ return m_elementPadding; }
void UI_Interface::SetPadding(const sf::Vector2f& l_padding){ m_elementPadding = l_padding;  }

void UI_Interface::Update(float l_dT){
    sf::Vector2f mousePos = sf::Vector2f(
        m_guiManager->GetContext()->GetEventManager()->GetMousePosition(
            m_guiManager->GetContext()->GetWindow()->GetRenderWindow()));
    
    if (m_beingMoved && m_moveMouseLast != mousePos){
        sf::Vector2f difference = mousePos - m_moveMouseLast;
        m_moveMouseLast = mousePos;
        sf::Vector2f newPosition = m_position + difference;
        SetPosition(newPosition);
    }
    
    for (auto &itr : m_elements){
        if (itr.second->NeedsRedraw()){
            if (itr.second->IsControl()){ m_controlRedraw = true; }
            else { m_contentRedraw = true; }
        }
        if (!itr.second->IsActive()){ continue; }
        itr.second->Update(l_dT);
        if (m_beingMoved){ continue; }
        UI_Event event;
        event.m_interface = m_name.c_str();
        event.m_element = itr.second->m_name.c_str();
        event.m_clickCoords.x = mousePos.x;
        event.m_clickCoords.y = mousePos.y;
        if (IsInside(mousePos) && itr.second->IsInside(mousePos)
            && !m_titleBar.getGlobalBounds().contains(mousePos))
        {
            if (itr.second->GetState() != UI_ElementState::Neutral){ continue; }
            itr.second->OnHover(mousePos);
            event.m_type = UI_EventType::Hover;
            m_guiManager->AddEvent(event);
        } else if (itr.second->GetState() == UI_ElementState::Focused){
            itr.second->OnLeave();
            event.m_type = UI_EventType::Leave;
            m_guiManager->AddEvent(event);
        }
    }
}

void UI_Interface::Draw(sf::RenderTarget* l_target){
    l_target->draw(m_backdrop);
    l_target->draw(m_content);
    l_target->draw(m_control);
    
    if (!m_showTitleBar){ return; }
    l_target->draw(m_titleBar);
    l_target->draw(m_visual.m_text);
}

bool UI_Interface::IsBeingMoved() const{ return m_beingMoved; }
bool UI_Interface::IsMovable() const{ return m_movable;  }

void UI_Interface::BeginMoving(){
    if (!m_showTitleBar || !m_movable){ return; }
    m_beingMoved = true;
    SharedContext* context = m_guiManager->GetContext();
    m_moveMouseLast = sf::Vector2f(context->GetEventManager()->
                                   GetMousePosition(context->GetWindow()->GetRenderWindow()));
}

void UI_Interface::StopMoving(){ m_beingMoved = false; }

sf::Vector2f UI_Interface::GetGlobalPosition() const{
    sf::Vector2f pos = m_position;
    UI_Interface* i = m_parent;
    while (i){
        pos += i->GetPosition();
        i = i->m_parent;
    }
    return pos;
}

void UI_Interface::ApplyStyle(){
    UI_Element::ApplyStyle(); // Call base method.
    m_visual.m_backgroundSolid.setPosition(0.f,0.f);
    m_visual.m_backgroundImage.setPosition(0.f,0.f);
    m_titleBar.setSize(sf::Vector2f(m_style[m_state].m_size.x, 16.f));
    m_titleBar.setPosition(m_position.x,m_position.y - m_titleBar.getSize().y);
    m_titleBar.setFillColor(m_style[m_state].m_elementColor);
    m_visual.m_text.setPosition(m_titleBar.getPosition() + m_style[m_state].m_textPadding);
    m_visual.m_glyph.setPosition(m_titleBar.getPosition() + m_style[m_state].m_glyphPadding);
}

void UI_Interface::Redraw(){
    if (m_backdropTexture->getSize().x != m_style[m_state].m_size.x ||
        m_backdropTexture->getSize().y != m_style[m_state].m_size.y)
    {
        m_backdropTexture->create(m_style[m_state].m_size.x, m_style[m_state].m_size.y);
    }
    m_backdropTexture->clear(sf::Color(0, 0, 0, 0));
    ApplyStyle();
    m_backdropTexture->draw(m_visual.m_backgroundSolid);
    
    if (m_style[m_state].m_backgroundImage != ""){
        m_backdropTexture->draw(m_visual.m_backgroundImage);
    }
    
    m_backdropTexture->display();
    m_backdrop.setTexture(m_backdropTexture->getTexture());
    m_backdrop.setTextureRect(sf::IntRect(0, 0, m_style[m_state].m_size.x, m_style[m_state].m_size.y));
    SetRedraw(false);
}
bool UI_Interface::NeedsContentRedraw() const{ return m_contentRedraw; }
void UI_Interface::RedrawContent(){
    if (m_contentTexture->getSize().x != m_contentSize.x ||
        m_contentTexture->getSize().y != m_contentSize.y)
    {
        m_contentTexture->create(m_contentSize.x, m_contentSize.y);
    }
    
    m_contentTexture->clear(sf::Color(0, 0, 0, 0));
    
    for (auto &itr : m_elements){
        UI_Element* element = itr.second;
        if (!element->IsActive() || element->IsControl()){ continue; }
        element->ApplyStyle();
        element->Draw(m_contentTexture);
        element->SetRedraw(false);
    }
    
    m_contentTexture->display();
    m_content.setTexture(m_contentTexture->getTexture());
    
    m_content.setTextureRect(sf::IntRect(m_scrollHorizontal, m_scrollVertical, m_style[m_state].m_size.x, m_style[m_state].m_size.y));
    m_contentRedraw = false;
}
bool UI_Interface::NeedsControlRedraw() const{ return m_controlRedraw; }
void UI_Interface::RedrawControls(){
    if (m_controlTexture->getSize().x != m_style[m_state].m_size.x ||
        m_controlTexture->getSize().y != m_style[m_state].m_size.y)
    {
        m_controlTexture->create(m_style[m_state].m_size.x, m_style[m_state].m_size.y);
    }
    m_controlTexture->clear(sf::Color(0, 0, 0, 0));
    
    for (auto &itr : m_elements){
        UI_Element* element = itr.second;
        if (!element->IsActive() || !element->IsControl()){ continue; }
        element->ApplyStyle();
        element->Draw(m_controlTexture);
        element->SetRedraw(false);
    }
    
    m_controlTexture->display();
    m_control.setTexture(m_controlTexture->getTexture());
    m_control.setTextureRect(sf::IntRect(0, 0, m_style[m_state].m_size.x, m_style[m_state].m_size.y));
    m_controlRedraw = false;
}

void UI_Interface::ToggleTitleBar(){ m_showTitleBar = !m_showTitleBar; }

void UI_Interface::AdjustContentSize(const UI_Element* l_reference){
    if (l_reference){
        sf::Vector2f bottomRight = l_reference->GetPosition() + l_reference->GetSize();
        if (bottomRight.x > m_contentSize.x){ m_contentSize.x = bottomRight.x; m_controlRedraw = true; }
        if (bottomRight.y > m_contentSize.y){ m_contentSize.y = bottomRight.y; m_controlRedraw = true; }
        return;
    }
    
    sf::Vector2f farthest = GetSize();
    
    for (auto &itr : m_elements){
        UI_Element* element = itr.second;
        if (!element->IsActive() || element->IsControl()){ continue; }
        sf::Vector2f bottomRight = element->GetPosition() + element->GetSize();
        if (bottomRight.x > farthest.x){ farthest.x = bottomRight.x; m_controlRedraw = true; }
        if (bottomRight.y > farthest.y){ farthest.y = bottomRight.y; m_controlRedraw = true; }
    }
    SetContentSize(farthest);
}

void UI_Interface::SetContentSize(const sf::Vector2f& l_vec){ m_contentSize = l_vec; }

void UI_Interface::UpdateScrollHorizontal(unsigned int l_percent){
    if (l_percent > 100){ return; }
    m_scrollHorizontal = ((m_contentSize.x - GetSize().x) / 100) * l_percent;
    sf::IntRect rect = m_content.getTextureRect();
    m_content.setTextureRect(sf::IntRect(m_scrollHorizontal, m_scrollVertical, rect.width, rect.height));
}

void UI_Interface::UpdateScrollVertical(unsigned int l_percent){
    if (l_percent > 100){ return; }
    m_scrollVertical = ((m_contentSize.y - GetSize().y) / 100) * l_percent;
    sf::IntRect rect = m_content.getTextureRect();
    m_content.setTextureRect(sf::IntRect(m_scrollHorizontal, m_scrollVertical, rect.width, rect.height));
}

const sf::Vector2f& UI_Interface::GetContentSize() const{ return m_contentSize; }

void UI_Interface::DefocusTextfields(){
    UI_Event event;
    event.m_type = UI_EventType::Release;
    event.m_interface = m_name.c_str();
    event.m_element = "";
    for (auto &itr : m_elements){
        if (itr.second->GetType() != UI_ElementType::Textfield){ continue; }
        itr.second->SetState(UI_ElementState::Neutral);
        event.m_element = itr.second->m_name.c_str();
        m_guiManager->AddEvent(event);
    }
}

int UI_Interface::GetScrollHorizontal()
{
    return m_scrollHorizontal;
}

int UI_Interface::GetScrollVertical()
{
    return m_scrollVertical;
}
