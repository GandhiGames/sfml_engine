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

class Window {
public:
    Window();
    Window(const std::string &l_title, const sf::Vector2u &l_size);
    ~Window();
    
    void BeginDraw(); // clear the window.
    void EndDraw(); // display the changes.
    
    void Update();
    
    bool IsDone();
    bool IsFullScreen();
    
    const sf::Vector2u* GetWindowSize();
    
    void ToggleFullScreen();
    
    void Draw(const sf::Drawable &l_drawable);
    
private:
    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    bool m_isFullScreen;
    
    void Setup(const std::string &l_title, const sf::Vector2u &l_size);
    void Destroy();
    void Create();
    
};

#endif /* Window_hpp */
