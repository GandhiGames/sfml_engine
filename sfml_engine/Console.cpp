//
//  Console.cpp
//  sfml_engine
//
//  Created by Robert Wells on 05/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#include "Console.hpp"

//TODO: create correct resource request for font.
//TODO: add scrollbar for output - control by keyboard?
Console::Console(sf::RenderWindow* l_wind)
{
    const sf::Vector2u windSize = l_wind->getSize();
    
    m_characterSize = 14;
    m_maxBufferLength = 30;
    m_commandCacheSize = 10;
    m_moveInPixelsPerSec = 600;
    m_moveOutPixelsPerSec = 800;
    m_percentScreen = 0.3;
    m_xOffset = l_wind->getSize().x * 0.05;
    m_moveOffset = windSize.y * m_percentScreen;
    m_maxBufferLines = (m_moveOffset / (m_characterSize + 3)) - 1;
    
    m_backgroundOut.setSize(sf::Vector2f(windSize.x - m_xOffset * 2, m_moveOffset));
    m_backgroundOut.setFillColor(sf::Color(90, 90, 90, 180));
    m_backgroundOut.setPosition(m_xOffset, 0);
    
    m_backgroundIn.setSize(sf::Vector2f(windSize.x - m_xOffset * 2, m_characterSize * 2));
    m_backgroundIn.setFillColor(sf::Color(90, 90, 90, 180));
    m_backgroundIn.setPosition(m_xOffset,
                             m_backgroundOut.getPosition().y + m_backgroundOut.getSize().y - m_backgroundIn.getSize().y);
    
    m_textFont.loadFromFile(resourcePath() + "media/Fonts/arial.ttf");
    
    m_inputText.setFont(m_textFont);
    m_inputText.setCharacterSize(m_characterSize);
    m_inputText.setFillColor(sf::Color::Black);
    m_inputText.setPosition(m_xOffset + m_characterSize,
                            m_backgroundIn.getPosition().y + (m_backgroundIn.getSize().y * 0.5) - (m_characterSize * 0.5));
    
    m_outputText.setFont(m_textFont);
    m_outputText.setCharacterSize(m_characterSize);
    m_outputText.setFillColor(sf::Color::Black);
    m_outputText.setPosition(m_xOffset + m_characterSize, m_backgroundOut.getPosition().y + 5);
    
    
    m_inputPreText.setFont(m_textFont);
    m_inputPreText.setString(">");
    m_inputPreText.setCharacterSize(m_characterSize);
    m_inputPreText.setPosition(m_xOffset, m_backgroundIn.getPosition().y + (m_backgroundIn.getSize().y * 0.5) - (m_characterSize * 0.5));
    
    Command listCommands = [this](std::vector<std::string> l) -> std::string
    {
        Print("commands:");
        
        for(const auto& i : m_commands) {
            Print(i.first);
        }
        
        return std::to_string(m_commands.size()) + " commands found.";
        
    };
    Add("list_commands", listCommands);
    
    Command clear = [this](std::vector<std::string> l) -> std::string
    {
        Purge();
        return "";
        
    };
    Add("clear", clear);
    
    Command exit = [this](std::vector<std::string> l) -> std::string
    {
        Close();
        return "";
        
    };
    Add("exit", exit);
    
    m_isOpen = false;
    m_shouldOpen = false;
}

Console::~Console()
{
    // what do i need to remove?
}

void Console::Open()
{
    m_inputBuffer.erase();
    UpdateText();
    
    m_backgroundOut.setPosition(m_xOffset, 0 - m_moveOffset);
    m_backgroundIn.setPosition(m_xOffset,
                               m_backgroundOut.getPosition().y + m_backgroundOut.getSize().y - m_backgroundIn.getSize().y);
    m_inputText.setPosition(m_xOffset + m_characterSize,
                            m_backgroundIn.getPosition().y + (m_backgroundIn.getSize().y * 0.5) - (m_characterSize * 0.5));
    m_outputText.setPosition(m_xOffset + m_characterSize, m_backgroundOut.getPosition().y + 5);
    
    m_inputPreText.setPosition(m_xOffset, m_backgroundIn.getPosition().y + (m_backgroundIn.getSize().y * 0.5) - (m_characterSize * 0.5));
    
    m_shouldClose = false;
    m_accumulatedMove = 0;
    m_shouldOpen = true;
}

void Console::Close()
{
    m_shouldOpen = false;
    m_accumulatedMove = 0;
    m_shouldClose = true;

}

void Console::Draw(sf::RenderWindow* l_wind)
{
    l_wind->draw(m_backgroundOut);
    l_wind->draw(m_backgroundIn);
    
    l_wind->draw(m_inputPreText);
    l_wind->draw(m_inputText);
    l_wind->draw(m_outputText);
    
}

