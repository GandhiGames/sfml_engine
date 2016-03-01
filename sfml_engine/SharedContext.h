//
//  SharedContext.h
//  sfml_engine
//
//  Created by Robert Wells on 01/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//


#ifndef SharedContext_h
#define SharedContext_h

#include "Window.hpp"
#include "EventManager.hpp"

struct SharedContext {
    SharedContext():m_window(nullptr), m_eventManager(nullptr){}
    
    Window *GetWindow()
    {
        return m_window;
    }
    
    EventManager *GetEventManager()
    {
        return m_eventManager;
    }
    
private:
    Window *m_window;
    EventManager *m_eventManager;
};

#endif /* SharedContext_h */
