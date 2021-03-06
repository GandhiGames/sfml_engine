//
//  Console.cpp
//  sfml_engine
//
//  Created by Robert Wells on 05/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#include "Console.hpp"

//TODO: create correct resource request for font.
//TODO: create correct resource request for shader.
Console::Console(sf::RenderWindow* l_wind, FontManager& l_fontManager) : m_cursor(0.6), m_fontManager(l_fontManager)
{    
    m_screenSize = l_wind->getSize();
    m_characterSize = 14;
    m_maxBufferLength = 30;
    m_maxBufferLines = 40;
    m_commandCacheSize = 10;
    m_xOffset = m_screenSize.x * 0.05;
    m_state = ConsoleState::None;
    m_cursorIndex = 0;
    m_currentViewLineIndex = 0;
    m_percentScreen = 0;
    
    m_backgroundOut.setFillColor(sf::Color(90, 90, 90, 180));
    m_backgroundIn.setFillColor(sf::Color(90, 90, 90, 180));
    
    if(m_fontManager.RequireResource("Default")){
        m_textFont = m_fontManager.GetResource("Default");
    }
 
    m_inputText.setFont(*m_textFont);
    m_inputText.setCharacterSize(m_characterSize);
    m_inputText.setFillColor(sf::Color::Black);
    m_outputText.setFont(*m_textFont);
    m_outputText.setCharacterSize(m_characterSize);
    m_outputText.setFillColor(sf::Color::Black);
    m_inputPreText.setFont(*m_textFont);
    m_inputPreText.setString(">");
    m_inputPreText.setCharacterSize(m_characterSize);
    m_inputPreText.setFillColor(sf::Color::White);
    
    m_cursor.SetSize(sf::Vector2f(m_characterSize * 0.5f, m_characterSize));

    
    Command listCommands = [this](std::vector<std::string> l) -> std::string
    {
        Print("commands:");
        
        Print("<comand_name> 'help' : sometimes provides useful info");
        
        Print("");
        
        for(const auto& i : m_commands) {
            
            if(i.second.HelpOutput().isEmpty()){
                Print(i.first);
            }else{
                Print(i.first + ": " + i.second.HelpOutput());
            }
        }
        
        Print("");
        
        return std::to_string(m_commands.size()) + " commands found.";
        
    };
    Add("ls", listCommands, 0, 0, "lists all available commands");
    
    
    Command clear = [this](std::vector<std::string> l) -> std::string
    {
        Purge();

        return "";
    };
    Add("cls", clear, 0, 0, "clears screen");
    
    Command exit = [this](std::vector<std::string> l) -> std::string
    {
        Close(m_movePixelsPerSec);

        return "";
        
    };
    Add("exit", exit, 0, 0, "exit: closes console");
    
    Command fillScreen = [this](std::vector<std::string> l) -> std::string
    {
        for (int i = 0; i < m_maxBufferLines; i++) {
            Print(std::to_string(i));
        }
        
        return "";
        
    };
    Add("fs", fillScreen, 0, 0, "fills output buffer");

}

Console::~Console()
{
    m_fontManager.ReleaseResource("Default");
}

void Console::Build(const float& l_screenSize)
{
    m_percentScreen = l_screenSize;
    m_moveOffset = m_screenSize.y * m_percentScreen;
    m_maxLinesOnScreen = (m_moveOffset / (m_characterSize + 3)) - 1;
    
    const float width = m_screenSize.x - m_xOffset * 2;
    
    m_backgroundIn.setSize(sf::Vector2f(width, m_characterSize * 2));
    m_backgroundOut.setSize(sf::Vector2f(width, m_moveOffset));
    
    m_scrollbar.Setup(sf::Vector2f(width + m_xOffset, m_backgroundOut.getPosition().y), sf::Vector2f(25, m_backgroundOut.getSize().y - m_backgroundIn.getSize().y));
}

