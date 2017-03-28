#include "Map.hpp"
#include "StateManager.hpp"

Map::Map(SharedContext* l_context)
:m_context(l_context), m_defaultTile(l_context), m_maxMapSize(32, 32), m_playerId(-1)
{
    m_context->SetMap(this);
    LoadTiles("tiles.cfg");
}

Map::~Map()
{
    PurgeMap();
    PurgeTileSet();
    m_context->SetMap(nullptr);
}

Tile* Map::GetTile(unsigned int l_x, unsigned int l_y, unsigned int l_layer)
{
    if(/*l_x < 0 || l_y < 0 ||*/ l_x >= m_maxMapSize.x || l_y >= m_maxMapSize.y || /*l_layer < 0 ||*/ l_layer >= Sheet::Num_Layers)
    {
        return nullptr;
    }
    
    auto itr = m_tileMap.find(ConvertCoords(l_x,l_y,l_layer));
    if (itr == m_tileMap.end()){ return nullptr; }
    return itr->second;
}

TileInfo* Map::GetDefaultTile(){ return &m_defaultTile; }
unsigned int Map::GetTileSize()const{ return Sheet::Tile_Size; }
const sf::Vector2u& Map::GetMapSize()const{ return m_maxMapSize; }
const sf::Vector2f& Map::GetPlayerStart()const{ return m_playerStart; }
int Map::GetPlayerId()const{ return m_playerId; }

void Map::LoadMap(const std::string& l_path)
{
    //TODO(robert): Setup default friction, handle loading entities,
    //load tiles, load map.

    
    std::ifstream i(resourcePath() + l_path);
    
    if(i.is_open())
    {
        json levelData;
        i >> levelData;

        assert(levelData["renderOrder"] == "right-down");

        ParseTileJsonData(levelData);
        ParseMapJsonData(levelData);
    }

    return;

    //TODO(robert): Remove below.
    std::ifstream mapFile;
    mapFile.open(resourcePath() + l_path);
    if (!mapFile.is_open())
    {
        std::cout << "! Failed loading map file: " << l_path << std::endl;
        return;
    }

    std::cout << "--- Loading a map: " << l_path << std::endl;
    std::string line;

    while(std::getline(mapFile,line))
    {
        if (line[0] == '|'){ continue; }
        std::stringstream keystream(line);
        std::string type;
        keystream >> type;
        if(type == "TILE")
        {
            int tileId = 0;
            keystream >> tileId;
            if (tileId < 0)
            {
                std::cout << "! Bad tile id: " << tileId << std::endl;
                continue;
            }

            auto itr = m_tileSet.find(tileId);
            if (itr == m_tileSet.end())
            {
                std::cout << "! Tile id(" << tileId << ") was not found in tileset." << std::endl;
                continue;
            }

            sf::Vector2i tileCoords;
            unsigned int tileLayer = 0;
            unsigned int tileSolidity = 0;
            keystream >> tileCoords.x >> tileCoords.y >> tileLayer >> tileSolidity;
            if (tileCoords.x > m_maxMapSize.x ||
                tileCoords.y > m_maxMapSize.y ||
                tileLayer >= Sheet::Num_Layers)
            {
                std::cout << "! Tile is out of range: " << tileCoords.x << " " << tileCoords.y << std::endl;
                continue;
            }

            Tile* tile = new Tile();
            // Bind properties of a tile from a set.
            tile->m_properties = itr->second;
            tile->m_solid = (bool)tileSolidity;
            if(!m_tileMap.emplace(ConvertCoords(
                                                tileCoords.x,tileCoords.y,tileLayer),tile).second)
            {
                // Duplicate tile detected!
                std::cout << "! Duplicate tile! : " << tileCoords.x << " " << tileCoords.y << std::endl;
                delete tile;
                continue;
            }

            std::string warp;
            keystream >> warp;
            tile->m_warp = false;
            if(warp == "WARP"){ tile->m_warp = true; }
        }
        else if(type == "SIZE")
        {
            keystream >> m_maxMapSize.x >> m_maxMapSize.y;
        }
        else if(type == "DEFAULT_FRICTION")
        {
            keystream >> m_defaultTile.m_friction.x >> m_defaultTile.m_friction.y;
        }
        else if(type == "ENTITY")
        {
            // Set up entity here.
            std::string name;
            keystream >> name;
            if (name == "Player" && m_playerId != -1){ continue; }
            int entityId = m_context->GetEntityManager()->AddEntity(name);
            if (entityId < 0){ continue; }
            if(name == "Player"){ m_playerId = entityId; }
            C_Base* position = m_context->GetEntityManager()->
            GetComponent<C_Position>(entityId,Component::Position);
            if(position){ keystream >> *position; }
        }
        else
        {
            // Something else.
            std::cout << "! Unknown type \"" << type << "\"." << std::endl;
        }
    }
    mapFile.close();

    std::cout << "--- Map Loaded! ---" << std::endl;
}

/* Example Json Map Data.

 { "height":20,
   "layers":[
        {
         "data":[0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
         "height":20,
         "name":"Walls",
         "opacity":1,
         "type":"tilelayer",
         "visible":true,
         "width":20,
         "x":0,
         "y":0
        }, 
        {
         "data":[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
         "height":20,
         "name":"Floor",
         "opacity":1,
         "type":"tilelayer",
         "visible":true,
         "width":20,
         "x":0,
         "y":0
        }],
 "nextobjectid":1,
 "orientation":"orthogonal",
 "renderorder":"right-down",
 "tileheight":32,
 "tilesets":[
        {
         "columns":2,
         "firstgid":1,
         "image":"level.png",
         "imageheight":32,
         "imagewidth":64,
         "margin":0,
         "name":"level",
         "spacing":0,
         "tilecount":2,
         "tileheight":32,
         "tilewidth":32
        }],
 "tilewidth":32,
 "version":1,
 "width":20
}
*/
void Map::ParseMapJsonData(const json& l_ data)
{
            
    int levelHeight  = levelData["height"];
    int levelWidth = levelData["width"];
        
    for(auto layer : animData["layers"])
    {
        //TODO(robert): Increment tiles layer each pass.
    }               
}

