//
//  ECS_Types.h
//  sfml_engine
//
//  Created by Robert Wells on 09/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef ECS_Types_h
#define ECS_Types_h

using ComponentType = unsigned int;

#define N_COMPONENT_TYPES 32

enum class Component{
    Position = 0, SpriteSheet, State, Movable, Controller, Collidable
};

enum class System{
    Renderer = 0, Movement, Collision, Control, State, SheetAnimation
};



#endif /* ECS_Types_h */
