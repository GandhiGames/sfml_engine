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
#include <assert.h>
#include "Window.hpp"
#include "ConsoleCursor.hpp"
#include "ConsoleScrollbar.hpp"
#include "ConsoleCommand.hpp"
#include "FontManager.hpp"


typedef std::function<std::string(std::vector<std::string>&)> Command;

class Console {
public:
    Console(sf::RenderWindow* wind, FontManager& l_fontManager);
    ~Console();
    
    void Add(const std::string& l_name,
             const std::function<std::string(std::vector<std::string>&)>& l_func,
             const sf::Uint8& l_minArguements,
             const sf::Uint8& l_maxArguements,
             const sf::String& l_help);
    void Remove(const std::string& l_name);
    
    void HandleTextInput(EventDetails* l_details);
    void Backspace(EventDetails* l_details);
    void ValidateInput(EventDetails* l_details);
    
    void CycleInputUp(EventDetails* l_details);
    void CycleInputDown(EventDetails* l_details);
    
    void ScrollOutputUp(EventDetails* l_details);
    void ScrollOutputDown(EventDetails* l_details);
    
    void MoveCursorLeft(EventDetails* l_details);
    void MoveCursorRight(EventDetails* l_details);
    
    void Draw(sf::RenderWindow* l_wind);
    
    void Open(const float& l_screenSize, const float& l_moveInPixelsPerSec);
    
    void Close(const float& l_movePixelsPerSec);
    
    void Update(const float& l_dt);
    
    bool IsOpen();
 
private:
    enum class ConsoleState {None = 0, Open, Opening, Closing, Closed};
    
    void Build(const float& l_screenSize);
    void MoveConsoleVertical(const float& l_amount);
    void ResetConsolePosition(const ConsoleState& l_desiredState);
    void Purge();
    void UpdateTextInput();
    void UpdateTextOutput();
    void ParseCommand();
    void Print(const std::string& l_str);
    std::vector<std::string> Tokenize(const std::string& l_input, char l_delim);
    void UpdateTextFromCurrentCommand();
    void DoMovement(const float& l_moveAmount, const ConsoleState& l_goToSate);
    
   
    FontManager& m_fontManager;
    ConsoleState m_state;
    ConsoleCursor m_cursor;
    ConsoleScrollbar m_scrollbar;
    float m_percentScreen;
    float m_movePixelsPerSec;
    float m_accumulatedMove;
    float m_moveOffset;
    sf::Uint16 m_xOffset;
    sf::Uint16 m_maxBufferLength;
    sf::Uint16 m_maxBufferLines;
    sf::Uint16 m_maxLinesOnScreen;
    sf::Uint16 m_currentViewLineIndex;
    sf::Vector2u m_screenSize;
    sf::Uint8 m_cursorIndex;
    sf::Uint8 m_characterSize;
    sf::Uint8 m_commandCacheSize;
    sf::Int8 m_InputCommandsIndex;
    sf::Text m_inputText;
    sf::Text m_outputText;
    sf::Text m_inputPreText;
    std::map<std::string, ConsoleCommand> m_commands;
    std::string m_inputBuffer;
    std::vector<std::string> m_outputBuffer;
    const sf::Font* m_textFont;
    sf::RectangleShape m_backgroundOut;
    sf::RectangleShape m_backgroundIn;
    std::vector<std::string> m_inputCommands;
    
};

#endif /* Console_hpp */
