//
//  inside.cpp
//  lab3
//
//  Created by Viktor Yberg on 06/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "inside.hpp"

Inside::Inside() : _has_enemy(false) {
    
}

Inside::~Inside() {
    
}

bool Inside::has_enemy() {
    return _has_enemy;
}

void Inside::has_enemy(bool has_enemy) {
    _has_enemy = has_enemy;
}