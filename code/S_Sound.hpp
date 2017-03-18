#if !defined(S_SOUND_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Robert Wells. $
   $Notice: (C) Copyright 2016 by Gandhi Games. All Rights Reserved. $
   ======================================================================== */

#define S_SOUND_H

#include "S_Base.hpp"
#include "C_SoundEmitter.hpp"
#include "C_SoundListener.hpp"

class S_Sound : public S_Base
{
public:
    S_Sound(SystemManager* l_systemMgr);
    ~S_Sound();

    void Update(float l_dT);
    void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event);
    void Notify(const Message& l_message);

    void SetUp(AudioManager* l_audioManager, SoundManager* l_soundManager);
private:
    sf::Vector3f MakeSoundPosition(const sf::Vector2f& l_entityPos, unsigned int l_elevation);
    void EmitSound(const EntityId& l_entity, const EntitySound& l_sound, 
        bool l_useId, bool l_relative, int l_checkFrame = -1);
    AudioManager* m_audioManager;
    SoundManager* m_soundManager;
};

#endif
