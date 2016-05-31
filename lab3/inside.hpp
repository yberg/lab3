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
    bool _has_enemy = false;
public:
    Inside();
    virtual ~Inside();
    
    virtual vector<char> directions() = 0;
    
    virtual bool has_enemy();
    
    virtual void has_enemy(bool);
};

#endif /* inside_hpp */
