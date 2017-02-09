//
//  Player.cpp
//  sfml_engine
//
//  Created by Robert Wells on 11/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#include "Player.hpp"
#include "EntityManager.hpp"
#include "StateManager.hpp"

Player::Player(EntityManager* l_entityMgr)
: Character(l_entityMgr)
{
    Load("Player.char");
    m_type = EntityType::Player;
    
    EventManager* events = m_entityManager->GetContext()->GetEventManager();
    events->AddCallback<Player>(StateType::Game, "Player_MoveLeft", &Player::React, this);
    events->AddCallback<Player>(StateType::Game, "Player_MoveRight", &Player::React, this);
    events->AddCallback<Player>(StateType::Game, "Player_Jump", &Player::React, this);
    events->AddCallback<Player>(StateType::Game, "Player_Attack", &Player::React, this);
}

Player::~Player(){
    EventManager* events = m_entityManager->GetContext()->GetEventManager();
    events->RemoveCallback(StateType::Game, "Player_MoveLeft");
    events->RemoveCallback(StateType::Game, "Player_MoveRight");
    events->RemoveCallback(StateType::Game, "Player_Jump");
    events->RemoveCallback(StateType::Game, "Player_Attack");
}

void Player::React(EventDetails * l_details){
    
    std::string name = l_details->GetName();
    
    if (name == "Player_MoveLeft"){
        Character::Move(Direction::Left);
    } else if (name == "Player_MoveRight"){
        Character::Move(Direction::Right);
    } else if (name == "Player_Jump"){
        Character::Jump();
    } else if (name == "Player_Attack"){
        Character::Attack();
    }
}

void Player::OnEntityCollision(EntityBase* l_collider, bool l_attack){
    if (m_state == EntityState::Dying){ return; }
    if(l_attack){
        /*
        if (m_state != EntityState::Attacking){ return; }
        if (!m_spriteSheet.GetCurrentAnim()->IsInAction()){ return; }
        if (l_collider->GetType() != EntityType::Enemy &&
            l_collider->GetType() != EntityType::Player)
        {
            return;
        }
        Character* opponent = (Character*)l_collider;
        opponent->GetHurt(1);
        if(m_position.x > opponent->GetPosition().x){
            opponent->AddVelocity(-32,0);
        } else {
            opponent->AddVelocity(32,0);
        }
         */
    } else {
        // Other behavior.
    }
}
