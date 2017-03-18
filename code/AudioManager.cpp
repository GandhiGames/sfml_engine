/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Casey Muratori $
   $Notice: (C) Copyright 2014 by Molly Rocket, Inc. All Rights Reserved. $
   ======================================================================== */

#include "AudioManager.hpp"

AudioManager::AudioManager():ResourceManager("audio.cfg"){}

sf::SoundBuffer* AudioManager::Load(const std::string& l_path)
{
    sf::SoundBuffer* sound = new sf::SoundBuffer();

    if (!sound->loadFromFile(resourcePath() + l_path))
    {
        delete sound;
        sound = nullptr;
        std::cerr << "! Failed to load sound: " << l_path << std::endl;
    }
    return sound;
}
