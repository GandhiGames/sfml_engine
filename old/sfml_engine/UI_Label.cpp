//
//  UI_Label.cpp
//  sfml_engine
//
//  Created by Robert Wells on 24/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#include "UI_Label.hpp"
#include <algorithm>
#include <iostream>
#include "Utilities.h"

UI_Label::UI_Label(const std::string& l_name, UI_Interface* l_owner)
: UI_Element(l_name, UI_ElementType::Label, l_owner){}
UI_Label::~UI_Label(){}

void UI_Label::ReadIn(std::stringstream& l_stream){
    std::string content;
    ReadQuotedString(l_stream, content);
    m_visual.m_text.setString(content);
}

void UI_Label::OnClick(const sf::Vector2f& l_mousePos){
    SetState(UI_ElementState::Clicked);
}
void UI_Label::OnRelease(){
    SetState(UI_ElementState::Neutral);
}
void UI_Label::OnHover(const sf::Vector2f& l_mousePos){
    SetState(UI_ElementState::Focused);
}
void UI_Label::OnLeave(){
    SetState(UI_ElementState::Neutral);
}
void UI_Label::Update(float l_dT){}
void UI_Label::Draw(sf::RenderTarget* l_target){
    l_target->draw(m_visual.m_backgroundSolid);
    if (m_style[m_state].m_glyph != ""){ l_target->draw(m_visual.m_glyph); }
    l_target->draw(m_visual.m_text);
}
