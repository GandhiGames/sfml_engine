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
    
    void SetWindow(Window *l_window)
    {
        m_window = l_window;
    }
    
    EventManager *GetEventManager()
    {
        return m_eventManager;
    }
    
    void SetEventManager(EventManager *l_eventManager)
    {
        m_eventManager = l_eventManager;
    }
    
private:
    Window *m_window;
    EventManager *m_eventManager;
};

#endif /* SharedContext_h */
