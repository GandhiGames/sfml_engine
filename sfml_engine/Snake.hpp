//
//  Snake.hpp
//  sfml_engine
//
//  Created by Robert Wells on 24/02/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef Snake_hpp
#define Snake_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>

struct SnakeSegment {
    SnakeSegment (int x, int y) : position(x, y){};
    sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction {
    None, Up, Down, Left, Right
};

class Snake {
public:
    Snake (int l_size);
    ~Snake();
    
    void SetDirection(Direction l_direction);
    const Direction &GetDirection() const;
    int GetSpeed();
    const sf::Vector2i & GetPositon() const;
    int GetLives() const;
    int GetScore() const;
    void IncreaseScore(int l_amount = 10);
    bool HasLost() const;
    
    void Lose();
    void ToggleLost();
    void Grow();
    void Reset();
    
    void Move();
    void Tick();
    
    void Cut(int l_segments);
    
    void Render(sf::RenderWindow &l_window);
    
private:
    void CheckCollision();
    SnakeContainer m_snakeBody;
    int m_size;
    Direction m_direction;
    int m_speed;
    int m_lives;
    int m_score;
    bool m_lost;
    sf::RectangleShape m_bodyRect;
    static const sf::Vector2i ZeroVector;

    
};

#endif /* Snake_hpp */
