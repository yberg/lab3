//
//  grass.cpp
//  lab3
//
//  Created by Viktor Yberg on 08/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "grass.hpp"

Grass::Grass() {
    _environment = "Grass";
    _items = vector<Item*>();
    _entities = vector<Entity*>();
}

Grass::~Grass() {
    
}

vector<const char> Grass::directions() {
    return vector<const char>();
}