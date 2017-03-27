//
//  SpriteSheet.hpp
//  sfml_engine
//
//  Created by Robert Wells on 05/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef SpriteSheet_hpp
#define SpriteSheet_hpp

#include <unordered_map>
#include "AnimBase.hpp"
#include "TextureManager.hpp"
#include <SFML/Graphics.hpp>
#include "Direction.h"
#include "json.hpp"

using json = nlohmann::json;

using Animation = std::unordered_map<Direction, AnimBase*>;
using Animations = std::unordered_map<std::string, Animation>;

class SpriteSheet
{
public:
    SpriteSheet(TextureManager* l_textManager);
    ~SpriteSheet();
    
    void CropSprite(const sf::IntRect &l_rect);
    const sf::Vector2u& GetSpriteSize() const;
    sf::Vector2f GetSpritePosition() const;
    //void SetSpriteSize(const sf::Vector2i &l_size);
    void SetSpritePosition(const sf::Vector2f &l_pos);
    
    void SetDirection(const Direction& l_dir);
    const Direction &GetDirection()const;
    
    bool LoadSheet(const std::string &l_file);
    void ReleaseSheet();
    
    AnimBase* GetCurrentAnim();
    bool SetAnimation(const std::string &l_name,
                      const bool& l_play = false,
                      const bool& l_loop = false);
    
    void Update(const float &l_dT);
    void Draw(sf::RenderWindow* l_wnd);
    
private:
    template<typename Out>
    void split(const std::string &s, char delim, Out result)
    {
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim))
        {
            *(result++) = item;
        }
    }
    
    void ParseJson(const std::string& l_path);
    
    std::string m_texture;
    sf::Sprite m_sprite;
    sf::Vector2u m_spriteSize;
    sf::Vector2f m_spriteScale;
    Direction m_direction;
    //std::string m_animType;

    AnimBase* m_animationCurrent;

    //TODO(robert): Rename to m_animations.
    Animations m_animationss;
    
    TextureManager* m_textureManager;
};

#endif /* SpriteSheet_hpp */
