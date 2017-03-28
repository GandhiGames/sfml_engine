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
             sf::Uint16 l_x, sf::Uint16 l_y)
            : m_context(l_context), m_x(l_x), m_y(l_y)
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
    
    sf::Uint16 m_x;
    sf::Uint16 m_y;
    std::string m_name;
    sf::Vector2f m_friction;
    
    SharedContext* m_context;
    std::string m_texture;
};

using TileMap = std::unordered_map<int, TileInfo*>;

class TiledMap
{
public:
    TiledMap(SharedContext* l_context);
    ~TiledMap();

    void LoadMap(const std::string& l_path);

    void Update(float l_dt);
    void Draw(sf::Uint8 l_layer);
    
    TileInfo* GetTile(sf::Uint16 l_x, sf::Utin16 l_y, sf::Uint8 l_layer);
    const sf::Uint8 GetTileSize() const;
    const sf::Vector2u& GetMapSize() const;
    
private:
    // int index = (rowNum * length_of_row) + columnNum;
    int PosToIndex(sf::Uint16 l_x, sf::Uint16 l_y, sf::Uint8 l_layer) const;

    void ParseMapJsonData(const json& l_data);
    void ParseTileJsonData(const json& l_data);

    void PurgeMap();

    TileMap m_tileMap;
    TileInfo m_defaultTile;
    
    sf::Vector2u m_maxMapSize;
    SharedContext* m_context;
}

#endif
