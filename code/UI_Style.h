//
//  UI_Style.h
//  sfml_engine
//
//  Created by Robert Wells on 14/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef UI_Style_h
#define UI_Style_h

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

enum class UI_ElementState{ Neutral, Focused, Clicked };

struct UI_Style{
    UI_Style(): m_textSize(12), m_textCenterOrigin(false),
    m_backgroundImageColor(255,255,255,255)
    {
        sf::Color none			= sf::Color(0, 0, 0, 0);
        m_backgroundColor		= none;
        m_elementColor			= none;
        m_textColor				= none;
    }
    
    sf::Vector2f m_size; // Element size.
    
    // Background properties.
    sf::Color m_backgroundColor;
    sf::Color m_elementColor;
    std::string m_backgroundImage;
    sf::Color m_backgroundImageColor;
    
    // Text properties.
    sf::Color m_textColor;
    std::string m_textFont;
    sf::Vector2f m_textPadding;
    unsigned int m_textSize;
    bool m_textCenterOrigin;
    
    // Glyph properties.
    std::string m_glyph;
    sf::Vector2f m_glyphPadding;
};

struct UI_Visual{
    sf::RectangleShape m_backgroundSolid;
    sf::Sprite m_backgroundImage;
    sf::Sprite m_glyph;
    sf::Text m_text;
};

#endif /* UI_Style_h */
