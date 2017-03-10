//
//  C_Controller.hpp
//  sfml_engine
//
//  Created by Robert Wells on 12/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef C_Controller_hpp
#define C_Controller_hpp

#include "C_Base.h"

// Currently only used as a flag to show that the entity can be controlled.
class C_Controller : public C_Base{
public:
    C_Controller() : C_Base(Component::Controller){}
    void ReadIn(std::stringstream& l_stream){}
private:
    
};


#endif /* C_Controller_hpp */
