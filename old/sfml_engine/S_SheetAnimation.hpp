//
//  S_SheetAnimation.hpp
//  sfml_engine
//
//  Created by Robert Wells on 12/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef S_SheetAnimation_hpp
#define S_SheetAnimation_hpp

#include "S_Base.hpp"

class S_SheetAnimation : public S_Base{
public:
    S_SheetAnimation(SystemManager* l_systemMgr);
    ~S_SheetAnimation();
    
    void Update(float l_dT);
    void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event);
    void Notify(const Message& l_message);
private:
    void ChangeAnimation(const EntityId& l_entity,
                         const std::string& l_anim, bool l_play, bool l_loop);
};

#endif /* S_SheetAnimation_hpp */
