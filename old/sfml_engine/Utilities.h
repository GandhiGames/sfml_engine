//
//  Utilities.h
//  sfml_engine
//
//  Created by Robert Wells on 14/02/2017.
//  Copyright © 2017 Gandhi Games. All rights reserved.
//

#ifndef Utilities_h
#define Utilities_h

inline void ReadQuotedString(std::stringstream& l_stream,
                             std::string& l_string)
{
    l_stream >> l_string;
    if (l_string.at(0) == '"'){
        while (l_string.at(l_string.length() - 1) != '"' || !l_stream.eof()){
            std::string str;
            l_stream >> str;
            l_string.append(" " + str);
        }
    }
    l_string.erase(std::remove(l_string.begin(), l_string.end(), '"'), l_string.end());
}

#endif /* Utilities_h */