void Console::Open(const float& l_screenSize, const float& l_movePixelsPerSec)
{
    assert(l_screenSize > 0 && l_screenSize <= 1);
    
    bool sizeChanged = false;
    
    if(m_percentScreen != l_screenSize){
        Build(l_screenSize);

        ResetConsolePosition(ConsoleState::Closed);
        

        
        sizeChanged = true;
    }
    
    if (sizeChanged || !IsOpen()){
    
        m_movePixelsPerSec = l_movePixelsPerSec;
        
        m_inputBuffer.erase();
        UpdateTextInput();
        
        m_accumulatedMove = 0;
        
        m_state = ConsoleState::Opening;
    }
   
}

void Console::Close(const float& l_movePixelsPerSec)
{
    m_accumulatedMove = 0;
    m_movePixelsPerSec = l_movePixelsPerSec;
    m_state = ConsoleState::Closing;
}

void Console::Draw(sf::RenderWindow* l_wind)
{
    l_wind->draw(m_backgroundOut);
    l_wind->draw(m_backgroundIn);
    
    l_wind->draw(m_inputPreText);
    l_wind->draw(m_inputText);
    l_wind->draw(m_outputText);
    
    if(m_state == ConsoleState::Open){
        m_cursor.Draw(l_wind);
        
        if(m_outputBuffer.size() > m_maxLinesOnScreen){
            m_scrollbar.Draw(l_wind);
        }
    }
}

void Console::Update(const float& l_dt)
{
    switch (m_state) {
        case ConsoleState::Open:
            m_cursor.Update(l_dt);
            break;
        case ConsoleState::Opening:
            DoMovement(m_movePixelsPerSec * l_dt, ConsoleState::Open);
            break;
        case ConsoleState::Closing:
            DoMovement(-m_movePixelsPerSec * l_dt, ConsoleState::Closed);
            break;
        default:
            assert(m_state != ConsoleState::None);
            break;
    }
    
   
}

void Console::DoMovement(const float& l_moveAmount, const ConsoleState& l_goToSate)
{
    MoveConsoleVertical(l_moveAmount);
    
    m_accumulatedMove += l_moveAmount < 0 ? (l_moveAmount * -1) : l_moveAmount;
    
    if(m_accumulatedMove >= m_moveOffset){
        ResetConsolePosition(l_goToSate);
        m_state = l_goToSate;
    }

}

void Console::MoveConsoleVertical(const float& l_amount)
{
    m_backgroundIn.setPosition(m_xOffset, m_backgroundIn.getPosition().y + l_amount);
    m_backgroundOut.setPosition(m_xOffset,  m_backgroundOut.getPosition().y + l_amount);
    m_inputText.setPosition(m_inputText.getPosition().x, m_inputText.getPosition().y + l_amount);
    m_outputText.setPosition(m_outputText.getPosition().x, m_outputText.getPosition().y + l_amount);
    m_inputPreText.setPosition(m_inputPreText.getPosition().x, m_inputPreText.getPosition().y + l_amount);
}

void Console::ResetConsolePosition(const ConsoleState& l_desiredState)
{
    assert(l_desiredState == ConsoleState::Open || l_desiredState == ConsoleState::Closed);
    
    float y = l_desiredState == ConsoleState::Closed ? -m_moveOffset : 0;
    
    m_backgroundOut.setPosition(m_xOffset, y);
    m_backgroundIn.setPosition(m_xOffset, m_backgroundOut.getPosition().y + m_backgroundOut.getSize().y - m_backgroundIn.getSize().y);
    
    m_inputText.setPosition(m_xOffset + m_characterSize,
                            m_backgroundIn.getPosition().y + (m_backgroundIn.getSize().y * 0.5) - (m_characterSize * 0.5));
    
    
    
    m_inputPreText.setPosition(m_xOffset + m_inputPreText.getLocalBounds().width * 0.2, m_backgroundIn.getPosition().y + (m_backgroundIn.getSize().y * 0.5) - (m_characterSize * 0.5));
    
    m_cursor.SetPosition(sf::Vector2f(m_inputText.getPosition().x, y < 0 ?  (m_inputText.getPosition().y + m_moveOffset) : m_inputText.getPosition().y));
}

