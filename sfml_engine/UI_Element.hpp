//
//  UI_Element.hpp
//  sfml_engine
//
//  Created by Robert Wells on 14/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef UI_Element_hpp
#define UI_Element_hpp

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>
#include <unordered_map>

#include "UI_Style.h"
#include <sstream>

enum class UI_ElementType{ None = -1, Window, Label, Button, Scrollbar, Textfield };

using ElementStyles = std::unordered_map<UI_ElementState, UI_Style>;

class UI_Interface;

class UI_Element{
    friend class UI_Interface;
public:
    UI_Element(const std::string& l_name, const UI_ElementType& l_type, UI_Interface* l_owner);
    virtual ~UI_Element();
    
    // Event methods.
    virtual void ReadIn(std::stringstream& l_stream) = 0;
    virtual void OnClick(const sf::Vector2f& l_mousePos) = 0;
    virtual void OnRelease() = 0;
    virtual void OnHover(const sf::Vector2f& l_mousePos) = 0;
    virtual void OnLeave() = 0;
    virtual void Update(float l_dT) = 0;
    virtual void Draw(sf::RenderTarget* l_target) = 0;
    
    // Non pure-virtual methods.
    virtual void UpdateStyle(const UI_ElementState& l_state, const UI_Style& l_style);
    virtual void ApplyStyle();
    
    UI_ElementType GetType();
    
    const std::string& GetName() const;
    void SetName(const std::string& l_name);
    const sf::Vector2f& GetPosition() const;
    void SetPosition(const sf::Vector2f& l_pos);
    const sf::Vector2f& GetSize() const;
    UI_ElementState GetState() const;
    void SetState(const UI_ElementState& l_state);
    void SetRedraw(const bool& l_redraw);
    bool NeedsRedraw() const;
    void SetOwner(UI_Interface* l_owner);
    UI_Interface* GetOwner() const;
    bool HasOwner() const;
    bool IsActive() const;
    void SetActive(const bool& l_active);
    bool IsInside(const sf::Vector2f& l_point) const;
    sf::Vector2f GetGlobalPosition() const;
    bool IsControl() const;
    std::string GetText() const;
    void SetText(const std::string& l_text);
    
    friend std::stringstream& operator >>(std::stringstream& l_stream, UI_Element& b)
    {
        b.ReadIn(l_stream);
        return l_stream;
    }
protected:
    void ApplyTextStyle();
    void ApplyBgStyle();
    void ApplyGlyphStyle();
    
    void RequireTexture(const std::string& l_name);
    void RequireFont(const std::string& l_name);
    void ReleaseTexture(const std::string& l_name);
    void ReleaseFont(const std::string& l_name);
    void ReleaseResources();
    
    std::string m_name;
    sf::Vector2f m_position;
    ElementStyles m_style; // Style of drawables.
    UI_Visual m_visual; // Drawable bits.
    UI_ElementType m_type;
    UI_ElementState m_state;
    UI_Interface* m_owner;
    
    bool m_needsRedraw;
    bool m_active;
    bool m_isControl;
};

#endif /* UI_Element_hpp */
