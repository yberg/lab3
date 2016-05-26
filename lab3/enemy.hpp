//
//  enemy.hpp
//  lab3
//
//  Created by Viktor Yberg on 05/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef enemy_hpp
#define enemy_hpp

#include "entity.hpp"

class Enemy : public Entity {
private:
protected:
    int _damage;
public:
    Enemy();
    ~Enemy();
    
    virtual void action(Entity*, Item*) = 0;
    virtual bool fight(const Entity&) = 0;
    virtual bool talk_to(const Entity&) = 0;
    
    virtual int damage();
    
};

#endif /* enemy_hpp */
