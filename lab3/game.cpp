//
//  game.cpp
//  lab3
//
//  Created by Viktor Yberg on 06/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

/**
 Xp
 Droppa nyckel när level > x
 Köpa uppgraderingar
 Slåss mot slutboss i låst rum
 */

#include "game.hpp"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <ncurses.h>
#include <cmath>
#include <iostream>
#include "house.hpp"
#include "water.hpp"
#include "grass.hpp"
#include "player.hpp"
#include "monster.hpp"
#include "direction.hpp"
#include "constants.hpp"

#define COLOR_FG        COLOR_WHITE
#define COLOR_BG        COLOR_BLACK
#define COLOR_PLAYER    COLOR_RED
#define COLOR_HOUSE     COLOR_YELLOW
#define COLOR_WATER     COLOR_BLUE
#define COLOR_GRASS     COLOR_GREEN

#define BG_FG           1
#define FG_HOUSE        2
#define FG_WATER        3
#define FG_GRASS        4
#define PLAYER_BG       5
#define PLAYER_HOUSE    6
#define PLAYER_WATER    7
#define PLAYER_GRASS    8
#define FG_GREEN        9
#define FG_RED          10
#define GREEN_BG        11
#define YELLOW_BG       12
#define RED_BG          13
#define BLUE_BG         14

Player player("Viktor");
vector<vector<Environment*>> environment(Constants::WORLD_SIZE);
vector<vector<Entity*>> entities(Constants::WORLD_SIZE);
vector<vector<Item*>> items(Constants::WORLD_SIZE);

bool playing, show_buymenu, show_fight;

Game::Game() {
    srand((unsigned int)time(NULL));
    
    // Create environment
    for (int i = 0; i < Constants::WORLD_SIZE; i++) {
        for(int j = 0; j < Constants::WORLD_SIZE; j++) {
            int r = rand() % 5;
            if (r < 1) {
                environment.at(i).push_back(new House());
                entities.at(i).push_back(new Monster("Wizard", "Kalle", 80, 2));
            }
            else if (r < 2) {
                environment.at(i).push_back(new Water());
                entities.at(i).push_back(NULL);
            }
            else {
                environment.at(i).push_back(new Grass());
                entities.at(i).push_back(NULL);
            }
        }
    }
    
    init_screen();
    intro();
    init_game();
    run();
}

Game::~Game() {
    
}

void Game::init_screen() {
    initscr();
    noecho();
    //raw();  // Disable CTRL-C etc.
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
    init_pair(9, COLOR_FG, COLOR_GREEN);
    init_pair(10, COLOR_FG, COLOR_RED);
    init_pair(11, COLOR_GREEN, COLOR_BG);
    init_pair(12, COLOR_YELLOW, COLOR_BG);
    init_pair(13, COLOR_RED, COLOR_BG);
    init_pair(14, COLOR_BLUE, COLOR_BG);
}

void Game::intro() {
    return; // remove
    putstr("Press p to play", 0, 0);
    int input = getch();
    while (input != 'p') {
        putch(input, 10, 10);
        input = getch();
    }
}

void Game::init_game() {
    player.balance(100);
    player.level(1);
    player.hp(50);
}

void Game::quit() {
    move(25, 0);
    clrtoeol();
    attron(COLOR_PAIR(BG_FG));
    addstr("Exit? (y/n)");
    attroff(COLOR_PAIR(BG_FG));
    while (true) {
        int r = getch();
        if (r == 'y') {
            playing = false;
            break;
        }
        else if (r == 'n') {
            break;
        }
    }
}

void Game::run() {
    draw();
    
    Enemy* enemy = nullptr;
    
    map<int,char> dirs;
    dirs[KEY_UP] = Direction::UP;
    dirs[KEY_DOWN] = Direction::DOWN;
    dirs[KEY_RIGHT] = Direction::RIGHT;
    dirs[KEY_LEFT] = Direction::LEFT;
    
    playing = true;
    while (playing && player.is_alive()) {
        int k = getch();
        if (k == KEY_UP || k == KEY_DOWN || k == KEY_RIGHT || k == KEY_LEFT) {
            player.go(dirs[k], environment);
            if ((enemy = dynamic_cast<Enemy*>(entities.at(player.position().row).at(player.position().col))) != NULL) {
                show_fight = true;
                show_buymenu = false;
            }
            else {
                show_fight = false;
            }
        }
        else if (k == 'b' && !show_fight) {
            show_buymenu = !show_buymenu;
        }
        else if (show_buymenu) {
            for (int i = 0; i < Constants::STORE.size(); ++i) {
                if (k == (char)(i+49)) {
                    player.buy(Constants::STORE.at(i));
                }
            }
        }
        if (k == 'q') {  // Quit
            quit();
        }
        draw();
        if (show_fight) {
            fight(enemy);
        }
    }
    endwin();
}

