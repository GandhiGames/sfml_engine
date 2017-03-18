#if !defined(SOUNDPROPS_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Robert Wells. $
   $Notice: (C) Copyright 2016 by Gandhi Games. All Rights Reserved. $
   ======================================================================== */

#define SOUNDPROPS_H

struct SoundProps
{
    SoundProps(const std::string& l_name):
            m_audioName(l_name), m_volume(100), m_pitch(1.0f), m_minDist(10.0f),
            m_attenuation(10.0f){}

    std::string m_audioName;
    float m_volume;
    float m_pitch;
    float m_minDist;
    float m_attenuation;
};

#endif
