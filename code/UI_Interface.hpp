//
//  UI_Interface.hpp
//  sfml_engine
//
//  Created by Robert Wells on 14/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef UI_Interface_hpp
#define UI_Interface_hpp

#include "UI_Element.hpp"
#include "Utilities.h"
#include <unordered_map>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

using Elements = std::unordered_map<std::string, UI_Element*>;

class UI_Manager;

class UI_Interface : public UI_Element{
    friend class GUI_Element;
    friend class GUI_Manager;
public:
    UI_Interface(const std::string& l_name, UI_Manager* l_guiManager);
    ~UI_Interface();
    
    void SetPosition(const sf::Vector2f& l_pos);
    
    bool AddElement(const UI_ElementType& l_type, const std::string& l_name);
    UI_Element* GetElement(const std::string& l_name) const;
    bool RemoveElement(const std::string& l_name);
    
    bool HasParent() const;
    UI_Manager* GetManager() const;
    
    bool IsInside(const sf::Vector2f& l_point) const;
    
    void Focus();
    void Defocus();
    bool IsFocused();
    
    void ReadIn(std::stringstream& l_stream);
    void OnClick(const sf::Vector2f& l_mousePos);
    void OnRelease();
    void OnHover(const sf::Vector2f& l_mousePos);
    void OnLeave();
    void OnTextEntered(const char& l_char);
    
    bool IsBeingMoved() const;
    bool IsMovable() const;
    void BeginMoving();
    void StopMoving();
    
    void ApplyStyle();
    
    const sf::Vector2f& GetPadding() const;
    void SetPadding(const sf::Vector2f& l_padding);
    sf::Vector2f GetGlobalPosition() const;
    const sf::Vector2f& GetContentSize() const;
    
    void Redraw();
    bool NeedsContentRedraw() const;
    void RedrawContent();
    bool NeedsControlRedraw() const;
    void RedrawControls();
    
    void ToggleTitleBar();
    
    void Update(float l_dT);
    void Draw(sf::RenderTarget* l_target);
    
    void UpdateScrollHorizontal(unsigned int l_percent);
    void UpdateScrollVertical(unsigned int l_percent);
    
    void AdjustContentSize(const UI_Element* l_reference = nullptr);
    
    int GetScrollHorizontal();
    int GetScrollVertical();
    
    void SetContentSize(const sf::Vector2f& l_vec);
    
private:
    void DefocusTextfields();
    
    Elements m_elements;
    sf::Vector2f m_elementPadding;
    
    UI_Interface* m_parent;
    UI_Manager* m_guiManager;
    
    sf::RenderTexture* m_backdropTexture;
    sf::Sprite m_backdrop;
    
    // Movement.
    sf::RectangleShape m_titleBar;
    sf::Vector2f m_moveMouseLast;
    bool m_showTitleBar;
    bool m_movable;
    bool m_beingMoved;
    bool m_focused;

    sf::RenderTexture* m_contentTexture;
    sf::Sprite m_content;
    sf::Vector2f m_contentSize;
    int m_scrollHorizontal;
    int m_scrollVertical;
    bool m_contentRedraw;
    
    // Control layer.
    sf::RenderTexture* m_controlTexture;
    sf::Sprite m_control;
    bool m_controlRedraw;
};

#endif /* UI_Interface_hpp */
