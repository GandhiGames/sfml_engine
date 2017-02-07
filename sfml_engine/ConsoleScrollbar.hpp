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
#include <assert.h>
#include <iostream>

class ConsoleScrollbar{
public:
    ConsoleScrollbar();
    ~ConsoleScrollbar();
    
    void Setup(const sf::Vector2f& l_topRight, const sf::Vector2f& l_size);
    
    void Draw(sf::RenderWindow *l_wind);

    void SetScrollPercent(const float& l_perc);
    
private:
    sf::RectangleShape m_background;
    sf::RectangleShape m_scrollbar;
};

#endif /* ConsoleScrollbar_hpp */
