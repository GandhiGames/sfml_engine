//
//  UI_Scrollbar.cpp
//  sfml_engine
//
//  Created by Robert Wells on 24/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#include "UI_Scrollbar.hpp"
#include "UI_Interface.hpp"
#include "UI_Manager.hpp"
#include "SharedContext.h"

UI_Scrollbar::UI_Scrollbar(const std::string& l_name, UI_Interface* l_owner)
: UI_Element(l_name, UI_ElementType::Scrollbar, l_owner)
{
    m_isControl = true;
}
UI_Scrollbar::~UI_Scrollbar(){}

void UI_Scrollbar::SetPosition(const sf::Vector2f& l_pos){
    UI_Element::SetPosition(l_pos);
    if (m_sliderType == SliderType::Horizontal){ m_position.x = 0; }
    else { m_position.y = 0; }
}
void UI_Scrollbar::ReadIn(std::stringstream& l_stream){
    std::string type;
    l_stream >> type;
    if (type == "Horizontal"){ m_sliderType = SliderType::Horizontal; }
    else { m_sliderType = SliderType::Vertical; }
    
    if (m_sliderType == SliderType::Horizontal){ m_slider.setPosition(0, GetPosition().y); }
    else { m_slider.setPosition(GetPosition().x, 0); }
}
void UI_Scrollbar::OnClick(const sf::Vector2f& l_mousePos){
    if (!m_slider.getGlobalBounds().contains(l_mousePos - m_owner->GetPosition())){ return; }
    SetState(UI_ElementState::Clicked);
    m_moveMouseLast = l_mousePos;
}
void UI_Scrollbar::OnRelease(){
    SetState(UI_ElementState::Neutral);
}
void UI_Scrollbar::OnHover(const sf::Vector2f& l_mousePos){
    SetState(UI_ElementState::Focused);
}
void UI_Scrollbar::OnLeave(){
    SetState(UI_ElementState::Neutral);
}
void UI_Scrollbar::UpdateStyle(const UI_ElementState& l_state,
                                const UI_Style& l_style)
{
    UI_Element::UpdateStyle(l_state, l_style);
    if (m_sliderType == SliderType::Horizontal){ m_style[l_state].m_size.x = m_owner->GetSize().x; }
    else { m_style[l_state].m_size.y = m_owner->GetSize().y; }
}

void UI_Scrollbar::ApplyStyle(){
    UI_Element::ApplyStyle();
    m_slider.setFillColor(m_style[m_state].m_elementColor);
    bool horizontal = m_sliderType == SliderType::Horizontal;
    auto& bgSolid = m_visual.m_backgroundSolid;
    SetPosition((horizontal ?
                 sf::Vector2f(0, m_owner->GetSize().y - bgSolid.getSize().y) :
                 sf::Vector2f(m_owner->GetSize().x - bgSolid.getSize().x, 0)));
    bgSolid.setSize((horizontal ?
                     sf::Vector2f(m_owner->GetSize().x, m_style[m_state].m_size.y) :
                     sf::Vector2f(m_style[m_state].m_size.x, m_owner->GetSize().y)));
    m_slider.setPosition(
                         (horizontal ? m_slider.getPosition().x : GetPosition().x),
                         (horizontal ? GetPosition().y : m_slider.getPosition().y));
    float SizeFactor = (horizontal ?
                        m_owner->GetContentSize().x / m_owner->GetSize().x :
                        m_owner->GetContentSize().y / m_owner->GetSize().y);
    if (SizeFactor < 1.f){ SizeFactor = 1.f; }
    float SliderSize = (horizontal ? m_owner->GetSize().x : m_owner->GetSize().y) / SizeFactor;
    m_slider.setSize((horizontal ?
                      sf::Vector2f(SliderSize, bgSolid.getSize().y) :
                      sf::Vector2f(bgSolid.getSize().x, SliderSize)));
    bgSolid.setPosition(GetPosition());
}

void UI_Scrollbar::Update(float l_dT){
    // Mouse-drag code.
    if (GetState() != UI_ElementState::Clicked){ return; }
    SharedContext* context = m_owner->GetManager()->GetContext();
    sf::Vector2f mousePos = sf::Vector2f(context->GetEventManager()->GetMousePos(
                                                                              context->GetWindow()->GetRenderWindow()));
    if (m_moveMouseLast == mousePos){ return; }
    sf::Vector2f difference = mousePos - m_moveMouseLast;
    m_moveMouseLast = mousePos;
    
    bool horizontal = m_sliderType == SliderType::Horizontal;
    m_slider.move((horizontal ? difference.x : 0), (horizontal ? 0 : difference.y));
    if (horizontal && m_slider.getPosition().x < 0){
        m_slider.setPosition(0, m_slider.getPosition().y);
    } else if (m_slider.getPosition().y < 0){
        m_slider.setPosition(m_slider.getPosition().x, 0);
    }
    if (horizontal && (m_slider.getPosition().x + m_slider.getSize().x > m_owner->GetSize().x)){
        m_slider.setPosition(m_owner->GetSize().x - m_slider.getSize().x, m_slider.getPosition().y);
    } else if (m_slider.getPosition().y + m_slider.getSize().y > m_owner->GetSize().y){
        m_slider.setPosition(m_slider.getPosition().x, m_owner->GetSize().y - m_slider.getSize().y);
    }
    float WorkArea = (horizontal ? m_owner->GetSize().x - m_slider.getSize().x
                      : m_owner->GetSize().y - m_slider.getSize().y);
    int percentage = ((horizontal ?
                       m_slider.getPosition().x : m_slider.getPosition().y) / WorkArea) * 100;
    if (horizontal){ m_owner->UpdateScrollHorizontal(percentage); }
    else { m_owner->UpdateScrollVertical(percentage); }
    SetRedraw(true);
}
void UI_Scrollbar::Draw(sf::RenderTarget* l_target){
    l_target->draw(m_visual.m_backgroundSolid);
    l_target->draw(m_slider);
}
