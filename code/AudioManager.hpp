#if !defined(AUDIOMANAGER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Robert Wells. $
   $Notice: (C) Copyright 2016 by Gandhi Games. All Rights Reserved. $
   ======================================================================== */

#define AUDIOMANAGER_H

#include "ResourceManager.h"
#include <SFML/Audio/SoundBuffer.hpp>

class AudioManager : public ResourceManager<AudioManager, sf::SoundBuffer>
{
public:
    AudioManager();

    sf::SoundBuffer* Load(const std::string& l_path);
};

#endif
