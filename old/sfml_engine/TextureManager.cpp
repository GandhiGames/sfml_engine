//
//  TextureManager.cpp
//  sfml_engine
//
//  Created by Robert Wells on 05/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "TextureManager.hpp"

TextureManager::TextureManager():ResourceManager("textures.cfg"){}

sf::Texture* TextureManager::Load(const std::string& l_path)
{
    sf::Texture* texture = new sf::Texture();
    if(!texture->loadFromFile(resourcePath() + l_path))
    {
        delete texture;
        texture = nullptr;
        std::cerr << "! Failed to load texture: " << l_path << std::endl;
    }
    
    return texture;
}
