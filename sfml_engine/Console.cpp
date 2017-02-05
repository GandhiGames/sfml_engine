//
//  Console.cpp
//  sfml_engine
//
//  Created by Robert Wells on 05/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#include "Console.hpp"


Console::Console()
{
    m_textFont.loadFromFile(resourcePath() + "media/Fonts/arial.ttf");
    
    m_inputText.setFont(m_textFont);
    m_inputText.setCharacterSize(12);
    m_inputText.setFillColor(sf::Color::Black);
    m_inputText.setPosition(0, 600);
    
    m_outputText.setFont(m_textFont);
    m_outputText.setCharacterSize(12);
    m_outputText.setFillColor(sf::Color::Black);
    m_outputText.setPosition(0, 600);
    
    m_maxBufferLength = 20;
    m_maxBufferLines = 10;

    
    Command c = [this](std::vector<std::string> l) -> std::string
    {
        for(const auto& i : m_commands)
            Print(i.first);
        
        return std::to_string(m_commands.size()) + " commands found.";
        
    };
    
    Add("list_commands", c);
    
    
    
    m_show = true;
}

Console::~Console()
{
    // what do i need to remove?
}

void Console::Draw(sf::RenderWindow* l_wind)
{
    //l_wind->setView(m_view);
    
    l_wind->draw(m_inputText);
    l_wind->draw(m_outputText);
}

void Console::Add(const std::string& l_name, Command l_cmd)
{
    if(m_commands.find(l_name) == m_commands.end()){
        m_commands.insert(std::make_pair(l_name, l_cmd));
    }
}

void Console::Remove(const std::string& l_name)
{
    const auto c = m_commands.find(l_name);
    if(c != m_commands.end()) {
        m_commands.erase(c);
    }
}

void Console::HandleEvent(const sf::Event& l_event)
{

    if(m_show)
    {
        std::cout << l_event.type <<std::endl;
        if(l_event.type == sf::Event::TextEntered)
        {
            std::cout << "here 3" <<std::endl;
            if (l_event.text.unicode > 31
                && l_event.text.unicode < 127
                && m_inputBuffer.size() < m_maxBufferLength)
            {
                m_inputBuffer += static_cast<char>(l_event.text.unicode);
                UpdateText();
            }
        }
        
        else if(l_event.type == sf::Event::KeyPressed)
        {
              std::cout << "here 4" <<std::endl;
            switch(l_event.key.code)
            {
                case sf::Keyboard::BackSpace:
                    if(!m_inputBuffer.empty()) { m_inputBuffer.pop_back(); }
                    UpdateText();
                    break;
                case sf::Keyboard::Return:
                    ParseCommand();
                    break;
            }
        }
    }
}

void Console::Print(const std::string& l_str)
{
    m_outputBuffer.push_back(l_str);
    
    if(m_outputBuffer.size() > m_maxBufferLines){
        m_outputBuffer.pop_front();
    }
    
    if(m_show){
        UpdateText();
    }
}

void Console::UpdateText()
{
    m_inputText.setString(m_inputBuffer);
    
    std::string output;
    for(const auto& s : m_outputBuffer)
        output += s + "\n";
    
    m_outputText.setString(output);
}

void Console::ParseCommand()
{
    if(!m_inputBuffer.empty())
    {
        std::vector<std::string> commands = Tokenize(m_inputBuffer, ' ');
        const auto c = m_commands.find(commands[0]);
        if(c != m_commands.end())
        {
            commands.erase(commands.begin());
            std::string result = c->second(commands);
            if(!result.empty()) { Print(result); }
        }
        else
        {
            Print(commands[0] + ": command not found");
        }
        
        m_inputBuffer.clear();
        UpdateText();
    }
}

//TODO: implement boost as tokenizer.
std::vector<std::string> Console::Tokenize(const std::string& l_input, char l_delim)
{
    std::vector<std::string> out;
    
    std::stringstream ss;
    ss.str(l_input);
    std::string item;
    
    while (std::getline(ss, item, l_delim)) {
        if(!item.empty()){
            out.emplace_back(item);
        }
    }
    
    return out;
}
