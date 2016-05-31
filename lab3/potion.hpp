//
//  potion.hpp
//  lab3
//
//  Created by Viktor Yberg on 25/05/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef potion_hpp
#define potion_hpp

#include "item.hpp"

class Potion : public Item {
private:
    int _healing;
protected:
public:
    Potion(string, int, int);
    virtual ~Potion();
    
    int healing();
};

#endif /* potion_hpp */
