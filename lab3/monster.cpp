//
//  monster.cpp
//  lab3
//
//  Created by Viktor Yberg on 05/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "monster.hpp"

Monster::Monster() {
    
}

Monster::~Monster() {
    
}

string Monster::type() {
    return "Monster";
}

string Monster::name() {
    return "Monsterkalle";
}

void Monster::action() {
    
}

bool Monster::fight(const Entity& entity) {
    return false;
}

bool Monster::talk_to(const Entity& entity) {
    return false;
}