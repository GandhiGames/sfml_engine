//
//  FontManager.hpp
//  sfml_engine
//
//  Created by Robert Wells on 08/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef FontManager_hpp
#define FontManager_hpp

#include "ResourceManager.h"
#include <SFML/Graphics.hpp>

class FontManager : public ResourceManager<FontManager, sf::Font>
{
public:
    FontManager();
    
    sf::Font* Load(const std::string& l_path);
    
};

#endif /* FontManager_hpp */
