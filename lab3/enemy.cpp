//
//  enemy.cpp
//  lab3
//
//  Created by Viktor Yberg on 05/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "enemy.hpp"

Enemy::Enemy() {
    
}

Enemy::~Enemy() {
    
}

int Enemy::damage() const {
    return _damage;
}

void Enemy::damage(int damage) {
    _damage = damage;
}
