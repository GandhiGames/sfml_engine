//
//  UI_Event.h
//  sfml_engine
//
//  Created by Robert Wells on 14/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef UI_Event_h
#define UI_Event_h

#include <string>

enum class UI_EventType{ None, Click, Release, Hover, Leave };

struct ClickCoordinates{
    float x, y;
};

struct UI_Event{
    UI_EventType m_type;
    const char* m_element;
    const char* m_interface;
    union{
        ClickCoordinates m_clickCoords;
    };
};

#endif /* UI_Event_h */
