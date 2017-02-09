//
//  SpriteSheet.cpp
//  sfml_engine
//
//  Created by Robert Wells on 05/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "SpriteSheet.hpp"

SpriteSheet::SpriteSheet(TextureManager &l_textMgr)
:m_textureManager(l_textMgr), m_animationCurrent(nullptr),
m_spriteScale(1.f, 1.f), m_direction(Direction::Right){}

SpriteSheet::~SpriteSheet(){ ReleaseSheet(); }

void SpriteSheet::ReleaseSheet()
{
    m_textureManager.ReleaseResource(m_texture);
    m_animationCurrent = nullptr;
    while(m_animations.begin() != m_animations.end()){
        delete m_animations.begin()->second;
        m_animations.erase(m_animations.begin());
    }
}

sf::Vector2i SpriteSheet::GetSpriteSize()const{ return m_spriteSize; }
sf::Vector2f SpriteSheet::GetSpritePosition()const{ return m_sprite.getPosition(); }
const Direction & SpriteSheet::GetDirection()const {
    return m_direction;
}
AnimBase* SpriteSheet::GetCurrentAnim(){ return m_animationCurrent; }

void SpriteSheet::SetSpriteSize(const sf::Vector2i &l_size){
    m_spriteSize = l_size;
    m_sprite.setOrigin(m_spriteSize.x * 0.5f, m_spriteSize.y);
}

void SpriteSheet::CropSprite(const sf::IntRect &l_rect){ m_sprite.setTextureRect(l_rect); }

void SpriteSheet::SetSpritePosition(const sf::Vector2f& l_pos){ m_sprite.setPosition(l_pos); }

void SpriteSheet::SetDirection(const Direction& l_dir){
    if (l_dir == m_direction){ return; }
    m_direction = l_dir;
    m_animationCurrent->CropSprite();
}

bool SpriteSheet::LoadSheet(const std::string& l_file){
    std::ifstream sheet;
    sheet.open(resourcePath() + l_file);
    if(sheet.is_open()){
        ReleaseSheet(); // Release current sheet resources.
        std::string line;
        while(std::getline(sheet,line)){
            if (line[0] == '|'){ continue; }
            std::stringstream keystream(line);
            std::string type;
            keystream >> type;
            if(type == "Texture"){
                if (m_texture != ""){
                    std::cerr << "! Duplicate texture entries in: " << l_file << std::endl;
                    continue;
                }
                std::string texture;
                keystream >> texture;
                if (!m_textureManager.RequireResource(texture)){
                    std::cerr << "! Could not set up the texture: " << texture << std::endl;
                    continue;
                }
                m_texture = texture;
                m_sprite.setTexture(*m_textureManager.GetResource(m_texture));
            } else if(type == "Size"){
                keystream >> m_spriteSize.x >> m_spriteSize.y;
                SetSpriteSize(m_spriteSize);
            } else if(type == "Scale"){
                keystream >> m_spriteScale.x >> m_spriteScale.y;
                m_sprite.setScale(m_spriteScale);
            } else if(type == "AnimationType"){
                keystream >> m_animType;
            } else if(type == "Animation"){
                /*std::string name;
                keystream >> name;
                if (m_animations.find(name) != m_animations.end()){
                    std::cerr << "! Duplicate animation(" << name << ") in: " << l_file << std::endl;
                    continue;
                }
                AnimBase* anim	= nullptr;
                if(m_animType == "Directional"){
                    anim = new AnimDirectional();
                } else {
                    std::cerr << "! Unknown animation type: " << m_animType << std::endl;
                    continue;
                }
                
                keystream >> *anim;
                anim->SetSpriteSheet(this);
                anim->SetName(name);
                anim->Reset();
                m_animations.emplace(name,anim);
                
                if (m_animationCurrent){ continue; }
                m_animationCurrent = anim;
                m_animationCurrent->Play();
                 */
            } else if(type == "Data"){
                std::string dataPath;
                
                keystream >> dataPath;
                
                ParseJson(dataPath);
            }
        }
        sheet.close();
        return true;
    }
    std::cerr << "! Failed loading spritesheet: " << l_file << std::endl;
    return false;
}

void SpriteSheet::ParseJson(const std::string& l_path)
{
    std::cout << resourcePath() << l_path << std::endl;
    
    std::ifstream i(resourcePath() + l_path);
    
    if(i.is_open()){
        json animData;
        i >> animData;
    
      
        
        for(auto it : animData["animations"]){
            
            std::string animName = it["animName"];
            int animCount = it["frameCount"].get<int>();
            float frameTime = it["frameTime"].get<float>();
            int actionStart = it["frameActionStart"].get<int>();
            int actionEnd = it["frameActionEnd"].get<int>();
            
            std::vector<Frame> frames;
            
            for(auto frame : animData["frames"]){

                
                size_t fileNameFound = frame["fileName"].get<std::string>().find(animName);
                
                if(fileNameFound != std::string::npos){
                    frames.emplace_back(sf::IntRect(frame["frame"]["x"], frame["frame"]["y"], frame["frame"]["w"], frame["frame"]["h"]));

                }
            }
            
            std::cout << animName << " " << std::to_string(frames.size()) << " " << animCount << std::endl;
            
            assert(frames.size() == animCount);
            
            //name
            std::cout << animName << std::endl;
            //int m_frameActionStart;
            std::cout << actionStart << std::endl;
            //int m_frameActionEnd;
            std::cout << actionEnd << std::endl;
            //float m_frameTime; // amount of time each frame takes to finish.
            std::cout << frameTime << std::endl;
            
            //"frame": {"x":64,"y":0,"w":32,"h":32},
            

            
            AnimBase* anim = new AnimBase();
            anim->SetActionStart(actionStart);
            anim->SetActionEnd(actionEnd);
            anim->SetFrameTime(frameTime);
            anim->SetFrames(frames);
            
            m_animations.emplace(animName, anim);
        }
    }
    
    
    assert(m_animations.size() > 0);
}

bool SpriteSheet::SetAnimation(const std::string& l_name,
                               const bool& l_play, const bool& l_loop)
{
    auto itr = m_animations.find(l_name);
    
    if (itr == m_animations.end()){ return false; }
    if (itr->second == m_animationCurrent){ return false; }
    
    if (m_animationCurrent){ m_animationCurrent->Stop(); }
    
    m_animationCurrent = itr->second;
    m_animationCurrent->SetLooping(l_loop);
    if(l_play){ m_animationCurrent->Play(); }
    m_animationCurrent->CropSprite();
    
    return true;
}

void SpriteSheet::Update(const float& l_dT){
    m_animationCurrent->Update(l_dT);
}

void SpriteSheet::Draw(sf::RenderWindow &l_wnd)
{
    l_wnd.draw(m_sprite);
}
