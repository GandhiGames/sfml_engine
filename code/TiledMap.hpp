#if !defined(TILEDMAP_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Robert Wells. $
   $Notice: (C) Copyright 2016 by Gandhi Games. All Rights Reserved. $
   ======================================================================== */

#define TILEDMAP_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <map>
#include <fstream>
#include <sstream>
#include "SharedContext.h"
#include "json.hpp"

struct TileInfo
{
    TileInfo(SharedContext* l_context,
             const std::string& l_texture = "",
             TileID l_id = 0)
    : m_context(l_context), m_id(0), m_deadly(false)
    {
        TextureManager* tmgr = l_context->GetTextureManager();

        if (l_texture == ""){ m_id = l_id; return; }
        if (!tmgr->RequireResource(l_texture)){ return; }

        m_texture = l_texture;
        m_id = l_id;
        m_sprite.setTexture(*tmgr->GetResource(m_texture));
        sf::IntRect tileBoundaries(m_id % (Sheet::Sheet_Width / Sheet::Tile_Size) * Sheet::Tile_Size,
                                   m_id / (Sheet::Sheet_Height / Sheet::Tile_Size) * Sheet::Tile_Size,
                                   Sheet::Tile_Size, Sheet::Tile_Size);
        m_sprite.setTextureRect(tileBoundaries);
    }
    
    ~TileInfo()
    {
        if (m_texture == ""){ return; }
        m_context->GetTextureManager()->ReleaseResource(m_texture);
    }
    
    sf::Sprite m_sprite;
    
    TileID m_id;
    std::string m_name;
    sf::Vector2f m_friction;
    
    SharedContext* m_context;
    std::string m_texture;
};

// int index = (rowNum * length_of_row) + columnNum;


#endif
