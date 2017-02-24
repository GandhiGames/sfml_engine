//
//  UI_TextField.cpp
//  sfml_engine
//
//  Created by Robert Wells on 24/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#include "UI_TextField.hpp"
#include <algorithm>
#include <iostream>
#include "Utilities.h"

UI_Textfield::UI_Textfield(const std::string& l_name, UI_Interface* l_owner)
: UI_Element(l_name, UI_ElementType::Textfield , l_owner){}
UI_Textfield::~UI_Textfield(){}
void UI_Textfield::ReadIn(std::stringstream& l_stream){
    std::string content;
    ReadQuotedString(l_stream, content);
    m_visual.m_text.setString(content);
}
void UI_Textfield::OnClick(const sf::Vector2f& l_mousePos){
    SetState(UI_ElementState::Clicked);
}
void UI_Textfield::OnRelease(){}
void UI_Textfield::OnHover(const sf::Vector2f& l_mousePos){
    SetState(UI_ElementState::Focused);
}
void UI_Textfield::OnLeave(){
    SetState(UI_ElementState::Neutral);
}
void UI_Textfield::Update(float l_dT){}
void UI_Textfield::Draw(sf::RenderTarget* l_target){
    l_target->draw(m_visual.m_backgroundSolid);
    if (m_style[m_state].m_glyph != ""){
        l_target->draw(m_visual.m_glyph);
    }
    l_target->draw(m_visual.m_text);
}
