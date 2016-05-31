//
//  water.cpp
//  lab3
//
//  Created by Viktor Yberg on 08/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "water.hpp"

Water::Water() {
    _environment = "Water";
    _items = vector<Item*>();
    _entities = vector<Entity*>();
}

Water::~Water() {
    
}

vector<const char> Water::directions() {
    return vector<const char>();
}