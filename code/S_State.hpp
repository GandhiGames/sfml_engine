//
//  S_State.hpp
//  sfml_engine
//
//  Created by Robert Wells on 12/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef S_State_hpp
#define S_State_hpp

#include "S_Base.hpp"
#include "C_State.hpp"

class S_State : public S_Base{
public:
    S_State(SystemManager* l_systemMgr);
    ~S_State();
    
    void Update(float l_dT);
    void HandleEvent(const EntityId& l_entity,const EntityEvent& l_event);
    void Notify(const Message& l_message);
private:
    void ChangeState(const EntityId& l_entity, const EntityState& l_state,
                     const bool& l_force);
};

#endif /* S_State_hpp */
