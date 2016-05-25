//
//  player.cpp
//  lab3
//
//  Created by Viktor Yberg on 06/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "player.hpp"
#include "potion.hpp"
#include <algorithm>
#include <iostream>

Player::Player(string n) {
    _type = "Player";
    _name = n;
}

Player::~Player() {
    
}

void Player::action() {
    
}

bool Player::fight(const Entity& entity) {
    return false;
}

bool Player::talk_to(const Entity& entity) {
    return false;
}

int Player::balance() {
    return _balance;
}

int Player::level() {
    return _level;
}

int Player::hp() {
    return _hp;
}

void Player::balance(int b) {
    _balance = b;
}

void Player::level(int l) {
    _level = l;
}

void Player::hp(int h) {
    _hp = h;
}

bool Player::buy(Item* item) {
    if (item->price() > _balance)
        return false;
    
    _balance -= item->price();
    
    if (dynamic_cast<Potion*>(item)) {
        _hp = min(100, _hp + ((Potion*)item)->healing());
    }
    else {
        // Add to inventory
        _inventory.push_back(item);
    }
    
    return true;
}

vector<Item*>& Player::inventory() {
    return _inventory;
}