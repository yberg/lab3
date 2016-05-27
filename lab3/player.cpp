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

Player::Player(string name) :
_damage(Constants::PLAYER_BASE_DAMAGE), _exp(0) {
    _type = "Player";
    _name = name;
    
    srand((unsigned int)time(NULL));
}

Player::~Player() {
    
}

void Player::action(Entity* entity, Item* item) {
    if (Enemy* enemy = dynamic_cast<Enemy*>(entity)) {
        int damage;
        if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {
            damage = (rand() % weapon->damage());
        }
        else {
            damage = (rand() % this->damage());
        }
        enemy->hp(max(0, enemy->hp() - damage));
    }
}

bool Player::fight(const Entity& entity) {
    return false;
}

bool Player::talk_to(const Entity& entity) {
    return false;
}

int Player::balance() const {
    return _balance;
}

int Player::level() const {
    return _level;
}

int Player::damage() const {
    return _damage;
}

int Player::exp() const {
    return _exp;
}

void Player::balance(int balance) {
    _balance = balance;
}

void Player::level(int level) {
    _level = level;
}

void Player::exp(int exp) {
    _exp = exp;
}

bool Player::buy(Item* item) {
    if (item->price() > _balance)
        return false;
    
    _balance -= item->price();
    
    if (Potion* potion = dynamic_cast<Potion*>(item)) {
        _hp = min(100, _hp + potion->healing());
    }
    else if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {  // Add to inventory
        const string name = weapon->name();
        auto it = find_if(this->inventory().begin(), this->inventory().end(), [&name](const Item* i) {return i->name() == name;});
        if (it != this->inventory().end()) {
            Weapon* w = (Weapon*) *it;
            w->damage(w->damage() * Constants::WEAPON_DAMAGE_MULTIPLIER);
            w->block(w->block() * Constants::WEAPON_BLOCK_MULTIPLIER);
        }
        else {
            _inventory.push_back(item);
        }
        item->price(item->price() * Constants::STORE_PRICE_MULTIPLIER);  // Update price in store
    }
    
    return true;
}

vector<Item*>& Player::inventory() {
    return _inventory;
}