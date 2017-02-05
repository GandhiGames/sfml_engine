//
//  Console.hpp
//  sfml_engine
//
//  Created by Robert Wells on 05/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef Console_hpp
#define Console_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <sstream>
#include "Window.hpp"

typedef std::function<std::string(std::vector<std::string>&)> Command;

class Console {
public:
    Console();
    ~Console();
    
    void Add(const std::string& l_name, Command l_cmd);
    void Remove(const std::string& l_name);
    
    void HandleEvent(const sf::Event& l_event);
    
    void Draw(sf::RenderWindow* l_wind);
private:
    void UpdateText();
    void ParseCommand();
    void Print(const std::string& l_str);
    
    std::vector<std::string> Tokenize(const std::string& l_input, char l_delim);
    
    sf::View m_view;
    bool m_show;
    int m_maxBufferLength;
    int m_maxBufferLines;
    sf::Text m_inputText;
    sf::Text m_outputText;
    std::map<std::string, Command> m_commands;
    std::string m_inputBuffer;
    std::list<std::string> m_outputBuffer;
    sf::Font m_textFont;
    
};

#endif /* Console_hpp */
