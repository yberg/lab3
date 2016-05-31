//
//  outside.hpp
//  lab3
//
//  Created by Viktor Yberg on 05/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef outside_hpp
#define outside_hpp

#include "environment.hpp"

class Outside : public Environment {
private:
protected:
public:
    Outside();
    virtual ~Outside();
    
    virtual vector<char> directions() = 0;
};

#endif /* outside_hpp */
