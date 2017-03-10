//
//  ConsoleCursor.hpp
//  sfml_engine
//
//  Created by Robert Wells on 06/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef ConsoleCursor_hpp
#define ConsoleCursor_hpp

#include <SFML/Graphics.hpp>

class ConsoleCursor{
public:
    ConsoleCursor(const float& l_blinkDelay);
    ~ConsoleCursor();

    void Update(const float& l_dt);
    void Draw(sf::RenderWindow* l_wind);
    
    void SetPosition(const sf::Vector2f& l_pos);
    const sf::Vector2f& GetPosition();
    
    void SetX(const float& l_x);
    
    void SetSize(const sf::Vector2f& l_size);
    const sf::Vector2f& GetSize();
    
private:
    float m_timeAccum;
    float m_blinkDelay;
    bool m_show;
    sf::RectangleShape m_cursor;
};

#endif /* ConsoleCursor_hpp */
