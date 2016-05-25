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
    string _name;
protected:
public:
    Player(string);
    ~Player();
    
    virtual string type();
    virtual string name();
    virtual void action();
    virtual bool fight(const Entity&);
    virtual bool talk_to(const Entity&);
};

#endif /* player_hpp */
