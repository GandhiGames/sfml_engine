//
//  FontManager.cpp
//  sfml_engine
//
//  Created by Robert Wells on 08/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#include "FontManager.hpp"

FontManager::FontManager():ResourceManager("fonts.cfg"){}

sf::Font* FontManager::Load(const std::string& l_path)
{
    sf::Font* font = new sf::Font();
    if(!font->loadFromFile(resourcePath() + l_path))
    {
        delete font;
        font = nullptr;
        std::cerr << "! Failed to load font: " << l_path << std::endl;
    }

    return font;
}
