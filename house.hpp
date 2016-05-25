//
//  house.hpp
//  lab3
//
//  Created by Viktor Yberg on 06/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef house_hpp
#define house_hpp

#include "inside.hpp"

class House : public Inside {
private:
    char _entrance, _exit;
protected:
public:
    House();
    ~House();
    
    virtual vector<const char> directions();
    virtual struct Description& description();
    
    char entrance();
    char exit();
};

#endif /* house_hpp */
