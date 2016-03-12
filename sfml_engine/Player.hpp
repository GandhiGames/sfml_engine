//
//  Player.hpp
//  sfml_engine
//
//  Created by Robert Wells on 11/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Character.hpp"
#include "EventManager.hpp"

class Player : public Character{
public:
    Player(EntityManager* l_entityMgr);
    ~Player();
    
    void OnEntityCollision(EntityBase* l_collider, bool l_attack);
    void React(EventDetails* l_details);
};

#endif /* Player_hpp */
