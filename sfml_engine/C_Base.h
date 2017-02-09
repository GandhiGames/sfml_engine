//
//  C_Base.h
//  sfml_engine
//
//  Created by Robert Wells on 09/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef C_Base_h
#define C_Base_h

#include "ECS_Types.h"

class C_Base{
public:
    C_Base(const Component& l_type): m_type(l_type){}
    virtual ~C_Base(){}
    
    Component GetType(){ return m_type; }
    
    friend std::stringstream& operator >>(std::stringstream& l_stream, C_Base& b)
    {
        b.ReadIn(l_stream);
        return l_stream;
    }
    
    virtual void ReadIn(std::stringstream& l_stream) = 0;
protected:
    Component m_type;
};


#endif /* C_Base_h */
