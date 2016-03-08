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
#include "TextureManager.hpp"

class Map;

//TODO: pass by reference for all setter methods?
struct SharedContext {
    SharedContext():m_window(nullptr), m_eventManager(nullptr), m_textureManager(nullptr){}
    
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
    
    TextureManager* GetTextureManager()
    {
        return m_textureManager;
    }
    
    void SetTextureManager(TextureManager *l_textureManager)
    {
        m_textureManager = l_textureManager;
    }
    
    Map *GetMap()
    {
        return m_map;
    }
    
    void SetMap(Map *l_map)
    {
        m_map = l_map;
    }
    
private:
    Window *m_window;
    EventManager *m_eventManager;
    TextureManager *m_textureManager;
    Map *m_map;
};

#endif /* SharedContext_h */
