//
//  weapon.hpp
//  lab3
//
//  Created by Viktor Yberg on 25/05/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef weapon_hpp
#define weapon_hpp

#include "item.hpp"

class Weapon : public Item {
private:
    int _damage, _block;
protected:
public:
    Weapon(string, int, int, int);
    virtual ~Weapon();
    
    int damage() const;
    int block() const;
    
    void damage(int);
    void block(int);
};

#endif /* weapon_hpp */
