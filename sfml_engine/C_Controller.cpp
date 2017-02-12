//
//  C_Controller.cpp
//  sfml_engine
//
//  Created by Robert Wells on 12/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#include "C_Controller.hpp"
#include "C_Base.h"

// Currently only used as a flag to show that the entity can be controlled.
class C_Controller : public C_Base{
public:
    C_Controller() : C_Base(Component::Controller){}
    void ReadIn(std::stringstream& l_stream){}
private:
    
};
