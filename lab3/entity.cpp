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

using namespace std;

Entity::Entity() {
    _position = { 0, 0 };
}

Entity::~Entity() {
    
}

bool Entity::go(const char direction, const vector<vector<Environment*>>& env) {
    int &row = _position.row;
    int &col = _position.col;
    switch (direction) {
        case Direction::UP:
            if (row <= 0) return false;
            if (enter(env.at(row).at(col), env.at(row-1).at(col), direction)) {
                row -= 1;
                return true;
            }
            break;
        case Direction::DOWN:
            if (row >= Constants::WORLD_SIZE-1) return false;
            if (enter(env.at(row).at(col), env.at(row+1).at(col), direction)) {
                row += 1;
                return true;
            }
            break;
        case Direction::RIGHT:
            if (col >= Constants::WORLD_SIZE-1) return false;
            if (enter(env.at(row).at(col), env.at(row).at(col+1), direction)) {
                col += 1;
                return true;
            }
            break;
        case Direction::LEFT:
            if (col <= 0) return false;
            if (enter(env.at(row).at(col), env.at(row).at(col-1), direction)) {
                col -= 1;
                return true;
            }
            break;
            
        default:
            break;
    }
    return false;
}

bool Entity::enter(Environment * src, Environment * dest, const char direction) {
    if (src->description().environment == "House") {
        if (dest->description().environment == "House") {
            return true;
        }
        else if (((House*)src)->exit() == direction) {
            return true;
        }
    }
    else if (dest->description().environment == "House") {
        if (((House*)dest)->entrance() == direction) {
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