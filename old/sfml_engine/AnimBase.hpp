//
//  AnimBase.hpp
//  sfml_engine
//
//  Created by Robert Wells on 06/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef AnimBase_hpp
#define AnimBase_hpp

#include <string>
#include <SFML/Graphics.hpp>
#include "Direction.h"

class SpriteSheet;

using Frame = sf::IntRect;

class AnimBase {
    friend class SpriteSheet;
public:
    AnimBase();
    virtual ~AnimBase();
    
    void SetSpriteSheet(SpriteSheet* l_sheet);
    void SetFrame(int l_frame);
    void SetFrames(const std::vector<Frame>& l_frames);
    void SetActionStart(int l_frame);
    void SetActionEnd(int l_frame);
    void SetFrameTime(float l_time);
    void SetLooping(bool l_loop);
    void SetName(const std::string& l_name);
    
    SpriteSheet* GetSpriteSheet();

    int GetActionStart();
    int GetActionEnd();
    float GetFrameTime();
    float GetElapsedTime();
    bool IsLooping();
    bool IsPlaying();
    bool IsInAction();
    const std::string& GetName();
    
    void Play();
    void Pause();
    void Stop();
    void Reset();
    void ForceUpdate();
    
    void SetAnimationDefaultDirection(const Direction& l_dir);

    virtual void Update(const float& l_dT);
    
    /*
    friend std::stringstream& operator >>(std::stringstream &l_stream, AnimBase &a)
    {
        a.ReadIn(l_stream);
        return l_stream;
    }
     */
    
protected:
    void FrameStep();
    void CropSprite();
    int GetCurrentFrame();
   // virtual void ReadIn(std::stringstream& l_stream) = 0;
    
    sf::Uint8 m_frameCurrent;
    std::vector<Frame> m_frames;
    std::vector<Frame> m_reverseFrames;
    int m_frameActionStart;
    int m_frameActionEnd;
    float m_frameTime; // amount of time each frame takes to finish.
    float m_elapsedTime;
    bool m_loop;
    bool m_playing;
    Direction m_defaultDir;
    
    std::string m_name;
    
    SpriteSheet* m_spriteSheet;
};

#endif /* AnimBase_hpp */
