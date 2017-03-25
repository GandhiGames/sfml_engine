//
//  AnimBase.cpp
//  sfml_engine
//
//  Created by Robert Wells on 06/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "AnimBase.hpp"
#include "SpriteSheet.hpp"

AnimBase::AnimBase(): m_frameCurrent(0), m_frameTime(0.f), m_elapsedTime(0.f), m_frameActionStart(-1),
                      m_frameActionEnd(-1), m_loop(false), m_playing(false), m_name(""),
                      m_hasMoved(false){}

AnimBase::~AnimBase(){}

void AnimBase::SetFrames(const std::vector<Frame>& l_frames)
{
    m_frames = l_frames;
    
    assert(m_spriteSheet->GetSpriteSize().x != 0 && m_spriteSheet->GetSpriteSize().y != 0);

    /*
    for(auto& it : m_frames)
    {
         m_reverseFrames.emplace_back(
             sf::IntRect(
                 it.left + m_spriteSheet->GetSpriteSize().x,
                 it.top,
                 -m_spriteSheet->GetSpriteSize().x,
                 m_spriteSheet->GetSpriteSize().y
             )
         );
    }
    */
}

bool AnimBase::SetFrame(int l_frame)
{
    if(l_frame >= 0 && l_frame < m_frames.size())
    {
        m_frameCurrent = l_frame;
        m_hasMoved = true;
        return true;
    }

    return false;
}

void AnimBase::FrameStep()
{
    bool stepped = SetFrame(m_frameCurrent + 1);

    if(stepped){ return; }

    if(m_loop)
    {
        SetFrame(0);
    }
    else
    {
        SetFrame(m_frames.size() - 1);
        Pause();
    }  
}

void AnimBase::CropSprite()
{   
    // if(m_spriteSheet->GetDirection() == m_defaultDir)
    //{
        m_spriteSheet->CropSprite(m_frames[GetCurrentFrame()]);
        //}
        //else
        //{
        //m_spriteSheet->CropSprite(m_reverseFrames[GetCurrentFrame()]);
        //
}

/*
void AnimBase::SetAnimationDefaultDirection(const Direction& l_dir)
{
    m_defaultDir = l_dir;
}
*/

bool AnimBase::IsInAction()
{
    if (m_frameActionStart == -1 || m_frameActionEnd == -1)
    {
        return true;
    }

    return (m_frameCurrent >= m_frameActionStart &&
            m_frameCurrent <= m_frameActionEnd);
}

void AnimBase::Reset()
{    
    m_frameCurrent = 0;
    m_elapsedTime = 0.0f;
    CropSprite();
    /*
    m_frameCurrent = m_frameStart;
    m_elapsedTime = 0.0f;
    CropSprite();
     */
}

void AnimBase::Update(const float& l_dT)
{
    if (!m_playing){ return; }
    
    m_elapsedTime += l_dT;
    if (m_elapsedTime < m_frameTime){ return; }
    
    FrameStep();
    CropSprite();
    m_elapsedTime = 0;
}

void AnimBase::Play(){ m_playing = true; }
void AnimBase::Pause(){ m_playing = false; }
void AnimBase::Stop(){ m_playing = false; Reset(); }
void AnimBase::ForceUpdate(){ m_elapsedTime = m_frameTime; }

void AnimBase::SetSpriteSheet(SpriteSheet* l_sheet){ m_spriteSheet = l_sheet; }
void AnimBase::SetActionStart(int l_frame){ m_frameActionStart = l_frame; }
void AnimBase::SetActionEnd(int l_frame){ m_frameActionEnd = l_frame; }
void AnimBase::SetFrameTime(float l_time){ m_frameTime = l_time; }
void AnimBase::SetLooping(bool l_loop){ m_loop = l_loop; }
void AnimBase::SetName(const std::string& l_name){ m_name = l_name; }

SpriteSheet* AnimBase::GetSpriteSheet(){ return m_spriteSheet; }
int AnimBase::GetCurrentFrame(){ return m_frameCurrent; }

bool AnimBase::CheckMoved()
{
    // std::cout << "Moved: " << m_hasMoved ? "true" : "false" << std::endl; 
    bool result = m_hasMoved;
    m_hasMoved = false;
    return result;
}

/*
Frame AnimBase::GetStartFrame(){ return m_frameStart; }
Frame AnimBase::GetEndFrame(){ return m_frameEnd; }
 */

int AnimBase::GetActionStart(){ return m_frameActionStart; }
int AnimBase::GetActionEnd(){ return m_frameActionEnd; }
float AnimBase::GetFrameTime(){ return m_frameTime; }
float AnimBase::GetElapsedTime(){ return m_elapsedTime; }
const std::string& AnimBase::GetName(){ return m_name;}
bool AnimBase::IsLooping(){ return m_loop; }
bool AnimBase::IsPlaying(){ return m_playing; }
