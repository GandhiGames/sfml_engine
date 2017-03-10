//
//  Textbox.hpp
//  sfml_engine
//
//  Created by Robert Wells on 27/02/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef Textbox_hpp
#define Textbox_hpp

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "ResourcePath.hpp"
#include "FontManager.hpp"

class Textbox {
public:
    Textbox(FontManager& l_fontManager);
    Textbox(int l_visible, int l_charSize, int l_width, const sf::Vector2f & l_screenPos, FontManager& l_fontManager);
    ~Textbox();

    void Setup(int l_visible, int l_charSize, int l_width, const sf::Vector2f & l_screenPos);
    
    void Add(std::string l_message);
    void Clear();
    
    void Render(sf::RenderWindow* l_window);
    
private:
    //TODO: define in header or imp?
    const static sf::Vector2f DEFAULT_POSITION;
    constexpr static float LINE_SPACING = 1.2f;
    const static sf::Vector2f OFFSET;
    const static int DEFAULT_LINES_VISIBLE = 5;
    const static int DEFAULT_CHAR_SIZE = 18;
    const static int DEFAULT_WIDTH = 300;
    const static sf::String DEFAULT_FONT;
    const static sf::Color DEFAULT_FONT_COLOUR;
    
    std::vector<std::string> m_messages;
    int m_numLinesVisible;
    FontManager& m_fontManager;
    sf::RectangleShape m_background;
    sf::Text m_content;
    sf::View m_view;
};

#endif /* Textbox_hpp */
