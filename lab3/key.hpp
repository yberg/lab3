//
//  key.hpp
//  lab3
//
//  Created by Viktor Yberg on 29/05/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef key_hpp
#define key_hpp

#include "item.hpp"

class Key : public Item {
private:
protected:
public:
    Key(string);
    ~Key();
    
    void use();
};

#endif /* key_hpp */
