//
//  UI_Label.hpp
//  sfml_engine
//
//  Created by Robert Wells on 24/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef UI_Label_hpp
#define UI_Label_hpp

#include "UI_Element.hpp"

class UI_Label : public UI_Element{
public:
    UI_Label(const std::string& l_name, UI_Interface* l_owner);
    ~UI_Label();
    
    void ReadIn(std::stringstream& l_stream);
    void OnClick(const sf::Vector2f& l_mousePos);
    void OnRelease();
    void OnHover(const sf::Vector2f& l_mousePos);
    void OnLeave();
    void Update(float l_dT);
    void Draw(sf::RenderTarget* l_target);
};

#endif /* UI_Label_hpp */
