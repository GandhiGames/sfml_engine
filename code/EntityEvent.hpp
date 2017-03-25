//
//  EntityEvent.hpp
//  sfml_engine
//
//  Created by Robert Wells on 09/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef EntityEvent_hpp
#define EntityEvent_hpp

enum class EntityEvent{
    Spawned, Despawned, Colliding_X, Colliding_Y,
    Moving_Left, Moving_Right, Moving_Up, Moving_Down,
    Elevation_Change, Became_Idle, Began_Moving
};

#endif /* EntityEvent_hpp */
