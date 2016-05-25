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

class Player : public Entity {
private:
    int _balance, _level, _hp;
    vector<Item*> _inventory;
protected:
public:
    Player(string);
    ~Player();

    virtual void action();
    virtual bool fight(const Entity&);
    virtual bool talk_to(const Entity&);
    
    int balance();
    int level();
    int hp();
    
    void balance(int);
    void level(int);
    void hp(int);
    bool buy(Item*);
    vector<Item*>& inventory();
};

#endif /* player_hpp */
