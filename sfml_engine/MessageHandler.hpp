//
//  MessageHandler.hpp
//  sfml_engine
//
//  Created by Robert Wells on 09/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef MessageHandler_hpp
#define MessageHandler_hpp

#include "Communicator.hpp"
#include "EntityMessage.hpp"
#include <unordered_map>

using Subscribtions = std::unordered_map<EntityMessage,Communicator>;

class MessageHandler{
public:
    bool Subscribe(const EntityMessage& l_type, Observer* l_observer)
    {
        return m_communicators[l_type].AddObserver(l_observer);
    }
    
    bool Unsubscribe(const EntityMessage& l_type, Observer* l_observer)
    {
        return m_communicators[l_type].RemoveObserver(l_observer);
    }
    
    void Dispatch(const Message& l_msg){
        auto itr = m_communicators.find((EntityMessage)l_msg.m_type);
        if (itr == m_communicators.end()){  return; }
        itr->second.Broadcast(l_msg);
    }
private:
    Subscribtions m_communicators;
};

#endif /* MessageHandler_hpp */
