//
//  player.hpp
//  lab3
//
//  Created by Viktor Yberg on 06/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include "entity.hpp"
#include "entity.hpp"
#include "item.hpp"

class Player : public Entity {
private:
    int _balance, _level, _base_damage, _exp;
    vector<Item*> _inventory;
    bool _has_key;
protected:
public:
    Player(string);
    ~Player();

    virtual void action(Entity*, Item*);
    virtual bool fight(const Entity&);
    virtual bool talk_to(const Entity&);
    virtual int damage() const;
    
    int block() const;
    
    int balance() const;
    int level() const;
    int base_damage() const;
    int exp() const;
    int max_exp() const;
    bool has_key() const;
    
    void balance(int);
    void level(int);
    void exp(int);
    void has_key(bool);
    
    bool buy(Item*);
    vector<Item*>& inventory();
};

#endif /* player_hpp */
