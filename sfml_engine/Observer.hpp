//
//  Observer.hpp
//  sfml_engine
//
//  Created by Robert Wells on 09/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef Observer_hpp
#define Observer_hpp

#include "Message.h"

class Observer{
public:
    virtual ~Observer(){}
    virtual void Notify(const Message& l_message) = 0;
};

#endif /* Observer_hpp */
