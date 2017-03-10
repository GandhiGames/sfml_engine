//
//  C_State.hpp
//  sfml_engine
//
//  Created by Robert Wells on 12/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef C_State_hpp
#define C_State_hpp

#include "C_Base.h"

enum class EntityState{ Idle, Walking, Attacking, Hurt, Dying };

class C_State : public C_Base{
public:
    C_State(): C_Base(Component::State){}
    void ReadIn(std::stringstream& l_stream){
        unsigned int state = 0;
        l_stream >> state;
        m_state = (EntityState)state;
    }
    
    EntityState GetState(){ return m_state; }
    void SetState(const EntityState& l_state){
        m_state = l_state;
    }
private:
    EntityState m_state;
};

#endif /* C_State_hpp */
