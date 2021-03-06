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
#include "monster.hpp"
#include "entity.hpp"

namespace Constants {
    
    static const int WORLD_SIZE = 20;

    static const int PLAYER_START_LEVEL = 1;
    static const int MAX_LEVEL = 2;
    static const int PLAYER_START_BALANCE = 100;
    static const int PLAYER_START_HP = 100;
    
    static const int EXP[] = {20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70};
    static const int ENEMY_HP[] = {100, 110, 120, 130, 140, 150, 160, 170, 180, 190};
    static const int ENEMY_BASE_DAMAGE = 2;

    static const double PLAYER_BASE_DAMAGE = 2;
    static const double WEAPON_DAMAGE_MULTIPLIER = 1.5;
    static const double WEAPON_BLOCK_MULTIPLIER = 1.5;
    static const double STORE_PRICE_MULTIPLIER = 1.7;
    static const double DAMAGE_PER_LEVEL_MULTIPLIER = 1.2;
    
    static std::vector<std::pair<std::string, std::string>> MONSTERS = {
        std::make_pair("Wizard", "Kalle"),
        std::make_pair("Lion", "Simba"),
        std::make_pair("Demon", "Abalam"),
        std::make_pair("Villager", "Joe"),
        std::make_pair("Knight", "Lancelot")
    };
    
    static struct Entity::Position superhouse_pos;
}

#endif /* constants_h */
