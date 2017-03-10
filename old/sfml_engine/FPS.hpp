//
//  FPS.hpp
//  sfml_engine
//
//  Created by Robert Wells on 12/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef FPS_hpp
#define FPS_hpp

#include <SFML/System.hpp>

class FPS{
public:
    FPS() : mFrame(0), mFps(0) {}
    
    /// @brief Update the frame count.
    ///
    void Update()
    {
        if(mClock.getElapsedTime().asSeconds() >= 1.f)
        {
            mFps = mFrame;
            mFrame = 0;
            mClock.restart();
        }
        
        ++mFrame;
    }
    
    /// @brief Get the current FPS count.
    /// @return FPS count.
    const unsigned int getFPS() const { return mFps; }
    
private:
    unsigned int mFrame;
    unsigned int mFps;
    sf::Clock mClock;
};




#endif /* FPS_hpp */
