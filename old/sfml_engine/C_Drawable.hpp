//
//  C_Drawable.hpp
//  sfml_engine
//
//  Created by Robert Wells on 10/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef C_Drawable_hpp
#define C_Drawable_hpp

#include "C_Base.h"
#include <SFML/Graphics.hpp>

class C_Drawable : public C_Base{
public:
    C_Drawable(const Component& l_type) : C_Base(l_type){}
    virtual ~C_Drawable(){}
    
    virtual void UpdatePosition(const sf::Vector2f& l_vec) = 0;
    virtual const sf::Vector2u& GetSize() = 0;
    virtual void Draw(sf::RenderWindow* l_wind) = 0;
private:
    
};

#endif /* C_Drawable_hpp */
