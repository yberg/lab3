//
//  monster.cpp
//  lab3
//
//  Created by Viktor Yberg on 05/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "monster.hpp"
#include "player.hpp"
#include "weapon.hpp"

Monster::Monster(string type, string name, int hp, int damage) {
    _type = type;
    _name = name;
    _hp = hp;
    _max_hp = hp;
    _damage = damage;
}

Monster::~Monster() {
    
}

void Monster::action(Entity* entity, Item* item) {
    if (Player* player = dynamic_cast<Player*>(entity)) {
        int damage = this->damage();
        for (auto it = player->inventory().begin(); it != player->inventory().end(); ++it) {
            if (Weapon* weapon = dynamic_cast<Weapon*>(*it)) {
                damage -= weapon->block();
            }
        }
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