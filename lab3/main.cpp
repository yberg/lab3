//
//  main.cpp
//  lab3
//
//  Created by Viktor Yberg on 05/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include <iostream>
#include "game.hpp"

#include "monster.hpp"
#include "house.hpp"
#include "player.hpp"
#include "constants.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    //Monster monster("Monsterkalle", 50, 10);
    //cout << monster.name() << ": hp: " << monster.hp() << ", damage: " << monster.damage() << endl;
    
    House house;
    cout << house.description().environment << endl;
    
    Player player("Viktor");
    cout << player.name() << endl;
    
    cout << endl << "Price before: " << Constants::STORE.at(0)->price() << endl;
    Constants::STORE.at(0)->price(Constants::STORE.at(0)->price() * 2);
    cout << "Price after: " << Constants::STORE.at(0)->price() << endl;
    
    Game game;
    
    return 0;
}
