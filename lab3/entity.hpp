//
//  entity.hpp
//  lab3
//
//  Created by Viktor Yberg on 05/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef entity_hpp
#define entity_hpp

#include <string>
#include <vector>
#include "item.hpp"

using namespace std;

class Environment;

class Entity {
private:
    //vector<const Item&> _items;
    bool enter(Environment*, Environment*, const char);
protected:
    string _type, _name;
    int _hp, _max_hp;
public:
    Entity();
    ~Entity();
    
    struct Position {
        int row, col;
    } _position;
    
    virtual string type() const;
    virtual string name() const;
    
    virtual void action(Entity*, Item*) = 0;
    virtual bool fight(const Entity&) = 0;
    virtual bool talk_to(const Entity&) = 0;
    
    virtual int hp() const;
    virtual int max_hp() const;
    virtual void hp(int);
    virtual bool is_alive() const;
    
    bool go(const char, const vector<vector<Environment*>>&);
    Position position();
    bool pick_up(const Item&);
    bool drop(const Item&);
    vector<const Item*>& items();
};

#endif /* entity_hpp */
