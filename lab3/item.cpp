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

int Item::weight() const{
    return _weight;
}

int Item::volume() const {
    return _volume;
}

int Item::price() const {
    return _price;
}

string Item::name() const {
    return _name;
}

void Item::price(int price) {
    _price = price;
}
