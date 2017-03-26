//
//  SpriteSheet.cpp
//  sfml_engine
//
//  Created by Robert Wells on 05/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "SpriteSheet.hpp"

SpriteSheet::SpriteSheet(TextureManager* l_textMgr)
:m_textureManager(l_textMgr), m_animationCurrent(nullptr),
m_spriteScale(1.f, 1.f), m_direction(Direction::Right), m_spriteSize(sf::Vector2f(0, 0)){}

SpriteSheet::~SpriteSheet(){ ReleaseSheet(); }

void SpriteSheet::ReleaseSheet()
{
    m_textureManager->ReleaseResource(m_texture);
    m_animationCurrent = nullptr;
    while(m_animationss.begin() != m_animationss.end())
    {
        while(m_animationss.begin()->second->begin() != m_animationss.begin()->second->end())
        {
            delete m_animationss.begin()->second->begin()->second;
            m_animationss.begin()->second->erase(m_animationss.begin()->second->begin());
        }
        
        delete m_animationss.begin()->second;
        m_animationss.erase(m_animationss.begin());
    }
}


const sf::Vector2u& SpriteSheet::GetSpriteSize()const{ return m_spriteSize; }


sf::Vector2f SpriteSheet::GetSpritePosition()const{ return m_sprite.getPosition(); }
const Direction& SpriteSheet::GetDirection()const { return m_direction; }
AnimBase* SpriteSheet::GetCurrentAnim(){ return m_animationCurrent; }

void SpriteSheet::CropSprite(const sf::IntRect& l_rect)
{
    m_sprite.setTextureRect(l_rect);
}

void SpriteSheet::SetSpritePosition(const sf::Vector2f& l_pos)
{
    m_sprite.setPosition(l_pos);
}

void SpriteSheet::SetDirection(const Direction& l_dir)
{
    if (l_dir == m_direction){ return; }
    
    m_direction = l_dir;
}

bool SpriteSheet::LoadSheet(const std::string& l_file)
{
    std::ifstream sheet;
    sheet.open(resourcePath() + l_file);

    if(sheet.is_open())
    {
        ReleaseSheet(); // Release current sheet resources.
        std::string line;
        while(std::getline(sheet,line))
        {
            if (line[0] == '|'){ continue; }
            std::stringstream keystream(line);
            std::string type;
            keystream >> type;
            if(type == "Texture")
            {
                if (m_texture != "")
                {
                    std::cerr << "! Duplicate texture entries in: " << l_file << std::endl;
                    continue;
                }

                std::string texture;
                keystream >> texture;

                if (!m_textureManager->RequireResource(texture))
                {
                    std::cerr << "! Could not set up the texture: " << texture << std::endl;
                    continue;
                }
                m_texture = texture;
                m_sprite.setTexture(*m_textureManager->GetResource(m_texture));
            }
            else if(type == "Data")
            {
                std::string dataPath;
                
                keystream >> dataPath;
                
                ParseJson(dataPath);
            }
        }
        
        sheet.close();
        
        assert(m_animationss.size() > 0);
        //assert(!m_animationss.begin()->second->GetName().empty());
        
        return true;
    }

    std::cerr << "! Failed loading spritesheet: " << l_file << std::endl;

    return false;
}

//TODO: read scale:  m_sprite.setScale(m_spriteScale);
void SpriteSheet::ParseJson(const std::string& l_path)
{    
    std::ifstream i(resourcePath() + l_path);
    
    if(i.is_open()){
        json animData;
        i >> animData;
        
        // Get default animation name.
        std::string defaultAnim = animData["meta"]["default"];
        
        assert(defaultAnim.size() > 0);
        
        // Set scale.
        float s = animData["meta"]["scale"].get<float>();
        assert(s != 0);
        m_spriteScale = sf::Vector2f(s, s);
        m_sprite.setScale(m_spriteScale);
        
        // Set origin.
        int sizeX = animData["meta"]["spriteSize"]["w"];
        int sizeY = animData["meta"]["spriteSize"]["w"];
        m_spriteSize = sf::Vector2u(sizeX, sizeY);
        m_sprite.setOrigin(sizeX * 0.5f, sizeY);
        
        // Get default direction.
        /*
        std::string dirName = animData["meta"]["direction"];
        Direction dir = Direction::Left;
        if(dirName == "Right"){
            dir = Direction::Right;
        }
        */
        
        for(auto it : animData["animations"])
        {
            std::string animName = it["animName"];
            
            assert(m_animationss.find(animName) == m_animationss.end());
            
            int animCount = it["frameCount"].get<int>();
            float frameTime = it["frameTime"].get<float>();
            int actionStart = it["frameActionStart"].get<int>();
            int actionEnd = it["frameActionEnd"].get<int>();
            
            std::vector<Frame> frames;
            
            for(auto frame : animData["frames"])
            {    
                size_t fileNameFound = frame["filename"].get<std::string>().find(animName);
                
                if(fileNameFound != std::string::npos)
                {
                    frames.emplace_back(sf::IntRect(frame["frame"]["x"], frame["frame"]["y"], frame["frame"]["w"], frame["frame"]["h"]));
                }
            }
            
            assert(frames.size() == animCount);            

            // Split animation string.            
            std::vector<std::string> elems;
            split(animName, ' ', std::back_inserter(elems));
            for(auto str : elems)
            {
                std::cout << "Spritesheet: " << str << std::endl;
            }
            assert(animName.size() == 2);

            
            AnimBase* anim = new AnimBase();
            anim->SetSpriteSheet(this);

            //TODO(robert): Does animation need a reference to its name?
            anim->SetName(animName);
            //anim->SetAnimationDefaultDirection(dir);
            anim->SetActionStart(actionStart);
            anim->SetActionEnd(actionEnd);
            anim->SetFrameTime(frameTime);
            anim->SetFrames(frames);
            anim->Reset();

            std::cout << "Spritesheet: animation name = " << animName << std::endl;
            
            //TODO(robert): Check if m_animations containks key before insertion attempt.
            //TODO(robert): Get animation dir from name, setup better method of direction retrieval
//            m_animationss[animName]->emplace(Direction::Down, anim);
            
            if (animName == defaultAnim)
            {
                m_animationCurrent = anim;
                m_animationCurrent->Play();
                m_animationCurrent->ForceUpdate();
            }
        }
        
       
    }
    
    i.close();
    
    
    assert(m_animationss.size() > 0);
}

bool SpriteSheet::SetAnimation(const std::string& l_name,
                               const bool& l_play, const bool& l_loop)
{
    auto itr = m_animationss.find(l_name);
    if (itr == m_animationss.end()){ return false; }

    auto itr2 = itr->second->find(m_direction);
    if(itr2 == itr->second->end()){ return false; }
    
    if (itr2->second == m_animationCurrent)
    {
        return false;
    }
    
    if (m_animationCurrent){ m_animationCurrent->Stop(); }
    
    m_animationCurrent = itr2->second;
    m_animationCurrent->SetLooping(l_loop);
    if(l_play){ m_animationCurrent->Play(); }
    m_animationCurrent->CropSprite();
    
    return true;
}

void SpriteSheet::Update(const float& l_dT)
{
    m_animationCurrent->Update(l_dT);
}

void SpriteSheet::Draw(sf::RenderWindow* l_wnd)
{
    l_wnd->draw(m_sprite);
}
