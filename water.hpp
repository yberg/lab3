//
//  water.hpp
//  lab3
//
//  Created by Viktor Yberg on 08/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef water_hpp
#define water_hpp

#include "outside.hpp"

class Water : public Outside {
private:
protected:
public:
    Water();
    ~Water();
    
    virtual vector<const char> directions();
    virtual struct Description& description();
};

#endif /* water_hpp */
