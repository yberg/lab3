//
//  house.cpp
//  lab3
//
//  Created by Viktor Yberg on 06/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "house.hpp"
#include "direction.hpp"

House::House() {
    _entrance = Direction::UP;
    _exit = (_entrance + 2) % 4;
}

House::~House() {
    
}

vector<const char> House::directions() {
    return vector<const char>();
}

struct Description& House::description() {
    Description * d = new Description();
    d->environment = "House";
    d->items = vector<Item*>();
    d->entities = vector<Entity*>();
    return *d;
}

char House::entrance() {
    return _entrance;
}

char House::exit() {
    return _exit;
}