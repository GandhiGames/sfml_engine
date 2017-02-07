//
//  ConsoleScrollbar.hpp
//  sfml_engine
//
//  Created by Robert Wells on 07/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef ConsoleScrollbar_hpp
#define ConsoleScrollbar_hpp

#include <SFML/Graphics.hpp>

class ConsoleScrollbar{
public:
    ConsoleScrollbar();
    ~ConsoleScrollbar();
    
    
    void SetSize(const sf::Vector2f& l_size, const sf::Vector2f& l_scrollSize);
    void Draw(sf::RenderWindow *l_wind);

    
private:
    sf::RectangleShape m_background;
    sf::RectangleShape m_scrollbar;
};

#endif /* ConsoleScrollbar_hpp */
