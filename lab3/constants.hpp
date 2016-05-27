//
//  constants.hpp
//  lab3
//
//  Created by Viktor Yberg on 07/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef constants_h
#define constants_h

#include <vector>
#include "item.hpp"
#include "weapon.hpp"
#include "potion.hpp"

namespace Constants {
    
    static const int WORLD_SIZE = 20;
    
    static const int LEVEL_EXP = 20;
    
    static const double PLAYER_BASE_DAMAGE = 2;
    static const double WEAPON_DAMAGE_MULTIPLIER = 1.5;
    static const double WEAPON_BLOCK_MULTIPLIER = 1.5;
    static const double STORE_PRICE_MULTIPLIER = 2;
    
    static std::vector<Item*> STORE = {
        new Weapon("Sword", 9, 0, 7),
        new Weapon("Shield", 0, 5, 5),
        new Potion("Health potion", 10, 2)
    };

};

#endif /* constants_h */
