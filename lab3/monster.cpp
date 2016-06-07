//
//  monster.cpp
//  lab3
//
//  Created by Viktor Yberg on 05/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "monster.hpp"
#include <iostream>
#include "player.hpp"
#include "weapon.hpp"
#include "constants.hpp"

Monster::Monster(string type, string name) {
    _type = type;
    _name = name;
    _hp = 1;
    _max_hp = 1;
    _damage = Constants::ENEMY_BASE_DAMAGE;
    left = true;
}

Monster::~Monster() {
    
}

/**
 * Deals damage to another entity. Damage is randomized from 1 to the monster's max damage.
 * @param entity The entity to attack
 * @param item   Item to attack with
 */
void Monster::action(Entity* entity, Item* item) {
    if (Player* player = dynamic_cast<Player*>(entity)) {
        int damage = (rand() % (int)(this->damage() * Constants::DAMAGE_PER_LEVEL_MULTIPLIER)) + 1;
        damage -= player->block();
        damage = max(0, damage);
        
        if (this->type() == "Guardian") {
            damage = 1000;
        }
        
        player->hp(max(0, player->hp() - damage));
    }
    else if (entity == nullptr && item == nullptr) {
        if (_position.col == _col) {
            if (left)
                _position.col--;
            else
                _position.col++;
        }
        else if (_position.col == _col - 1) {
            left = false;
            _position.col++;
        }
        else {
            left = true;
            _position.col--;
        }
    }
}

bool Monster::fight(const Entity& entity) {
    return false;
}

bool Monster::talk_to(const Entity& entity) {
    return false;
}

void Monster::pos(int row, int col) {
    _row = row;
    _col = col;
}