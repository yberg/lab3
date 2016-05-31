//
//  house.cpp
//  lab3
//
//  Created by Viktor Yberg on 06/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "house.hpp"
#include "direction.hpp"

House::House(bool req_key) : _entrance(Direction::UP), _exit((_entrance + 2) % 4), _req_key(req_key) {
    _entrance = Direction::UP;
    _exit = (_entrance + 2) % 4;
    _has_enemy = true;
    
    if (req_key)
        _environment = "Superhouse";
    else
        _environment = "House";
    
    _items = vector<Item*>();
    _entities = vector<Entity*>();
}

House::~House() {
    
}

vector<char> House::directions() {
    return vector<char>();
}

char House::entrance() {
    return _entrance;
}

char House::exit() {
    return _exit;
}

bool House::req_key() const {
    return _req_key;
}