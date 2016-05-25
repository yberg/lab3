//
//  game.cpp
//  lab3
//
//  Created by Viktor Yberg on 06/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

#include "game.hpp"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <ncurses.h>
#include "house.hpp"
#include "water.hpp"
#include "grass.hpp"
#include "player.hpp"
#include "constants.hpp"
#include "direction.hpp"

#define COLOR_FG COLOR_WHITE
#define COLOR_BG COLOR_BLACK
#define COLOR_PLAYER COLOR_RED
#define COLOR_HOUSE COLOR_YELLOW
#define COLOR_WATER COLOR_BLUE
#define COLOR_GRASS COLOR_GREEN

Player player("Viktor");
vector<vector<Environment*>> environment(Constants::WORLD_SIZE);
vector<vector<Entity*>> entities(Constants::WORLD_SIZE);
vector<vector<Item*>> items(Constants::WORLD_SIZE);

Game::Game() {
    srand((unsigned int)time(NULL));
    
    // Create environment
    for (int i = 0; i < Constants::WORLD_SIZE; i++) {
        for(int j = 0; j < Constants::WORLD_SIZE; j++) {
            int r = rand() % 5;
            if (r < 1)
                environment.at(i).push_back(new House());
            else if (r < 3)
                environment.at(i).push_back(new Water());
            else
                environment.at(i).push_back(new Grass());
        }
    }
    
    run();
}

Game::~Game() {
    
}

void Game::run() {
    initscr();
    noecho();
    raw();
    start_color();
    keypad(stdscr, true);
    curs_set(0);
    init_pair(1, COLOR_BG, COLOR_FG);
    init_pair(2, COLOR_FG, COLOR_HOUSE);
    init_pair(3, COLOR_FG, COLOR_WATER);
    init_pair(4, COLOR_FG, COLOR_GRASS);
    init_pair(5, COLOR_PLAYER, COLOR_BG);
    init_pair(6, COLOR_PLAYER, COLOR_HOUSE);
    init_pair(7, COLOR_PLAYER, COLOR_WATER);
    init_pair(8, COLOR_PLAYER, COLOR_GRASS);
    draw();
    map<int,char> dirs;
    dirs[KEY_UP] = Direction::UP;
    dirs[KEY_DOWN] = Direction::DOWN;
    dirs[KEY_RIGHT] = Direction::RIGHT;
    dirs[KEY_LEFT] = Direction::LEFT;
    bool playing = true;
    while (playing) {
        int k = getch();
        if (k == KEY_UP || k == KEY_DOWN || k == KEY_RIGHT || k == KEY_LEFT) {
            player.go(dirs[k], environment);
        }
        else if (k == 'q') {
            move(23, 0);
            clrtoeol();
            attron(COLOR_PAIR(1));
            addstr("Exit? (y/n)");
            attroff(COLOR_PAIR(1));
            while (true) {
                int r = getch();
                if (r == (int)'y') {
                    playing = false;
                    break;
                }
                else if (r == (int)'n') {
                    break;
                }
            }
        }
        draw();
    }
    endwin();
}

void Game::draw() {
    //clear(); // flickering
    clearscr();
    // Edges
    for (int i = 1; i <= Constants::WORLD_SIZE*2; i++) {
        move(0, i);
        addch('=');
        move(Constants::WORLD_SIZE + 1, i);
        addch('=');
    }
    for (int i = 1; i <= Constants::WORLD_SIZE; i++) {
        move(i, 0);
        addch('|');
        move(i, Constants::WORLD_SIZE*2 + 1);
        addch('|');
    }
    
    // Environment
    int row = 0, col = 0;
    for (auto &r : environment) {
        for (auto &e : r) {
            if (e->description().environment == "House") {
                attron(COLOR_PAIR(2));
                putch('^', row, col);
                attroff(COLOR_PAIR(2));
            }
            else if (e->description().environment == "Water") {
                attron(COLOR_PAIR(3));
                putch('~', row, col);
                attroff(COLOR_PAIR(3));
            }
            else if (e->description().environment == "Grass") {
                attron(COLOR_PAIR(4));
                putch(' ', row, col);
                attroff(COLOR_PAIR(4));
            }
            col++;
        }
        row++;
        col = 0;
    }
    
    // Player
    Entity::Position pos = player.position();
    auto color = COLOR_PAIR(5);
    if (environment.at(pos.row).at(pos.col)->description().environment == "House")
        color = COLOR_PAIR(6);
    else if (environment.at(pos.row).at(pos.col)->description().environment == "Water")
        color = COLOR_PAIR(7);
    else if (environment.at(pos.row).at(pos.col)->description().environment == "Grass")
        color = COLOR_PAIR(8);
    attron(color);
    putch('@', pos.row, pos.col);
    attroff(color);
    
    // Info
    move(5, 50);
    printw("row: %d", pos.row);
    move(6, 50);
    printw("col: %d", pos.col);
    refresh();
}

void Game::putch(char c, int row, int col) {
    move(row + 1, col * 2 + 1);
    addch(c);
    move (row + 1, col * 2 + 2);
    addch(c);
}

void Game::putstr(string s, int row, int col) {
    move(row + 1, col * 2 + 1);
    addstr(s.c_str());
}

void Game::clearscr() {
    // TODO adjust to info pane
    for (int i = 0; i < 24; i++) {
        move(i, 43);
        addstr("                                      "); // 38 spaces
    }
}