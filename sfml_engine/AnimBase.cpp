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
m_frameActionEnd(-1), m_loop(false), m_playing(false){}

AnimBase::~AnimBase(){}

void AnimBase::SetFrames(const std::vector<Frame>& l_frames)
{
    m_frames = l_frames;
}

void AnimBase::SetFrame(int l_frame){
    /*
    if((l_frame >= m_frameStart && l_frame <= m_frameEnd) ||
       (l_frame >= m_frameEnd && l_frame <= m_frameStart))
    {
        m_frameCurrent = l_frame;
    }
     */
}

void AnimBase::FrameStep()
{
    /*
     if (m_frameStart < m_frameEnd){ ++m_frameCurrent; }
     else { --m_frameCurrent; }
     
     if ((m_frameStart < m_frameEnd && m_frameCurrent > m_frameEnd) ||
     (m_frameStart > m_frameEnd && m_frameCurrent < m_frameEnd))
     {
     if (m_loop){ m_frameCurrent = m_frameStart; return; }
     m_frameCurrent = m_frameEnd;
     Pause();
     }
     */
}

void AnimBase::CropSprite()
{
    /*
     sf::IntRect rect(m_spriteSheet->GetSpriteSize().x * m_frameCurrent,
     m_spriteSheet->GetSpriteSize().y * (m_frameRow + (short)m_spriteSheet->GetDirection()),
     m_spriteSheet->GetSpriteSize().x, m_spriteSheet->GetSpriteSize().y);
     m_spriteSheet->CropSprite(rect);
     */
}

bool AnimBase::IsInAction(){
    if (m_frameActionStart == -1 || m_frameActionEnd == -1){ return true; }
    return (m_frameCurrent >= m_frameActionStart && m_frameCurrent <= m_frameActionEnd);
}

void AnimBase::Reset(){
    /*
    m_frameCurrent = m_frameStart;
    m_elapsedTime = 0.0f;
    CropSprite();
     */
}

void AnimBase::Update(const float& l_dT){
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

void AnimBase::SetSpriteSheet(SpriteSheet* l_sheet){ m_spriteSheet = l_sheet; }

/*
void AnimBase::SetStartFrame(Frame l_frame){ m_frameStart = l_frame; }
void AnimBase::SetEndFrame(Frame l_frame){ m_frameEnd = l_frame; }
*/

void AnimBase::SetActionStart(int l_frame){ m_frameActionStart = l_frame; }
void AnimBase::SetActionEnd(int l_frame){ m_frameActionEnd = l_frame; }
void AnimBase::SetFrameTime(float l_time){ m_frameTime = l_time; }
void AnimBase::SetLooping(bool l_loop){ m_loop = l_loop; }
void AnimBase::SetName(const std::string& l_name){ m_name = l_name; }

SpriteSheet* AnimBase::GetSpriteSheet(){ return m_spriteSheet; }
int AnimBase::GetFrame(){ return m_frameCurrent; }

/*
Frame AnimBase::GetStartFrame(){ return m_frameStart; }
Frame AnimBase::GetEndFrame(){ return m_frameEnd; }
 */


int AnimBase::GetActionStart(){ return m_frameActionStart; }
int AnimBase::GetActionEnd(){ return m_frameActionEnd; }
float AnimBase::GetFrameTime(){ return m_frameTime; }
float AnimBase::GetElapsedTime(){ return m_elapsedTime; }
std::string AnimBase::GetName(){ return m_name; }
bool AnimBase::IsLooping(){ return m_loop; }
bool AnimBase::IsPlaying(){ return m_playing; }
