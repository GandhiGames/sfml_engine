#if !defined(C_SOUNDLISTENER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Robert Wells. $
   $Notice: (C) Copyright 2016 by Gandhi Games. All Rights Reserved. $
   ======================================================================== */

#define C_SOUNDLISTENER_H

#include "C_Base.h"

class C_SoundListener : public C_Base
{
public:
    C_SoundListener() : C_Base(Component::SoundListener){}
    void ReadIn(std::stringstream& l_stream){}
};

#endif
