//
//  Communicator.hpp
//  sfml_engine
//
//  Created by Robert Wells on 09/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef Communicator_hpp
#define Communicator_hpp

#include <vector>
#include "Observer.hpp"

using ObserverContainer = std::vector<Observer*>;

class Communicator{
public:
    ~Communicator(){ m_observers.clear(); }
    
    bool AddObserver(Observer* l_observer){
        if (HasObserver(l_observer)){ return false; }
        m_observers.emplace_back(l_observer);
        return true;
    }
    
    bool RemoveObserver(Observer* l_observer){
        auto observer = std::find_if(m_observers.begin(), m_observers.end(),
                                     [&l_observer](Observer* o){ return o == l_observer; });
        if (observer == m_observers.end()){ return false; }
        m_observers.erase(observer);
        return true;
    }
    
    bool HasObserver(const Observer* l_observer){
        return (std::find_if(m_observers.begin(), m_observers.end(),
                             [&l_observer](Observer* o){ return o == l_observer; }) != m_observers.end());
    }
    
    void Broadcast(const Message& l_msg){
        for(auto& itr : m_observers){ itr->Notify(l_msg); }
    }
    
private:
    ObserverContainer m_observers;
};

#endif /* Communicator_hpp */
