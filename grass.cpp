//
//  grass.cpp
//  lab3
//
//  Created by Viktor Yberg on 08/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "grass.hpp"

Grass::Grass() {
    
}

Grass::~Grass() {
    
}

vector<const char> Grass::directions() {
    return vector<const char>();
}

struct Description& Grass::description() {
    Description * d = new Description();
    d->environment = "Grass";
    d->items = vector<Item*>();
    d->entities = vector<Entity*>();
    return *d;
}