//
//  weapon.cpp
//  lab3
//
//  Created by Viktor Yberg on 25/05/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "weapon.hpp"

Weapon::Weapon(string name, int bonus_damage, int block, int price) : _bonus_damage(bonus_damage), _block(block) {
    _name = name;
    _price = price;
}

Weapon::~Weapon() {
    
}

int Weapon::bonus_damage() {
    return _bonus_damage;
}

int Weapon::block() {
    return _block;
}