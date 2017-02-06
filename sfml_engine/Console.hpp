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
    Console(sf::RenderWindow* wind);
    ~Console();
    
    void Add(const std::string& l_name, Command l_cmd);
    void Remove(const std::string& l_name);
    
    void HandleTextInput(EventDetails* l_details);
    void Backspace(EventDetails* l_details);
    void ValidateInput(EventDetails* l_details);
    void CycleInput(EventDetails* l_details);
    
    void Draw(sf::RenderWindow* l_wind);
    
    void Open();
    
    void Close();
 
private:
    void Purge();
    void UpdateText();
    void ParseCommand();
    void Print(const std::string& l_str);
    std::vector<std::string> Tokenize(const std::string& l_input, char l_delim);
    
    bool m_show;
    int m_maxBufferLength;
    int m_maxBufferLines;
    sf::Text m_inputText;
    sf::Text m_outputText;
    sf::Text m_inputPreText;
    std::map<std::string, Command> m_commands;
    std::string m_inputBuffer;
    std::list<std::string> m_outputBuffer;
    sf::Font m_textFont;
    sf::RectangleShape m_backgroundOut;
    sf::RectangleShape m_backgroundIn;
    
};

#endif /* Console_hpp */
