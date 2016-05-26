//
//  weapon.cpp
//  lab3
//
//  Created by Viktor Yberg on 25/05/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "weapon.hpp"

Weapon::Weapon(string name, int damage, int block, int price) : _damage(damage), _block(block) {
    _name = name;
    _price = price;
}

Weapon::~Weapon() {
    
}

int Weapon::damage() {
    return _damage;
}

int Weapon::block() {
    return _block;
}