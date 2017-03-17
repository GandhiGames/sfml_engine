//
//  S_Movement.hpp
//  sfml_engine
//
//  Created by Robert Wells on 12/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef S_Movement_hpp
#define S_Movement_hpp

//#pragma clang diagnostic ignored "-Wswitch"

#include "S_Base.hpp"
#include "C_Movable.hpp"


enum class Axis{ x, y };

class Map;

class S_Movement : public S_Base{
public:
    S_Movement(SystemManager* l_systemMgr);
    ~S_Movement();
    
    void Update(float l_dT);
    void HandleEvent(const EntityId& l_entity,const EntityEvent& l_event);
    void Notify(const Message& l_message);
    
    void SetMap(Map* l_gameMap);
private:
    void StopEntity(const EntityId& l_entity, const Axis& l_axis);
    void SetDirection(const EntityId& l_entity, const Direction& l_dir);
    const sf::Vector2f& GetTileFriction(int l_elevation,
                                        unsigned int l_x, unsigned int l_y);
    void MovementStep(float l_dT, C_Movable* l_movable, C_Position* l_position);
    
    Map* m_gameMap;
};

#endif /* S_Movement_hpp */
