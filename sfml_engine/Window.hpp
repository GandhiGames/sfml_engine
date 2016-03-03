//
//  Window.hpp
//  sfml_engine
//
//  Created by Robert Wells on 23/02/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp
 
#include <SFML/Graphics.hpp>
#include "EventManager.hpp"

class Window {
public:
    Window();
    Window(const std::string &l_title, const sf::Vector2u &l_size);
    ~Window();
    
    void BeginDraw(); // clear the window.
    void EndDraw(); // display the changes.
    
    void Update();
    
    const bool& IsDone() const;
    const bool& IsFullScreen() const;
    const bool& IsFocused() const;
    
    const sf::Vector2u & GetWindowSize() const;
    
    void ToggleFullScreen(EventDetails *l_details = nullptr);
    void Close(EventDetails *l_details = nullptr);
   
     void Draw(const sf::Drawable &l_drawable);

    sf::RenderWindow *GetRenderWindow();
    EventManager *GetEventManager();
    
private:
    EventManager m_eventManager;
    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    bool m_isFullScreen;
    bool m_isFocused;
    
    void Setup(const std::string &l_title, const sf::Vector2u &l_size);
    void Destroy();
    void Create();
    
};

#endif /* Window_hpp */