void Game::fight(Enemy* enemy) {
    Item* item;
    bool attacked = false;
    while (enemy->hp() > 0 && player.hp() > 0) {
        int k = getch();
        attacked = false;
        
        if (k == 'q') {  // Quit
            quit();
            draw();
            break;
        }
        if (player.inventory().size() == 0) {
            if (k == '0') {
                player.action(enemy, NULL);
                attacked = true;
            }
        }
        else {
            for (int i = 0; i < player.inventory().size(); ++i) {
                if (k == (char)(i+49)) {
                    item = player.inventory().at(i);
                    if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {
                        player.action(enemy, weapon);
                        attacked = true;
                    }
                }
            }
        }
        
        if (attacked && enemy->hp() > 0) {
            enemy->action(&player, NULL);
        }
        else if (attacked && enemy->hp() == 0) {
            player.balance(player.balance() + enemy->max_hp()/10);
            player.exp(player.exp() + enemy->max_hp()/20);
        }
        draw();
    }
}

void Game::draw() {
    //clear(); // flickering
    clearscr();
    
    draw_edges();
    draw_environment();
    draw_player();
    draw_info();
    draw_inventory();
    if (show_buymenu) draw_buymenu();
    if (show_fight) draw_fight();
    
    refresh();
}

void Game::draw_edges() {
    // Edges
    if (show_fight)
        attron(RED_BG);
    for (int i = 1; i <= Constants::WORLD_SIZE*2; i++) {
        move(0, i);
        addch(115 | A_ALTCHARSET);
        move(Constants::WORLD_SIZE + 1, i);
        addch(111 | A_ALTCHARSET);
    }
    for (int i = 1; i <= Constants::WORLD_SIZE; i++) {
        move(i, 0);
        addch(ACS_VLINE);
        move(i, Constants::WORLD_SIZE*2 + 1);
        addch(ACS_VLINE);
    }
    if (show_fight)
        attroff(RED_BG);
}

void Game::draw_environment() {
    // Environment
    int row = 0, col = 0;
    for (auto &r : environment) {
        for (auto &e : r) {
            if (e->description().environment == "House") {
                attron(COLOR_PAIR(FG_HOUSE));
                putch('^', row, col);
                attroff(COLOR_PAIR(FG_HOUSE));
            }
            else if (e->description().environment == "Water") {
                attron(COLOR_PAIR(FG_WATER));
                putch('~', row, col);
                attroff(COLOR_PAIR(FG_WATER));
            }
            else if (e->description().environment == "Grass") {
                attron(COLOR_PAIR(FG_GRASS));
                putch(' ', row, col);
                attroff(COLOR_PAIR(FG_GRASS));
            }
            col++;
        }
        row++;
        col = 0;
    }
}

void Game::draw_player() {
    // Player
    Entity::Position pos = player.position();
    auto color = COLOR_PAIR(PLAYER_BG);
    if (environment.at(pos.row).at(pos.col)->description().environment == "House")
        color = COLOR_PAIR(PLAYER_HOUSE);
    else if (environment.at(pos.row).at(pos.col)->description().environment == "Water")
        color = COLOR_PAIR(PLAYER_WATER);
    else if (environment.at(pos.row).at(pos.col)->description().environment == "Grass")
        color = COLOR_PAIR(PLAYER_GRASS);
    attron(color);
    putch('@', pos.row, pos.col);
    attroff(color);
}

void Game::draw_info() {
    // Info

    int i;
    
    // Level
    move(22, 1);
    printw("Level %d", player.level());
    
    // Experience
    move(23, 1);
    attron(COLOR_PAIR(FG_GREEN));
    for (i = 0; i < player.exp()/5; i++) {
        if (i == 0)
            addch('[');
        else if (i == 19)
            addch(']');
        else
            addch(' ');
    }
    attroff(COLOR_PAIR(FG_GREEN));
    attron(COLOR_PAIR(FG_RED));
    for (; i < 20; i++) {
        if (i == 0)
            addch('[');
        else if (i == 19)
            addch(']');
        else
            addch(' ');
    }
    attroff(COLOR_PAIR(FG_RED));
    
    // HP
    putstr("Health", 22, 21);
    move(22, 34);
    printw("%3d/100", player.hp());
    
    // HP bar
    move(23, 21);
    attron(COLOR_PAIR(FG_GREEN));
    for (i = 0; i < player.hp()/5; i++) {
        if (i == 0)
            addch('[');
        else if (i == 19)
            addch(']');
        else
            addch(' ');
    }
    attroff(COLOR_PAIR(FG_GREEN));
    attron(COLOR_PAIR(FG_RED));
    for (; i < 20; i++) {
        if (i == 0)
            addch('[');
        else if (i == 19)
            addch(']');
        else
            addch(' ');
    }
    attroff(COLOR_PAIR(FG_RED));
    
    // Balance
    move(22, 50);
    printw("Balance: ");
    attron(COLOR_PAIR(YELLOW_BG));
    printw("$%d", player.balance());
    attroff(COLOR_PAIR(YELLOW_BG));
}

