//
//  Profiler.cpp
//  sfml_engine
//
//  Created by Robert Wells on 13/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#include "Profiler.hpp"

void Profiler::Start()
{
    m_clock.restart();
}

sf::Time Profiler::GetElapsed()
{
    return m_clock.getElapsedTime();
}
