//
//  container.hpp
//  lab3
//
//  Created by Viktor Yberg on 05/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef container_hpp
#define container_hpp

#include "item.hpp"

class Container : public Item {
private:
protected:
public:
    Container();
    
    virtual int weight();
    virtual int volume();
    virtual int price();
    
    int hold_weight();
    int hold_volume();
    bool add(Item&);
    bool remove(Item&);
};

#endif /* container_hpp */
