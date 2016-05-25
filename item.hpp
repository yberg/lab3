//
//  item.hpp
//  lab3
//
//  Created by Viktor Yberg on 05/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef item_hpp
#define item_hpp

class Item {
private:
protected:
public:
    Item();
    ~Item();
    
    virtual int weight() = 0;
    virtual int volume() = 0;
    virtual int price() = 0;
};

#endif /* item_hpp */
