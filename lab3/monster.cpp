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
        player->hp(max(0, player->hp() - damage));
    }
}

bool Monster::fight(const Entity& entity) {
    return false;
}

bool Monster::talk_to(const Entity& entity) {
    return false;
}