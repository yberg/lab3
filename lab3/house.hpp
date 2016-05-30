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
    char _entrance, _exit, _req_key;
protected:
public:
    House(bool);
    ~House();
    
    virtual vector<const char> directions();
    
    char entrance();
    char exit();
    
    bool req_key() const;
};

#endif /* house_hpp */
