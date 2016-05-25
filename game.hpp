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

using namespace std;

class Game {
private:
protected:
public:
    Game();
    ~Game();
    
    void run();
    void draw();
    void putch(char, int, int);
    void putstr(string, int, int);
    void clearscr();
};

#endif /* game_hpp */