void Map::ParseTileJsonData(cost json& l_data)
{
    // Create tilemap and tileset
    for(auto tileSet : animData["tilesets"])
    {
        const std::string& imagePath = tileSet["image"];
        
        int tileHeight = tileSet["tileheight"];
        int tileWidth = tileSet["tilewidth"];

        int numOfTiles = tileSet["tilecount"];

        int spacing = tileSet["spacing"];
        int margin = tileSet["margin"];

        int imageHeight = tileSet["imageHeight"];
        int imageWidth = tileset["imageWidth"];

        int firstId = tileSet["firstgid"];

        
        
        // How tiles are current created:
        /*
                    int tileId = 0;
            keystream >> tileId;
            if (tileId < 0)
            {
                std::cout << "! Bad tile id: " << tileId << std::endl;
                continue;
            }

            auto itr = m_tileSet.find(tileId);
            if (itr == m_tileSet.end())
            {
                std::cout << "! Tile id(" << tileId << ") was not found in tileset." << std::endl;
                continue;
            }

            sf::Vector2i tileCoords;
            unsigned int tileLayer = 0;
            unsigned int tileSolidity = 0;
            keystream >> tileCoords.x >> tileCoords.y >> tileLayer >> tileSolidity;
            if (tileCoords.x > m_maxMapSize.x ||
                tileCoords.y > m_maxMapSize.y ||
                tileLayer >= Sheet::Num_Layers)
            {
                std::cout << "! Tile is out of range: " << tileCoords.x << " " << tileCoords.y << std::endl;
                continue;
            }

            Tile* tile = new Tile();
            // Bind properties of a tile from a set.
            tile->m_properties = itr->second;
            tile->m_solid = (bool)tileSolidity;
            if(!m_tileMap.emplace(ConvertCoords(
                                                tileCoords.x,tileCoords.y,tileLayer),tile).second)
            {
                // Duplicate tile detected!
                std::cout << "! Duplicate tile! : " << tileCoords.x << " " << tileCoords.y << std::endl;
                delete tile;
                continue;
            }

            std::string warp;
            keystream >> warp;
            tile->m_warp = false;
            if(warp == "WARP"){ tile->m_warp = true; }*/

    }
}

void Map::LoadTiles(const std::string& l_path)
{
    std::ifstream tileSetFile;
    tileSetFile.open(resourcePath() + l_path);

    if (!tileSetFile.is_open())
    {
        std::cout << "! Failed loading tile set file: " << l_path << std::endl;
        return;
    }

    std::string line;
    while(std::getline(tileSetFile,line))
    {
        if (line[0] == '|'){ continue; }
        std::stringstream keystream(line);
        int tileId;
        keystream >> tileId;
        if (tileId < 0){ continue; }
        TileInfo* tile = new TileInfo(m_context,"TileSheet",tileId);
        keystream >> tile->m_name >> tile->m_friction.x
                  >> tile->m_friction.y >> tile->m_deadly;

        if(!m_tileSet.emplace(tileId,tile).second)
        {
            // Duplicate tile detected!
            std::cout << "! Duplicate tile type: " << tile->m_name << std::endl;
            delete tile;
            tile = nullptr;
        }
    }
    tileSetFile.close();
}

void Map::Update(float l_dT){}

void Map::Draw(unsigned int l_layer)
{
    if (l_layer >= Sheet::Num_Layers){ return; }
    sf::RenderWindow* l_wind = m_context->GetWindow()->GetRenderWindow();
    sf::FloatRect viewSpace = m_context->GetWindow()->GetViewSpace();
    
    sf::Vector2i tileBegin(floor(viewSpace.left / Sheet::Tile_Size),floor(viewSpace.top / Sheet::Tile_Size));
    sf::Vector2i tileEnd(ceil((viewSpace.left + viewSpace.width) / Sheet::Tile_Size),
                         ceil((viewSpace.top + viewSpace.height) / Sheet::Tile_Size));
    
    unsigned int count = 0;

    for(int x = tileBegin.x; x <= tileEnd.x; ++x)
    {
        for(int y = tileBegin.y; y <= tileEnd.y; ++y)
        {
            Tile* tile = GetTile(x,y,l_layer);
            if (!tile){ continue; }
            sf::Sprite& sprite = tile->m_properties->m_sprite;
            sprite.setPosition(x * Sheet::Tile_Size, y * Sheet::Tile_Size);
            l_wind->draw(sprite);
            ++count;
        }
    }
}

unsigned int Map::ConvertCoords(unsigned int l_x, unsigned int l_y, unsigned int l_layer)const
{
    return ((l_layer*m_maxMapSize.y+l_y) * m_maxMapSize.x + l_x);
}

void Map::PurgeMap()
{
    while(m_tileMap.begin() != m_tileMap.end()){
        delete m_tileMap.begin()->second;
        m_tileMap.erase(m_tileMap.begin());
    }
    m_tileCount = 0;
    m_context->GetEntityManager()->Purge();
}

void Map::PurgeTileSet()
{
    while(m_tileSet.begin() != m_tileSet.end()){
        delete m_tileSet.begin()->second;
        m_tileSet.erase(m_tileSet.begin());
    }
    m_tileSetCount = 0;
}
