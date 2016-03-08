//
//  AnimDirectional.cpp
//  sfml_engine
//
//  Created by Robert Wells on 07/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "AnimDirectional.hpp"
#include "SpriteSheet.hpp"

void AnimDirectional::FrameStep()
{
    if (m_frameStart < m_frameEnd){ ++m_frameCurrent; }
    else { --m_frameCurrent; }
    
    if ((m_frameStart < m_frameEnd && m_frameCurrent > m_frameEnd) ||
        (m_frameStart > m_frameEnd && m_frameCurrent < m_frameEnd))
    {
        if (m_loop){ m_frameCurrent = m_frameStart; return; }
        m_frameCurrent = m_frameEnd;
        Pause();
    }
}

void AnimDirectional::CropSprite()
{
    sf::IntRect rect(m_spriteSheet->GetSpriteSize().x * m_frameCurrent,
                     m_spriteSheet->GetSpriteSize().y * (m_frameRow + (short)m_spriteSheet->GetDirection()),
                     m_spriteSheet->GetSpriteSize().x, m_spriteSheet->GetSpriteSize().y);
    m_spriteSheet->CropSprite(rect);
}

void AnimDirectional::ReadIn(std::stringstream &l_stream)
{
    l_stream >> m_frameStart >> m_frameEnd >> m_frameRow
    >> m_frameTime >> m_frameActionStart >> m_frameActionEnd;
}
