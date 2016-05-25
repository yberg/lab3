//
//  environment.hpp
//  lab3
//
//  Created by Viktor Yberg on 05/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef environment_hpp
#define environment_hpp

#include <vector>
#include "entity.hpp"
#include "item.hpp"

using namespace std;

class Environment {
private:
protected:
public:
    Environment();
    ~Environment();
    
    virtual vector<const char> directions() = 0;
    virtual struct Description& description() = 0;

    Item& neighbor(const char);
    bool enter(const Entity&);
    bool leave(const Entity&);
    bool pick_up(const Item&);  
    bool drop(const Item&);
};

ostream& operator<<(ostream&, const Environment&);

struct Description {
    string environment;
    vector<Item*> items;
    vector<Entity*> entities;
};

#endif /* environment_hpp */
