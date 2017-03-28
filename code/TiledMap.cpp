/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Casey Muratori $
   $Notice: (C) Copyright 2014 by Molly Rocket, Inc. All Rights Reserved. $
   ======================================================================== */
#include "TiledMap.hpp"

TiledMap::TiledMap(SharedContext* l_context)
        :m_context(l_context)
{
    
}

~TiledMap::TiledMap()
{
    PurgeMap();
}

void TiledMap::LoadMap(const std::string& l_path)
{
    //Load json file
//Pass to parsemap
    //pass to parse tile.
}

