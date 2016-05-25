//
//  potion.cpp
//  lab3
//
//  Created by Viktor Yberg on 25/05/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "potion.hpp"

Potion::Potion(string name, int healing, int price) : _healing(healing)
{
    _name = name;
    _price = price;
}

Potion::~Potion() {
    
}

int Potion::healing() {
    return _healing;
}
