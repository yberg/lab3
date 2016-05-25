//
//  inside.hpp
//  lab3
//
//  Created by Viktor Yberg on 06/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef inside_hpp
#define inside_hpp

#include "environment.hpp"

class Inside : public Environment {
private:
protected:
    bool _has_enemy;
public:
    Inside();
    ~Inside();
    
    virtual vector<const char> directions() = 0;
    
    virtual bool has_enemy();
};

#endif /* inside_hpp */
