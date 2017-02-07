//
//  ConsoleCommand.hpp
//  sfml_engine
//
//  Created by Robert Wells on 07/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef ConsoleCommand_hpp
#define ConsoleCommand_hpp


#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>


class ConsoleCommand{
public:
    ConsoleCommand(std::function<std::string(std::vector<std::string>& l_cmds)>& l_func,
        sf::Uint8 l_minArguements,
        sf::Uint8 l_maxArguements,
        const sf::String& l_help)
    : m_func(l_func), m_minArguements(l_minArguements), m_maxArguements(l_maxArguements), m_help(l_help){}
    
    ~ConsoleCommand(){}

    std::string Run(std::vector<std::string>& l_cmds) { return m_func(l_cmds); }
    
    const sf::Uint8& GetMinArguementCount(){ return m_minArguements; }
    const sf::Uint8& GetMaxArguementCount(){ return m_maxArguements; }
    const sf::String& HelpOutput(){ return m_help; }

    
private:
    const std::function<std::string(std::vector<std::string>& func)> m_func;
    const sf::Uint8 m_minArguements;
    const sf::Uint8 m_maxArguements;
    const sf::String m_help;
};

#endif /* ConsoleCommand_hpp */
