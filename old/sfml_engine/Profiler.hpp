//
//  Profiler.hpp
//  sfml_engine
//
//  Created by Robert Wells on 13/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef Profiler_hpp
#define Profiler_hpp

#include <SFML/System.hpp>

class Profiler{
public:
    void Start();
    sf::Time GetElapsed();
    
private:
    sf::Clock m_clock;
};

#endif /* Profiler_hpp */
