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
_base_damage(Constants::PLAYER_BASE_DAMAGE), _exp(1) {
    _type = "Player";
    _name = name;
    _max_hp = Constants::PLAYER_START_HP;
    
    srand((unsigned int)time(NULL));
}

Player::~Player() {
    
}

void Player::action(Entity* entity, Item* item) {
    if (Enemy* enemy = dynamic_cast<Enemy*>(entity)) {
        int damage;
        if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {
            damage = (rand() % weapon->damage()) + 1 + _base_damage;
        }
        else {
            damage = (rand() % this->base_damage()) + 1;
        }
        enemy->hp(max(0, enemy->hp() - damage));
    }
    if (Potion* potion = dynamic_cast<Potion*>(item)) {
        _hp = min(_max_hp, _hp + potion->healing());
    }
}

bool Player::fight(const Entity& entity) {
    return false;
}

bool Player::talk_to(const Entity& entity) {
    return false;
}

int Player::damage() const {
    int max_dmg = 0;
    for (auto it = _inventory.begin(); it != _inventory.end(); ++it) {
        if (Weapon* w = dynamic_cast<Weapon*>(*it)) {
            if (w->damage() > max_dmg) {
                max_dmg = w->damage();
            }
        }
    }
    return max_dmg;
}

int Player::block() const {
    int max_block = 0;
    for (auto it = _inventory.begin(); it != _inventory.end(); ++it) {
        if (Weapon* w = dynamic_cast<Weapon*>(*it)) {
            if (w->block() > max_block) {
                max_block = w->block();
            }
        }
    }
    return max_block;
}

int Player::balance() const {
    return _balance;
}

int Player::level() const {
    return _level;
}

int Player::base_damage() const {
    return _base_damage * _level;
}

int Player::exp() const {
    return _exp;
}

int Player::max_exp() const {
    return Constants::EXP[_level - 1];
}

void Player::balance(int balance) {
    _balance = balance;
}

void Player::level(int level) {
    _level = level;
}

void Player::exp(int exp) {
    if (exp >= Constants::EXP[_level - 1]) {
        _exp = exp - Constants::EXP[_level - 1];
        _level += 1;
        _max_hp += 10;
        _hp += 10;
    }
    else {
        _exp = exp;
    }
    
    if (_exp == 0) {
        _exp = 1;
    }
}

bool Player::buy(Item* item) {
    if (item->price() > _balance)
        return false;
    
    _balance -= item->price();
    
    if (Potion* potion = dynamic_cast<Potion*>(item)) {
        action(nullptr, potion);
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