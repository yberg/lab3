//
//  environment.cpp
//  lab3
//
//  Created by Viktor Yberg on 05/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "environment.hpp"
#include <iostream>
#include "direction.hpp"
#include "container.hpp"

using namespace std;

Environment::Environment() {
    
}

Environment::~Environment() {
    
}

/*Item& Environment::neighbor(const char direction) {
    Container * c = new Container();
    return *c;
}*/

/*bool Environment::enter(const Entity& entity) {
    return false;
}*/

/*bool Environment::leave(const Entity& entity) {
    return false;
}*/

bool Environment::pick_up(const Item& item) {
    return false;
}

bool Environment::drop(const Item& item) {
    return false;
}

struct Description& Environment::description() {
    Description * d = new Description();
    d->environment = _environment;
    d->items = _items;
    d->entities = _entities;
    return *d;
}

ostream& operator<<(ostream& os, const Environment& env) {
    os << "hej";
    return os;
}