//
//  monster.hpp
//  lab3
//
//  Created by Viktor Yberg on 05/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef monster_hpp
#define monster_hpp

#include "enemy.hpp"

class Monster : public Enemy {
private:
protected:
public:
    Monster(string, string);
    ~Monster();

    virtual void action(Entity*, Item*);
    virtual bool fight(const Entity&);
    virtual bool talk_to(const Entity&);
};

#endif /* monster_hpp */
