//
//  Entity_Manager.hpp
//  sfml_engine
//
//  Created by Robert Wells on 09/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef Entity_Manager_hpp
#define Entity_Manager_hpp

#include "C_Position.hpp"
#include "C_SpriteSheet.hpp"
#include "C_State.hpp"
#include "C_Movable.hpp"
#include "C_Controller.hpp"
#include "C_Collidable.hpp"
#include "C_SoundEmitter.hpp"
#include "C_SoundListener.hpp"
#include "Bitmask.h"
#include "TextureManager.hpp"
#include <unordered_map>
#include <vector>
#include <functional>

using EntityId = unsigned int;

using ComponentContainer = std::vector<C_Base*>;
using EntityData = std::pair<Bitmask,ComponentContainer>;
using EntityContainer = std::unordered_map<EntityId,EntityData>;
using ComponentFactory = std::unordered_map<Component,std::function<C_Base*(void)>>;

class SystemManager;
class EntityManager
{
public:
    EntityManager(SystemManager* l_sysMgr, TextureManager* l_textureMgr);
    ~EntityManager();
    
    int AddEntity(const Bitmask& l_mask);
    int AddEntity(const std::string& l_entityFile);
    bool RemoveEntity(const EntityId& l_id);
    
    bool AddComponent(const EntityId& l_entity, const Component& l_component);
    
    template<class T>
    T* GetComponent(const EntityId& l_entity, const Component& l_component)
    {
        auto itr = m_entities.find(l_entity);
        if (itr == m_entities.end()){ return nullptr; }
        // Found the entity.
        if (!itr->second.first.GetBit((unsigned int)l_component)){ return nullptr; }
        // Component exists.
        auto& container = itr->second.second;
        auto component = std::find_if(container.begin(), container.end(), [&l_component](C_Base* c){ return c->GetType() == l_component; });
        
        return (component != container.end() ? dynamic_cast<T*>(*component) : nullptr);
    }
    
    bool RemoveComponent(const EntityId& l_entity, const Component& l_component);
    bool HasComponent(const EntityId& l_entity, const Component& l_component);
    
    void Purge();
private:
    template<class T>
    void AddComponentType(const Component& l_id)
    {
        m_cFactory[l_id] = []()->C_Base* { return new T(); };
    }
    
    // Data members
    unsigned int m_idCounter;
    EntityContainer m_entities;
    ComponentFactory m_cFactory;
    
    SystemManager* m_systems;
    TextureManager* m_textureManager;
};

#endif /* Entity_Manager_hpp */
