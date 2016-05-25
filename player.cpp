//
//  player.cpp
//  lab3
//
//  Created by Viktor Yberg on 06/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "player.hpp"

Player::Player(string n)
: _name(n)
{
    _name = n;
}

Player::~Player() {
    
}

string Player::type() {
    return "Player";
}

string Player::name() {
    return _name;
}

void Player::action() {
    
}

bool Player::fight(const Entity& entity) {
    return false;
}

bool Player::talk_to(const Entity& entity) {
    return false;
}