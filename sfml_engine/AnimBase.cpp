//
//  AnimBase.cpp
//  sfml_engine
//
//  Created by Robert Wells on 06/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "AnimBase.hpp"
#include "SpriteSheet.hpp"

AnimBase::AnimBase(): m_frameCurrent(0), m_frameStart(0), m_frameEnd(0),
m_frameRow(0), m_frameTime(0.f), m_elapsedTime(0.f), m_frameActionStart(-1),
m_frameActionEnd(-1), m_loop(false), m_playing(false){}

AnimBase::~AnimBase(){}

void AnimBase::SetFrame(Frame l_frame){
    if((l_frame >= m_frameStart && l_frame <= m_frameEnd) ||
       (l_frame >= m_frameEnd && l_frame <= m_frameStart))
    {
        m_frameCurrent = l_frame;
    }
}

bool AnimBase::IsInAction(){
    if (m_frameActionStart == -1 || m_frameActionEnd == -1){ return true; }
    return (m_frameCurrent >= m_frameActionStart && m_frameCurrent <= m_frameActionEnd);
}

void AnimBase::Reset(){
    m_frameCurrent = m_frameStart;
    m_elapsedTime = 0.0f;
    CropSprite();
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
void AnimBase::SetStartFrame(Frame l_frame){ m_frameStart = l_frame; }
void AnimBase::SetEndFrame(Frame l_frame){ m_frameEnd = l_frame; }
void AnimBase::SetFrameRow(Frame l_row){ m_frameRow = l_row; }
void AnimBase::SetActionStart(Frame l_frame){ m_frameActionStart = l_frame; }
void AnimBase::SetActionEnd(Frame l_frame){ m_frameActionEnd = l_frame; }
void AnimBase::SetFrameTime(float l_time){ m_frameTime = l_time; }
void AnimBase::SetLooping(bool l_loop){ m_loop = l_loop; }
void AnimBase::SetName(const std::string& l_name){ m_name = l_name; }