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
#include "ResourcePath.hpp"

//TODO: Singleton

using MessageContainer = std::vector<std::string>;

class Textbox {
public:
    Textbox();
    Textbox(int l_visible, int l_charSize, int l_width, const sf::Vector2f & l_screenPos);
    ~Textbox();

    void Setup(int l_visible, int l_charSize, int l_width, const sf::Vector2f & l_screenPos);
    
    void Add(std::string l_message);
    void Clear();
    
    void Render(sf::RenderWindow & l_window);
    
private:
    //TODO: define in header or imp?
    const static sf::Vector2f DEFAULT_POSITION;
    constexpr static float LINE_SPACING = 1.2f;
    const static sf::Vector2f OFFSET;
    const static int DEFAULT_LINES_VISIBLE = 5;
    const static int DEFAULT_CHAR_SIZE = 9;
    const static int DEFAULT_WIDTH = 200;
    const static sf::String DEFAULT_FONT;
    const static sf::Color DEFAULT_FONT_COLOUR;
    
    MessageContainer m_messages;
    int m_numLinesVisible;
    
    sf::RectangleShape m_background;
    sf::Font m_font;
    sf::Text m_content;
};

#endif /* Textbox_hpp */
