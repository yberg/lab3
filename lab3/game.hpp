//
//  game.hpp
//  lab3
//
//  Created by Viktor Yberg on 06/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <string>
#include "enemy.hpp"

using namespace std;

class Game {
private:
protected:
public:
    Game();
    ~Game();
    
    void init_screen();
    void intro();
    void init_game();
    void quit();
    void run();
    void fight(Enemy*);
    
    void draw();
    void draw_edges();
    void draw_environment();
    void draw_player();
    void draw_info();
    void draw_inventory();
    void draw_buymenu();
    void draw_fight();
    
    void putch(char, int, int);
    void putstr(string, int, int);
    void clearscr();
};

#endif /* game_hpp */
