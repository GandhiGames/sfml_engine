//
//  SystemManager.hpp
//  sfml_engine
//
//  Created by Robert Wells on 09/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef SystemManager_hpp
#define SystemManager_hpp

#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "S_Renderer.hpp"
#include "S_Movement.hpp"
#include "S_Collision.hpp"
#include "S_Control.hpp"
#include "S_State.hpp"
#include "S_SheetAnimation.hpp"
#include "S_Sound.hpp"
#include "EventQueue.hpp"
#include "MessageHandler.hpp"
#include "Profiler.hpp"
#include <unordered_map>
//#include "DebugOverlay.h"

using SystemContainer = std::unordered_map<System,S_Base*>;
using EntityEventContainer = std::unordered_map<EntityId,EventQueue>;

class EntityManager;
class SystemManager{
public:
    SystemManager();
    ~SystemManager();
    
    void SetEntityManager(EntityManager* l_entityMgr);
    EntityManager* GetEntityManager();
    MessageHandler* GetMessageHandler();
    
    template<class T>
    T* GetSystem(const System& l_system){
        auto itr = m_systems.find(l_system);
        return(itr != m_systems.end() ? dynamic_cast<T*>(itr->second) : nullptr);
    }
    
    void AddEvent(const EntityId& l_entity, const EventID& l_event);
    
    void Update(float l_dT);
    void HandleEvents();
    void Draw(Window* l_wind, unsigned int l_elevation);
    
    void EntityModified(const EntityId& l_entity, const Bitmask& l_bits);
    void RemoveEntity(const EntityId& l_entity);
    
    void PurgeEntities();
    void PurgeSystems();
   // DebugOverlay* m_debugOverlay;
private:
    SystemContainer m_systems;
    EntityManager* m_entityManager;
    EntityEventContainer m_events;
    MessageHandler m_messages;
    Profiler m_profiler;
};

#endif /* SystemManager_hpp */
