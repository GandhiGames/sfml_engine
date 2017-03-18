//
//  EntityMessage.hpp
//  sfml_engine
//
//  Created by Robert Wells on 09/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef EntityMessage_hpp
#define EntityMessage_hpp

enum class EntityMessage{
    Move, Is_Moving, Frame_Change, State_Changed, Direction_Changed,
    Switch_State, Attack_Action, Dead
};

#endif /* EntityMessage_hpp */
