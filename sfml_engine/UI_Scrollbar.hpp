//
//  UI_Scrollbar.hpp
//  sfml_engine
//
//  Created by Robert Wells on 24/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef UI_Scrollbar_hpp
#define UI_Scrollbar_hpp

#include "UI_Element.hpp"

enum class SliderType{ Horizontal, Vertical };

class UI_Scrollbar : public UI_Element{
public:
    UI_Scrollbar(const std::string& l_name, UI_Interface* l_owner);
    ~UI_Scrollbar();
    
    void SetPosition(const sf::Vector2f& l_pos);
    
    void ReadIn(std::stringstream& l_stream);
    void OnClick(const sf::Vector2f& l_mousePos);
    void OnRelease();
    void OnHover(const sf::Vector2f& l_mousePos);
    void OnLeave();
    
    void ApplyStyle();
    void UpdateStyle(const UI_ElementState& l_state, const UI_Style& l_style);
    
    void Update(float l_dT);
    void Draw(sf::RenderTarget* l_target);
private:
    SliderType m_sliderType;
    sf::RectangleShape m_slider;
    sf::Vector2f m_moveMouseLast;
    int m_percentage;
};

#endif /* UI_Scrollbar_hpp */
