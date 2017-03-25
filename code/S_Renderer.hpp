//
//  S_Renderer.hpp
//  sfml_engine
//
//  Created by Robert Wells on 10/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef S_Renderer_hpp
#define S_Renderer_hpp

#include "S_Base.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Window.hpp"

class S_Renderer : public S_Base
{
public:
    S_Renderer(SystemManager* l_systemMgr);
    ~S_Renderer();
    
    void Update(float l_dT);
    void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event);
    void Notify(const Message& l_message);
    void Render(Window* l_wind, unsigned int l_layer);
private:
    void SetSheetDirection(const EntityId& l_entity, const Direction& l_dir);
    void SortDrawables();
};

#endif /* S_Renderer_hpp */