void Game::draw_inventory() {
    int i = 20;
    long j = player.inventory().size();
    for (auto it = player.inventory().begin(); it != player.inventory().end(); ++it) {
        move(i--, 50);
        if (show_fight)
            printw("%d. ", j--);
        printw((*it)->name().c_str());
        if (Weapon* w = dynamic_cast<Weapon*>(*it)) {
            printw(" (");
            attron(COLOR_PAIR(RED_BG));
            printw("%d", w->damage());
            attroff(COLOR_PAIR(RED_BG));
            printw(", ");
            attron(COLOR_PAIR(BLUE_BG));
            printw("%d", w->block());
            attroff(COLOR_PAIR(BLUE_BG));
            printw(")");
        }
    }
    if (player.inventory().size() == 0) {
        move(i--, 50);
        if (show_fight) {
            printw("0. Kick");
        }
        else {
            attron(COLOR_PAIR(YELLOW_BG));
            printw("Empty");
            attroff(COLOR_PAIR(YELLOW_BG));
        }
    }
    move(i, 50);
    attron(A_UNDERLINE);
    if (!show_buymenu)
        attron(COLOR_PAIR(GREEN_BG));
    printw("    INVENTORY    ");
    attroff(A_UNDERLINE);
    if (!show_buymenu)
        attroff(COLOR_PAIR(GREEN_BG));
}

void Game::draw_buymenu() {
    // Buymenu
    attron(A_UNDERLINE);
    attron(COLOR_PAIR(GREEN_BG));
    putstr("     BUYMENU     ", 1, 50);
    attroff(COLOR_PAIR(GREEN_BG));
    attroff(A_UNDERLINE);
    
    int choice = 1, i = 2;
    for (auto it = Constants::STORE.begin(); it != Constants::STORE.end(); ++it) {
        move(i++, 50);
        printw("%d. $%-3d %s", choice++, (*it)->price(), (*it)->name().c_str());
        if (Weapon* w = dynamic_cast<Weapon*>(*it)) {
            printw(" (");
            attron(COLOR_PAIR(RED_BG));
            printw("%d", w->damage());
            attroff(COLOR_PAIR(RED_BG));
            printw(", ");
            attron(COLOR_PAIR(BLUE_BG));
            printw("%d", w->block());
            attroff(COLOR_PAIR(BLUE_BG));
            printw(")");
        }
        if (Potion* p = dynamic_cast<Potion*>(*it)) {
            printw(" (");
            attron(COLOR_PAIR(GREEN_BG));
            printw("%d", p->healing());
            attroff(COLOR_PAIR(GREEN_BG));
            printw(")");
        }
    }
    putstr("b. Close", ++i, 50);
}

void Game::draw_fight() {
    
    if (Enemy* enemy = dynamic_cast<Enemy*>(entities.at(player.position().row).at(player.position().col))) {
    
        move(1, 50);
        attron(A_UNDERLINE);
        attron(COLOR_PAIR(RED_BG));
        printw("      FIGHT      ");
        attroff(A_UNDERLINE);
        attroff(COLOR_PAIR(RED_BG));
        
        move(2, 50);
        printw(enemy->name().c_str());
        printw(" (");
        printw(enemy->type().c_str());
        printw(")");
        if (enemy->hp() == 0) {
            attron(COLOR_PAIR(RED_BG));
            printw(" (DEAD)");
            attroff(COLOR_PAIR(RED_BG));
        }
        
        // HP
        putstr("Health", 3, 50);
        move(3, 66 - ceil(log10(enemy->max_hp()+1)));
        printw("%3d/%d", enemy->hp(), enemy->max_hp());
        
        // HP bar
        int i;
        move(4, 50);
        attron(COLOR_PAIR(FG_GREEN));
        for (i = 0; i < enemy->hp()/(enemy->max_hp()/20); i++) {
            if (i == 0)
                addch('[');
            else if (i == 19)
                addch(']');
            else
                addch(' ');
        }
        attroff(COLOR_PAIR(FG_GREEN));
        attron(COLOR_PAIR(FG_RED));
        for (; i < 20; i++) {
            if (i == 0)
                addch('[');
            else if (i == 19)
                addch(']');
            else
                addch(' ');
        }
        attroff(COLOR_PAIR(FG_RED));
    }
}

void Game::putch(char c, int row, int col) {
    move(row + 1, col * 2 + 1);
    addch(c);
    move (row + 1, col * 2 + 2);
    addch(c);
}

void Game::putstr(string s, int row, int col) {
    move(row, col);
    printw(s.c_str());
}

void Game::clearscr() {
    // TODO adjust to info pane
    for (int i = 0; i < 22; i++) {
        move(i, 41);
        printw("                                      "); // 38 spaces
    }
    for (int i = 22; i < 26; i++) {
        move(i, 0);
        clrtoeol();
    }
}