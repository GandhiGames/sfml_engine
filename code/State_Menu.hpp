//
//  State_Menu.hpp
//  sfml_engine
//
//  Created by Robert Wells on 03/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef State_Menu_hpp
#define State_Menu_hpp

#include "BaseState.h"
#include "EventManager.hpp"

class State_Menu : public BaseState {
public:
    State_Menu(StateManager &l_stateManager);
    ~State_Menu();
    
    void OnCreate();
    void OnDestroy();
    
    void Activate();
    void Deactivate();
    
    void Update(const sf::Time &l_time);
    void Draw();
    
    void MenuSelectionUp(EventDetails* l_details);
    void MenuSelectionDown(EventDetails* l_details);
    void ValidateSelection(EventDetails* l_details);
    
private:
    sf::Text m_text;
    
    sf::Vector2f m_buttonSize;
    sf::Vector2f m_buttonPos;
    
    unsigned int m_buttonPadding;
    
    sf::RectangleShape m_rects[3];
    sf::Text m_labels[3];
    
    sf::Uint8 m_selectedIndex;
    
    void IncrementSelect(const sf::Int8& l_increment);
    
};

#endif /* State_Menu_hpp */
