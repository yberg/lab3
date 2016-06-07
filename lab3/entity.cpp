//
//  entity.cpp
//  lab3
//
//  Created by Viktor Yberg on 05/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "entity.hpp"
#include <algorithm>
#include "direction.hpp"
#include "constants.hpp"
#include "environment.hpp"
#include "house.hpp"
#include "player.hpp"

using namespace std;

Entity::Entity() {
    _position = { Constants::WORLD_SIZE/2, Constants::WORLD_SIZE/2 };
}

Entity::~Entity() {
    
}

string Entity::type() const {
    return _type;
}

string Entity::name() const {
    return _name;
}

int Entity::hp() const {
    return _hp;
}

int Entity::max_hp() const {
    return _max_hp;
}

void Entity::hp(int hp) {
    _hp = hp;
}

void Entity::max_hp(int max_hp) {
    _max_hp = max_hp;
}

bool Entity::is_alive() const {
    return _hp > 0;
}

/**
 * Moves an entity to given position.
 * @param  direction Direction to move in
 * @param  env       Game environment matrix
 * @param  has_key   Whether the entity has a key
 * @return           Whether the entity can move or not
 */
bool Entity::go(const char direction, const vector<vector<Environment*>>& env, bool has_key) {
    int &row = _position.row;
    int &col = _position.col;

    /* Updates entity position variables if it can move */
    switch (direction) {
        case Direction::UP:
            if (row <= 0) return false;
            if (enter(env.at(row).at(col), env.at(row-1).at(col), direction, has_key)) {
                row -= 1;
                return true;
            }
            break;
        case Direction::DOWN:
            if (row >= Constants::WORLD_SIZE-1) return false;
            if (enter(env.at(row).at(col), env.at(row+1).at(col), direction, has_key)) {
                row += 1;
                return true;
            }
            break;
        case Direction::RIGHT:
            if (col >= Constants::WORLD_SIZE-1) return false;
            if (enter(env.at(row).at(col), env.at(row).at(col+1), direction, has_key)) {
                col += 1;
                return true;
            }
            break;
        case Direction::LEFT:
            if (col <= 0) return false;
            if (enter(env.at(row).at(col), env.at(row).at(col-1), direction, has_key)) {
                col -= 1;
                return true;
            }
            break;
            
        default:
            break;
    }
    return false;
}

/**
 * Checks if given destination is a valid move.
 * @param  src       Source position
 * @param  dest      Destination
 * @param  direction Direction to move in
 * @param  has_key   Whether the entity has a key
 * @return           Whether the player can move or not
 */
bool Entity::enter(Environment * src, Environment * dest, const char direction, bool has_key) {
    /* House to house */
    if (dynamic_cast<House*>(src)) {
        if (House* dest_house = dynamic_cast<House*>(dest)) {
            if (dest_house->req_key()) {
                return has_key;
            }
            else {
                return true;
            }
        }
        else if (((House*)src)->exit() == direction) {
            return true;
        }
    }
    /* Anywhere to house */
    else if (House* dest_house = dynamic_cast<House*>(dest)) {
        if (dest_house->entrance() == direction) {
            if (dest_house->req_key())
                return has_key;
            else
                return true;
        }
    }
    else {
        return true;
    }
    return false;
}

Entity::Position Entity::position() {
    return _position;
}

void Entity::position(int row, int col) {
    _position = {row, col};
}

bool Entity::pick_up(const Item& item) {
    //_items.push_back(item);
    return false;
}

bool Entity::drop(const Item& item) {
    //_items.erase(remove(_items.begin(), _items.end(), item), _items.end());
    return false;
}

vector<const Item*>& Entity::items() {
    return * new vector<const Item*>;
}