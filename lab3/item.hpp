//
//  item.hpp
//  lab3
//
//  Created by Viktor Yberg on 05/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef item_hpp
#define item_hpp

#include <string>

using namespace std;

class Item {
private:
protected:
    int _weight, _volume, _price;
    string _name;
public:
    Item();
    ~Item();
    
    virtual int weight() const;
    virtual int volume() const;
    virtual int price() const;
    virtual string name() const;
    
    virtual void price(int);
};

#endif /* item_hpp */
