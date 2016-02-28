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
    const static sf::Vector2f DefaultPosition;
    constexpr static float LineSpacing = 1.2f;
    const static sf::Vector2f Offset;
    const static int DefaultLinesVisible = 5;
    const static int DefaultCharSize = 9;
    const static int DefaultWidth = 200;
    const static sf::String DefaultFont;
    const static sf::Color DefaultFontColor;
    
    MessageContainer m_messages;
    int m_numLinesVisible;
    
    sf::RectangleShape m_background;
    sf::Font m_font;
    sf::Text m_content;
};

#endif /* Textbox_hpp */
