//
//  Console.cpp
//  sfml_engine
//
//  Created by Robert Wells on 05/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#include "Console.hpp"


Console::Console(sf::RenderWindow* l_wind)
{
    m_maxBufferLength = 20;
    m_maxBufferLines = 12;
    
    const sf::Vector2u windSize = l_wind->getSize();
    const sf::Uint16 offset = l_wind->getSize().x * 0.1;
    const sf::Uint8 characterSize = 14;
    
    m_backgroundOut.setSize(sf::Vector2f(windSize.x - offset * 2, windSize.y * 0.4));
    m_backgroundOut.setFillColor(sf::Color(90, 90, 90, 120));
    m_backgroundOut.setPosition(offset, 0);
    
    m_backgroundIn.setSize(sf::Vector2f(windSize.x - offset * 2, characterSize * 2));
    m_backgroundIn.setFillColor(sf::Color(90, 90, 90, 90));
    m_backgroundIn.setPosition(offset, m_backgroundOut.getSize().y - m_backgroundIn.getSize().y);
    
    m_textFont.loadFromFile(resourcePath() + "media/Fonts/arial.ttf");
    
    m_inputText.setFont(m_textFont);
    m_inputText.setCharacterSize(characterSize);
    m_inputText.setFillColor(sf::Color::Black);
    m_inputText.setPosition(offset + characterSize,
                            m_backgroundIn.getPosition().y + (m_backgroundIn.getSize().y * 0.5) - (characterSize * 0.5));
    
    m_outputText.setFont(m_textFont);
    m_outputText.setCharacterSize(characterSize);
    m_outputText.setFillColor(sf::Color::Black);
    m_outputText.setPosition(offset + characterSize, m_backgroundOut.getPosition().y + characterSize);
    

    m_inputPreText.setFont(m_textFont);
    m_inputPreText.setString(">");
    m_inputPreText.setCharacterSize(characterSize);
    m_inputPreText.setPosition(offset, m_backgroundIn.getPosition().y + (m_backgroundIn.getSize().y * 0.5) - (characterSize * 0.5));
    
    Command c = [this](std::vector<std::string> l) -> std::string
    {
        Print("commands:");
        
        for(const auto& i : m_commands) {
            Print(i.first);
        }
        
        return std::to_string(m_commands.size()) + " commands found.";
        
    };
    Add("list_commands", c);
    
    Command clear = [this](std::vector<std::string> l) -> std::string
    {
        Purge();
        return "";
        
    };
    Add("clear", clear);

    m_show = false;
}

Console::~Console()
{
    // what do i need to remove?
}

void Console::Open()
{
    m_show = true;
}

void Console::Close()
{
    m_show = false;
}

void Console::Draw(sf::RenderWindow* l_wind)
{
    l_wind->draw(m_backgroundOut);
    l_wind->draw(m_backgroundIn);
    
    l_wind->draw(m_inputPreText);
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

void Console::HandleTextInput(EventDetails* l_details)
{
    if(m_show)
    {
        const sf::Uint32& textEntered = l_details->GetTextEntered();
        
        if (textEntered > 31
            && textEntered < 127
            && m_inputBuffer.size() < m_maxBufferLength)
        {
            m_inputBuffer += static_cast<char>(textEntered);
            UpdateText();
        }

    }
}

void Console::ValidateInput(EventDetails* l_details)
{
    if(m_show)
    {
        ParseCommand();
    }
}

void Console::Backspace(EventDetails* l_details)
{
    if(m_show)
    {
        if(!m_inputBuffer.empty()){
            m_inputBuffer.pop_back();
            UpdateText();
        }
    }
}

//TODO: implement input cycling
void Console::CycleInput(EventDetails* l_details)
{
    if(l_details->GetKeyCode() == sf::Keyboard::Up){
        
    } else if(l_details->GetKeyCode() == sf::Keyboard::Down){
        
    }
}

/*
void Console::HandleEvent(EventDetails* l_details)
{
    if(m_show)
    {
        if(l_details-> == sf::Event::TextEntered)
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
 */


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

void Console::Purge()
{
    if(!m_outputBuffer.empty()){
        m_outputBuffer.clear();
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
