//
//  grass.hpp
//  lab3
//
//  Created by Viktor Yberg on 08/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef grass_hpp
#define grass_hpp

#include "outside.hpp"

class Grass : public Outside {
private:
protected:
public:
    Grass();
    ~Grass();
    
    virtual vector<const char> directions();
    virtual struct Description& description();
};

#endif /* grass_hpp */