void Console::Update(const float& l_dt)
{
    if(m_shouldOpen){
 
        m_backgroundIn.setPosition(m_xOffset, m_backgroundIn.getPosition().y + m_moveInPixelsPerSec * l_dt);
        m_backgroundOut.setPosition(m_xOffset, m_backgroundOut.getPosition().y + m_moveInPixelsPerSec * l_dt);
        m_inputText.setPosition(m_inputText.getPosition().x, m_inputText.getPosition().y + m_moveInPixelsPerSec * l_dt);
        m_outputText.setPosition(m_outputText.getPosition().x, m_outputText.getPosition().y + m_moveInPixelsPerSec * l_dt);
        m_inputPreText.setPosition(m_inputPreText.getPosition().x, m_inputPreText.getPosition().y + m_moveInPixelsPerSec * l_dt);
        
        m_accumulatedMove += m_moveInPixelsPerSec * l_dt;
        
        if(m_accumulatedMove >= m_moveOffset){
            m_backgroundOut.setPosition(m_xOffset, 0);
            m_backgroundIn.setPosition(m_xOffset, m_backgroundOut.getPosition().y + m_backgroundOut.getSize().y - m_backgroundIn.getSize().y);
            m_inputText.setPosition(m_xOffset + m_characterSize,
                                    m_backgroundIn.getPosition().y + (m_backgroundIn.getSize().y * 0.5) - (m_characterSize * 0.5));
            m_outputText.setPosition(m_xOffset + m_characterSize, m_backgroundOut.getPosition().y + 5);
            
            m_inputPreText.setPosition(m_xOffset, m_backgroundIn.getPosition().y + (m_backgroundIn.getSize().y * 0.5) - (m_characterSize * 0.5));
            
            m_shouldOpen = false;
            m_isOpen = true;
        }
    }else if(m_shouldClose){
        
        m_backgroundIn.setPosition(m_xOffset, m_backgroundIn.getPosition().y - m_moveOutPixelsPerSec * l_dt);
        m_backgroundOut.setPosition(m_xOffset,  m_backgroundOut.getPosition().y - m_moveOutPixelsPerSec * l_dt);
        m_inputText.setPosition(m_inputText.getPosition().x, m_inputText.getPosition().y - m_moveOutPixelsPerSec * l_dt);
        m_outputText.setPosition(m_outputText.getPosition().x, m_outputText.getPosition().y - m_moveOutPixelsPerSec * l_dt);
        m_inputPreText.setPosition(m_inputPreText.getPosition().x, m_inputPreText.getPosition().y - m_moveOutPixelsPerSec * l_dt);
        
         m_accumulatedMove += m_moveOutPixelsPerSec * l_dt;
        
        if(m_accumulatedMove >= m_moveOffset){
            m_backgroundOut.setPosition(m_xOffset, 0 - m_moveOffset);
            m_backgroundIn.setPosition(m_xOffset, m_backgroundOut.getPosition().y + m_backgroundOut.getSize().y - m_backgroundIn.getSize().y);
            
            m_inputText.setPosition(m_xOffset + m_characterSize,
                                    m_backgroundIn.getPosition().y + (m_backgroundIn.getSize().y * 0.5) - (m_characterSize * 0.5));
            m_outputText.setPosition(m_xOffset + m_characterSize, m_backgroundOut.getPosition().y + 5);
            
            m_inputPreText.setPosition(m_xOffset, m_backgroundIn.getPosition().y + (m_backgroundIn.getSize().y * 0.5) - (m_characterSize * 0.5));
            m_shouldClose = false;
            m_isOpen = false;
        }
    }
}

bool Console::IsOpen()
{
    return m_shouldOpen || m_isOpen;
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
    if(c != m_commands.end()){
        m_commands.erase(c);
    }
}

void Console::HandleTextInput(EventDetails* l_details)
{
    if(m_isOpen){
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
    if(m_isOpen){
        ParseCommand();
    }
}

void Console::Backspace(EventDetails* l_details)
{
    if(m_isOpen){
        if(!m_inputBuffer.empty()){
            m_inputBuffer.pop_back();
            UpdateText();
        }
    }
}

//TODO: implement input cycling
void Console::CycleInputUp(EventDetails* l_details)
{
    if(m_inputCommands.size() > 0){
        
        m_InputCommandsIndex--;
        
        if(m_InputCommandsIndex < 0){
            m_InputCommandsIndex = 0;
        }
        
        UpdateTextFromCurrentCommand();
    }
}

void Console::CycleInputDown(EventDetails* l_details)
{
    if(m_inputCommands.size() > 0){
        
        m_InputCommandsIndex++;
        
        if(m_InputCommandsIndex > m_inputCommands.size() - 1){
            m_InputCommandsIndex = m_inputCommands.size() - 1;
            
            m_inputBuffer.erase();
            UpdateText();
        } else{
            UpdateTextFromCurrentCommand();
        }
    }
}

void Console::UpdateTextFromCurrentCommand()
{
    m_inputBuffer = m_inputCommands[m_InputCommandsIndex];
    
    UpdateText();
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
    
    if(m_isOpen){
        UpdateText();
    }
}

void Console::UpdateText()
{
    m_inputText.setString(m_inputBuffer);
    
    std::string output;
    for(const auto& s : m_outputBuffer){
        output += s + "\n";
    }
    
    m_outputText.setString(output);
}

void Console::ParseCommand()
{
    if(!m_inputBuffer.empty()){
        std::vector<std::string> commands = Tokenize(m_inputBuffer, ' ');
        const auto c = m_commands.find(commands[0]);
        if(c != m_commands.end()){
            commands.erase(commands.begin());
            std::string result = c->second(commands);
            if(!result.empty()) { Print(result); }
        }else{
            Print(commands[0] + ": command not found");
        }
        
        m_inputCommands.emplace_back(m_inputBuffer);
        
        if(m_inputCommands.size() > m_commandCacheSize){
            m_inputCommands.erase(m_inputCommands.begin());
        }
        
        m_InputCommandsIndex = m_inputCommands.size();
        
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
    
    while (std::getline(ss, item, l_delim)){
        if(!item.empty()){
            out.emplace_back(item);
        }
    }
    
    return out;
}
