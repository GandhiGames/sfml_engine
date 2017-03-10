//
//  S_Control.hpp
//  sfml_engine
//
//  Created by Robert Wells on 12/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef S_Control_hpp
#define S_Control_hpp

#include "S_Base.hpp"
#include "C_Movable.hpp" 

class S_Control : public S_Base{
public:
    S_Control(SystemManager* l_systemMgr);
    ~S_Control();
    
    void Update(float l_dT);
    void HandleEvent(const EntityId& l_entity,const EntityEvent& l_event);
    void Notify(const Message& l_message);
private:
    void MoveEntity(const EntityId& l_entity, const Direction& l_dir);
};

#endif /* S_Control_hpp */
