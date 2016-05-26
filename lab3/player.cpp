//
//  player.cpp
//  lab3
//
//  Created by Viktor Yberg on 06/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "player.hpp"
#include <algorithm>
#include <iostream>
#include "potion.hpp"
#include "enemy.hpp"
#include "weapon.hpp"
#include "constants.hpp"

Player::Player(string name) {
    _type = "Player";
    _name = name;
    _damage = Constants::PLAYER_BASE_DAMAGE;
}

Player::~Player() {
    
}

void Player::action(Entity* entity, Item* item) {
    if (Enemy* enemy = dynamic_cast<Enemy*>(entity)) {
        if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {
            enemy->hp(max(0, enemy->hp() - weapon->damage()));
        }
        else {
            enemy->hp(max(0, enemy->hp() - this->damage()));
        }
    }
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

void Player::balance(int balance) {
    _balance = balance;
}

void Player::level(int level) {
    _level = level;
}

int Player::damage() {
    return _damage;
}

bool Player::buy(Item* item) {
    if (item->price() > _balance)
        return false;
    
    _balance -= item->price();
    
    if (dynamic_cast<Potion*>(item)) {
        _hp = min(100, _hp + ((Potion*)item)->healing());
    }
    else {  // Add to inventory
        _inventory.push_back(item);
    }
    
    return true;
}

vector<Item*>& Player::inventory() {
    return _inventory;
}