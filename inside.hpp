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
public:
    Inside();
    ~Inside();
    
    virtual vector<const char> directions() = 0;
    virtual struct Description& description() = 0;
};

#endif /* inside_hpp */
