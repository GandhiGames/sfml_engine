//
//  AnimDirectional.hpp
//  sfml_engine
//
//  Created by Robert Wells on 07/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef AnimDirectional_hpp
#define AnimDirectional_hpp

#include "AnimBase.hpp"

class AnimDirectional : public AnimBase {
protected:
    void FrameStep();
    void CropSprite();
    void ReadIn(std::stringstream &l_stream);
};

#endif /* AnimDirectional_hpp */
