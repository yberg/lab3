//
//  item.cpp
//  lab3
//
//  Created by Viktor Yberg on 05/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "item.hpp"

using namespace std;

Item::Item() {
    
}

Item::~Item() {
    
}

int Item::weight() {
    return _weight;
}

int Item::volume() {
    return _volume;
}

int Item::price() {
    return _price;
}

string Item::name() {
    return _name;
}