bool Console::IsOpen()
{
    return m_state != ConsoleState::Closed;
}

void Console::Add(const std::string& l_name, const std::function<std::string(std::vector<std::string>&)>& l_func, const sf::Uint8& l_minArguements, const sf::Uint8& l_maxArguements, const sf::String& l_help)
{
    if(m_commands.find(l_name) == m_commands.end()){
        ConsoleCommand cmd(l_func, l_minArguements, l_maxArguements, l_help);
        
        m_commands.insert(std::make_pair(l_name, cmd));
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
    if(m_state == ConsoleState::Open){
        const sf::Uint32& textEntered = l_details->GetTextEntered();
        
        if (textEntered > 31
            && textEntered < 127
            && m_inputBuffer.size() < m_maxBufferLength)
        {

            m_inputBuffer.insert(m_inputBuffer.begin() + m_cursorIndex, static_cast<char>(textEntered));
            
            m_cursor.SetX(m_inputText.findCharacterPos(m_cursorIndex).x + m_textFont->getGlyph(m_inputBuffer[m_cursorIndex], m_characterSize, false).bounds.width);
            
            m_cursorIndex++;

            UpdateTextInput();
        }
        
    }
}

void Console::ValidateInput(EventDetails* l_details)
{
    if(m_state == ConsoleState::Open){
        ParseCommand();
    }
}

void Console::Backspace(EventDetails* l_details)
{
      if(m_state == ConsoleState::Open){
        if(!m_inputBuffer.empty() && m_cursorIndex > 0){
            m_inputBuffer.erase(m_inputBuffer.begin() + m_cursorIndex -1);
            m_cursorIndex--;
            
 
            m_cursor.SetX(m_inputText.findCharacterPos(m_cursorIndex).x);
            
            UpdateTextInput();
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
            m_InputCommandsIndex = m_inputCommands.size();
            
            m_inputBuffer.erase();
            
            m_cursorIndex = 0;
            m_cursor.SetX(m_inputText.getPosition().x);
            
            UpdateTextInput();
        } else{
            UpdateTextFromCurrentCommand();
        }
    }
}

void Console::ScrollOutputUp(EventDetails* l_details)
{
    if(m_outputBuffer.size() < m_maxLinesOnScreen || m_currentViewLineIndex == m_outputBuffer.size()){ return; }
    
    m_currentViewLineIndex += 2;
    
    if(m_currentViewLineIndex > m_outputBuffer.size()){
        m_currentViewLineIndex = m_outputBuffer.size();
    }
    
    
    m_scrollbar.SetScrollPercent((((float)m_currentViewLineIndex - m_maxLinesOnScreen) / (m_outputBuffer.size() - m_maxLinesOnScreen)) * 100.0);
    
    
   
    
  
    
   // std::cout << std::to_string(((float)m_currentViewLineIndex / (float)m_outputBuffer.size()) * 100.0) << " ";
    
    UpdateTextOutput();
}

void Console::ScrollOutputDown(EventDetails* l_details)
{
    if(m_outputBuffer.size() < m_maxLinesOnScreen || m_currentViewLineIndex == 0){ return; }
    

    m_currentViewLineIndex -= 2;

    
    if(m_currentViewLineIndex < m_maxLinesOnScreen){
        m_currentViewLineIndex = m_maxLinesOnScreen;
    }

     m_scrollbar.SetScrollPercent((((float)m_currentViewLineIndex - m_maxLinesOnScreen) / (m_outputBuffer.size() - m_maxLinesOnScreen)) * 100.0);
    

    UpdateTextOutput();
    
}

void Console::MoveCursorLeft(EventDetails* l_details)
{
    if(m_cursorIndex > 0){
        m_cursorIndex--;
        
        m_cursor.SetX(m_inputText.findCharacterPos(m_cursorIndex).x);
    }
}

void Console::MoveCursorRight(EventDetails* l_details)
{
    if(m_cursorIndex < m_inputBuffer.size()){
        m_cursorIndex++;
        
        m_cursor.SetX(m_inputText.findCharacterPos(m_cursorIndex).x);
    }
}

void Console::UpdateTextFromCurrentCommand()
{
    m_inputBuffer = m_inputCommands[m_InputCommandsIndex];
    m_cursorIndex = m_inputBuffer.size();
    
    UpdateTextInput();
    
    m_cursor.SetX(m_inputText.findCharacterPos(m_cursorIndex).x);
}

void Console::Print(const std::string& l_str)
{
    m_outputBuffer.push_back(l_str);
    
    if(m_outputBuffer.size() > m_maxBufferLines){
        m_outputBuffer.erase(m_outputBuffer.begin());
    }
    
    m_currentViewLineIndex = m_outputBuffer.size();
    
    if(m_state == ConsoleState::Open){
        UpdateTextOutput();
    }
}

void Console::UpdateTextInput()
{
    m_inputText.setString(m_inputBuffer);
}

void Console::UpdateTextOutput()
{
    if(m_outputBuffer.size() == 0){
        m_outputText.setString("");
        return;
    }
    
    //std::string output;
    std::stringstream ss;
    
    sf::Int32 start = m_currentViewLineIndex - m_maxLinesOnScreen;
    if(start < 0){
        start = 0;
    }
    
    for (int i = start; i < m_currentViewLineIndex; i++) {
        ss << m_outputBuffer[i] << "\n";
    }
    
    
    
    m_outputText.setString(ss.str());
    
    m_outputText.setPosition(m_xOffset + m_characterSize,
                             m_backgroundOut.getPosition().y + m_backgroundOut.getSize().y - m_outputText.getLocalBounds().height - m_backgroundIn.getSize().y);
}

void Console::ParseCommand()
{
    if(!m_inputBuffer.empty()){
        std::vector<std::string> commands = Tokenize(m_inputBuffer, ' ');
        
        const auto c = m_commands.find(commands[0]);
        
        if(c != m_commands.end()){
            
            if(commands.size() > 1 && commands[1] == "help"){
                if(c->second.HelpOutput().isEmpty()){
                    Print(commands[0] + ": help not found");
                }else{
                    Print(commands[0] + ": " + c->second.HelpOutput());
                }
            }else{
                
                bool runCommand = true;
                
                if((commands.size() - 1) < c->second.GetMinArguementCount()){
                    Print(commands[0] + ": requires at least " + std::to_string(c->second.GetMinArguementCount()) + " arguements");
                    runCommand = false;
                }
                
                if((commands.size() - 1) > c->second.GetMaxArguementCount()){
                    Print(commands[0] + ": requires at most " + std::to_string(c->second.GetMaxArguementCount()) + " arguements");
                    runCommand = false;
                }
                
                if(runCommand){
                    std::string cmdName = commands[0];
                    commands.erase(commands.begin());
                    std::string result = c->second.Run(commands);
                    if(!result.empty()) { Print(cmdName + ": " + result); }
                }
            }
        }else{
            Print(commands[0] + ": command not found");
        }
        
        m_inputCommands.emplace_back(m_inputBuffer);
        
        if(m_inputCommands.size() > m_commandCacheSize){
            m_inputCommands.erase(m_inputCommands.begin());
        }
        
        m_InputCommandsIndex = m_inputCommands.size();
        
        m_inputBuffer.clear();
        m_cursorIndex = 0;
        m_cursor.SetX(m_inputText.getPosition().x);
        
        UpdateTextInput();
    }
}

void Console::Purge()
{
    if(!m_outputBuffer.empty()){
        m_outputBuffer.clear();
        UpdateTextOutput();
    }
}

//TODO: implement boost as tokenizer?
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


