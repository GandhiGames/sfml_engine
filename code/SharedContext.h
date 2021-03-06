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
#include "FontManager.hpp"
#include "Entity_Manager.hpp"
#include "SystemManager.hpp"
#include "DebugOverlay.h"
#include "Textbox.hpp"
#include "UI_Manager.hpp"
#include "SoundManager.hpp"
#include "AudioManager.hpp"

class Map;

//TODO(robert): Remove setter and getters? Convert to pure dataclass.
//TODO(robert): Have components set nullptr in the SharedContext when destructors called to prevent access.
struct SharedContext {
    SharedContext():m_window(nullptr), m_eventManager(nullptr),
                    m_textureManager(nullptr), m_fontManager(nullptr),
                    m_entityManager(nullptr), m_systemManager(nullptr),
                    m_map(nullptr), m_debugOverlay(nullptr), m_debugText(nullptr),
                    m_uiManager(nullptr), m_soundManager(nullptr), m_audioManager(nullptr){}
    
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
    
    FontManager* GetFontManager()
    {
        return m_fontManager;
    }
    
    void SetFontManager(FontManager* l_fontManager)
    {
        m_fontManager = l_fontManager;
    }
    
    Map* GetMap()
    {
        return m_map;
    }
    
    void SetMap(Map* l_map)
    {
        m_map = l_map;
    }
    
    EntityManager* GetEntityManager() const
    {
        return m_entityManager;
    }
    
    void SetEntityManager(EntityManager* l_entityManager)
    {
        m_entityManager = l_entityManager;
    }
    
    SystemManager* GetSystemManager()
    {
        return m_systemManager;
    }
    
    void SetSystemManager(SystemManager* l_systemManager)
    {
        m_systemManager = l_systemManager;
    }
    
    DebugOverlay *GetDebugOverlay()
    {
        return m_debugOverlay;
    }
    
    void SetDebugOverlay(DebugOverlay *l_debugOverlay)
    {
        m_debugOverlay = l_debugOverlay;
    }
    
    Textbox* GetDebugText()
    {
        return m_debugText;
    }
    
    void SetDebugText(Textbox* l_textbox)
    {
        m_debugText = l_textbox;
    }
    
    UI_Manager* GetUIManager()
    {
        return m_uiManager;
    }
    
    void SetUIManager(UI_Manager* l_uiManager)
    {
        m_uiManager = l_uiManager;
    }

    SoundManager* GetSoundManager()
    {
        return m_soundManager;
    }

    void SetSoundManager(SoundManager* l_soundManager)
    {
        m_soundManager = l_soundManager;
    }

    AudioManager* GetAudioManager()
    {
        return m_audioManager;
    }

    void SetAudioManager(AudioManager* l_audioManager)
    {
        m_audioManager = l_audioManager;
    }
    
private:
    Window* m_window;
    EventManager* m_eventManager;
    TextureManager* m_textureManager;
    FontManager* m_fontManager;
    EntityManager* m_entityManager;
    SystemManager* m_systemManager;
    Map* m_map;
    DebugOverlay* m_debugOverlay;
    Textbox* m_debugText;
    UI_Manager* m_uiManager;
    SoundManager* m_soundManager;
    AudioManager* m_audioManager;
};

#endif /* SharedContext_h */
