//
//  Enemy.hpp
//  sfml_engine
//
//  Created by Robert Wells on 11/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "Character.hpp"

class Enemy : public Character{
public:
    Enemy(EntityManager* l_entityMgr);
    ~Enemy();

    void OnEntityCollision(EntityBase* l_collider, bool l_attack);
    void Update(float l_dT);
private:
    sf::Vector2f m_destination;
    bool m_hasDestination;
};

#endif /* Enemy_hpp */
