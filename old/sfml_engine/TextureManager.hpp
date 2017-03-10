//
//  TextureManager.hpp
//  sfml_engine
//
//  Created by Robert Wells on 05/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "ResourceManager.h"
#include <SFML/Graphics/Texture.hpp>

class TextureManager : public ResourceManager<TextureManager, sf::Texture> {
public:
    TextureManager();
    
    sf::Texture* Load(const std::string& l_path);
    
};

#endif /* TextureManager_hpp */
