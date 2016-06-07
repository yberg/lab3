//
//  game.cpp
//  lab3
//
//  Created by Viktor Yberg on 06/01/16.
//  Copyright © 2016 Viktor Yberg. All rights reserved.
//

/**
 Köpa potions under fight
 Rött hus med boss
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
#include <algorithm>
#include "house.hpp"
#include "water.hpp"
#include "grass.hpp"
#include "player.hpp"
#include "monster.hpp"
#include "direction.hpp"
#include "key.hpp"
#include "constants.hpp"

#define COLOR_FG            COLOR_WHITE
#define COLOR_BG            COLOR_BLACK
#define COLOR_PLAYER        COLOR_BLACK
#define COLOR_HOUSE         COLOR_YELLOW
#define COLOR_WATER         COLOR_BLUE
#define COLOR_GRASS         COLOR_GREEN
#define COLOR_SUPERHOUSE    COLOR_RED
#define COLOR_GUARDIAN      COLOR_RED

#define BG_FG               1
#define FG_HOUSE            2
#define FG_WATER            3
#define FG_GRASS            4
#define PLAYER_BG           5
#define PLAYER_HOUSE        6
#define PLAYER_WATER        7
#define PLAYER_GRASS        8
#define FG_GREEN            9
#define FG_RED              10
#define GREEN_BG            11
#define YELLOW_BG           12
#define RED_BG              13
#define BLUE_BG             14
#define FG_CYAN             15
#define CYAN_BG             16
#define FG_SUPERHOUSE       17
#define PLAYER_SUPERHOUSE   18
#define GUARDIAN_GRASS      19
#define GUARDIAN_WATER      20
#define GUARDIAN_BG         21

Player player("Viktor");
Monster * guardian = new Monster("Guardian", "Prince John");

vector<vector<Environment*>> environment(Constants::WORLD_SIZE);
vector<vector<Entity*>> entities(Constants::WORLD_SIZE);
vector<vector<Item*>> items(Constants::WORLD_SIZE);

vector<Item*> store;

bool playing, pause_before_exit, show_buymenu, show_fight, left, guardian_move;
string status_first, status_second;

/**
 * Randomly generates environment blocks and puts them on the board.
 */
Game::Game() {
    srand((unsigned int)time(NULL));
    
    bool superhouse = false;
    
    // Create environment
    for (int i = 0; i < Constants::WORLD_SIZE; i++) {
        for(int j = 0; j < Constants::WORLD_SIZE; j++) {
            int r = rand() % 5;
            if (r < 1 && j != Constants::WORLD_SIZE - 1) {
                if (!superhouse && rand() % 20 == 0) {
                    environment.at(i).push_back(new House(true));
                    entities.at(i).push_back(new Monster("Final boss", "Dr. Dark"));
                    superhouse = true;
                    Constants::superhouse_pos = {i, j};
                    status_first = to_string(i) + ", " + to_string(j);
                    status_second = to_string(Constants::superhouse_pos.row) + ", " + to_string(Constants::superhouse_pos.col);
                }
                else {
                    if (i != Constants::superhouse_pos.row + 1 && (j < Constants::superhouse_pos.col - 1 || j > Constants::superhouse_pos.col + 1)) {
                        environment.at(i).push_back(new House(false));
                        int r1 = rand() % 5;
                        entities.at(i).push_back(new Monster(Constants::MONSTERS.at(r1).first, Constants::MONSTERS.at(r1).second));
                    }
                    else {
                        environment.at(i).push_back(new Grass());
                        entities.at(i).push_back(NULL);
                    }
                }
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
    entities.at(Constants::superhouse_pos.row + 1).at(Constants::superhouse_pos.col) = guardian;
    guardian->pos(Constants::superhouse_pos.row + 1, Constants::superhouse_pos.col);
    guardian->position(Constants::superhouse_pos.row + 1, Constants::superhouse_pos.col);
    
    init_screen();
    intro();
    init_game();
    run();
}

Game::~Game() {
    for (auto it = environment.begin(); it != environment.end(); ++it) {
        for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
            delete (*it2);
        }
    }
    environment.clear();
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
            delete (*it2);
        }
    }
    entities.clear();
    for (auto it = items.begin(); it != items.end(); ++it) {
        for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
            delete (*it2);
        }
    }
    items.clear();
    for (auto it = player.inventory().begin(); it != player.inventory().end(); ++it) {
        if (dynamic_cast<Key*>(*it))
            delete (*it);
    }
    player.inventory().clear();
    for (auto it = store.begin(); it != store.end(); ++it) {
        delete (*it);
    }
    store.clear();
    
    delete guardian;
}

/**
 * Initialises the ncurses window.
 */
void Game::init_screen() {
    initscr();
    noecho();
    raw();  // Disable CTRL-C etc.
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
    init_pair(15, COLOR_FG, COLOR_CYAN);
    init_pair(16, COLOR_CYAN, COLOR_BG);
    init_pair(17, COLOR_FG, COLOR_SUPERHOUSE);
    init_pair(18, COLOR_PLAYER, COLOR_SUPERHOUSE);
    init_pair(19, COLOR_GUARDIAN, COLOR_GRASS);
    init_pair(20, COLOR_GUARDIAN, COLOR_WATER);
    init_pair(21, COLOR_GUARDIAN, COLOR_BG);
}

/**
 * Prints intro text on the screen.
 */
void Game::intro() {
    return; // remove
    move(5, 10);
    attron(COLOR_PAIR(RED_BG));
    printw("Dr. Dark");
    attroff(COLOR_PAIR(RED_BG));
    printw(" has locked himself in a house");
    putstr("with a hostage.", 6, 10);
    putstr("Defeat the monsters, find the key to", 8, 10);
    putstr("his house and kill him.", 9, 10);
    putstr("Press p to play.", 12, 10);
    int input = getch();
    while (input != 'p') {
        input = getch();
    }
}

/**
 * Initialise game variables.
 */
void Game::init_game() {
    player.balance(Constants::PLAYER_START_BALANCE);
    player.level(Constants::PLAYER_START_LEVEL);
    player.hp(Constants::PLAYER_START_HP);
    
    store = {
        new Weapon("Sword", 3, 0, 12),
        new Weapon("Shield", 2, 3, 6),
        new Potion("Healing potion", 10, 2)
    };
}

/**
 * Quits the game.
 */
void Game::quit() {
    move(28, 1);
    clrtoeol();
    attron(COLOR_PAIR(BG_FG));
    addstr("Quit game? (y/n)");
    attroff(COLOR_PAIR(BG_FG));
    while (true) {
        int r = getch();
        if (r == 'y') {
            playing = false;
            pause_before_exit = false;
            break;
        }
        else if (r == 'n') {
            break;
        }
    }
}

/**
 * Loops as long as the player is alive. Waits for player input and performs actions.
 * At the end of each loop, draw() is called, and the board is updated.
 */
void Game::run() {
    draw();
    
    Enemy* enemy = nullptr;
    
    map<int,char> dirs;
    dirs[KEY_UP] = Direction::UP;
    dirs[KEY_DOWN] = Direction::DOWN;
    dirs[KEY_RIGHT] = Direction::RIGHT;
    dirs[KEY_LEFT] = Direction::LEFT;
    
    playing = true;
    pause_before_exit = true;
    
    while (playing && player.is_alive()) {
        int k = getch();  // Wait for input
        if (k == KEY_UP || k == KEY_DOWN || k == KEY_RIGHT || k == KEY_LEFT) {
            
            /* Move guardian */
            if (guardian_move) {
                for (int i = Constants::superhouse_pos.col - 1; i <= Constants::superhouse_pos.col + 1; i++) {
                    entities.at(Constants::superhouse_pos.row + 1).at(i) = NULL;
                }
                guardian->action(nullptr, nullptr);
                entities.at(guardian->position().row).at(guardian->position().col) = guardian;
                guardian_move = false;
            }
            else {
                guardian_move = true;
            }
            
            if (!player.go(dirs[k], environment, player.has_key())) {  // Check if player can go in given direction
                status_first = "You can't enter here";
                status_second = "";
            }
            /* If there is an enemy at player position */
            if ((enemy = dynamic_cast<Enemy*>(entities.at(player.position().row).at(player.position().col))) != NULL) {
                show_fight = true;
                show_buymenu = false;
                /* Set enemy hp and damage based on player level */
                if (enemy->is_alive()) {
                    enemy->hp(Constants::ENEMY_HP[player.level() - 1]);
                    enemy->max_hp(enemy->hp());
                    enemy->damage(Constants::ENEMY_BASE_DAMAGE * Constants::DAMAGE_PER_LEVEL_MULTIPLIER * player.level());
                }
            }
            else {
                show_fight = false;
            }

        }
        /* Bring up buymenu */
        else if (k == 'b' && !show_fight) {
            show_buymenu = !show_buymenu;
        }
        /* If buymenu is active and player clicks on a key */
        else if (show_buymenu) {
            for (unsigned i = 0; i < store.size(); ++i) {
                if (k == (char)(i+49)) {
                    player.buy(store.at(i));
                }
            }
        }
        /* Static keybind for using a healing potion */
        if (k == '9') {
            const string name = "Healing potion";
            /* Check if there is a healing potion in inventory, and use it */
            auto it = find_if(player.inventory().begin(), player.inventory().end(), [&name](const Item* i) {
                return i->name() == name;
            });
            if (it != player.inventory().end()) {
                player.action(nullptr, *it);
            }
        }
        /* Quit the game */
        if (k == 'q') {  // Quit
            quit();
        }

        /* Redraw the board */ 
        draw();

        /* If a fight is active, jump to fight() function */
        if (show_fight) {
            fight(enemy);
        }
    }

    /* Game is finished, press Q to quit */
    while (pause_before_exit) {
        if (getch() == 'q') {  // Quit
            quit();
        }
        draw();
    };

    /* Close the ncurses window */
    endwin();
}

/**
 * Simulates a fight against an enemy. Waits for player input, and makes the enemy fight back.
 * @param enemy A pointer to the enemy to fight
 */
void Game::fight(Enemy* enemy) {
    Item* item;
    bool attacked, healed;
    int enemy_hp = 0, player_hp = 0;
    while (enemy->is_alive() && player.is_alive()) {
        int k = getch();
        attacked = false;
        healed = false;
        
        /* Store player and enemy hp before each attack */
        enemy_hp = enemy->hp();
        player_hp = player.hp();
        
        if (k == 'q') {  // Quit
            quit();
            draw();
            break;
        }

        /* Press 0 to attack the enemy without a weapon */
        if (k == '0') {
            player.action(enemy, NULL);
            attacked = true;
        }

        /* Static keybind for using a healing potion */
        else if (k == '9') {
            const string name = "Healing potion";
            auto it = find_if(player.inventory().begin(), player.inventory().end(), [&name](const Item* i) {
                return i->name() == name;
            });
            if (it != player.inventory().end()) {
                player.action(nullptr, *it);
                attacked = true;
                healed = true;
            }
        }

        /* Attack with any weapon from the inventory */
        else {
            for (unsigned i = 0; i < player.inventory().size(); ++i) {
                if (k == (char)(i+49)) {
                    item = player.inventory().at(i);
                    /* If the chosen item from the inventory is a weapon, 
                     * use it to attack the enemy. */
                    if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {
                        player.action(enemy, weapon);
                        attacked = true;
                        break;
                    }
                }
            }
        }
        
        /* Player attacked the enemy but it is still alive */
        if (attacked && enemy->hp() > 0) {
            enemy->action(&player, NULL);
            
            if (healed) {
                status_first = "Healed for " + to_string(player.hp() - player_hp);
            }
            else {
                status_first = "You damaged " + enemy->name() + " for " + to_string(enemy_hp - enemy->hp());
            }
            status_second = enemy->name() + " damaged you for " + to_string(player_hp - player.hp());
            
            /* Player died, game over */
            if (!player.is_alive()) {
                status_first = "Game over";
                status_second = "You died";
                playing = false;
            }
        }

        /* Enemy died, give the player money and experience and exit the fight */
        else if (attacked && enemy->hp() == 0) {
            player.balance(player.balance() + enemy->max_hp()/10);
            player.exp(player.exp() + enemy->max_hp()/20);
            
            status_first = "You defeated " + enemy->name() + " (" + enemy->type() + ")";
            status_second = "";
            if (enemy->type() == "Final boss") {
                status_second = "You won the game";
                playing = false;
            }
            else if (player.level() == Constants::MAX_LEVEL) {
                const string key = "Super key";
                auto it = find_if(player.inventory().begin(), player.inventory().end(), [&key](const Item* i) {return i->name() == key;});
                if (it == player.inventory().end()) {
                    player.inventory().push_back(new Key("Super key"));
                    player.has_key(true);
                    status_first = "You retreived the Super key";
                    status_second = "Find Dr. Dark and kill him";
                }
            }
        }

        /* Redraw the board */
        draw();
    }
}

/**
 * Clears the screen and calls submethods for redrawing the screen.
 */
void Game::draw() {
    clearscr();
    
    draw_edges();
    draw_environment();
    draw_enemies();
    draw_player();
    draw_info();
    draw_inventory();
    draw_status();
    if (show_buymenu) draw_buymenu();
    if (show_fight) draw_fight();
    
    refresh();
}

/**
 * Draws the outer edges of the board.
 */
void Game::draw_edges() {
    show_fight ? attron(COLOR_PAIR(RED_BG)) : attron(COLOR_PAIR(GREEN_BG));
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
    show_fight ? attroff(COLOR_PAIR(RED_BG)) : attroff(COLOR_PAIR(GREEN_BG));
}

/**
 * Draws the environment on the board, (Houses, water, grass).
 */
void Game::draw_environment() {
    int row = 0, col = 0;
    for (auto &r : environment) {
        for (auto &e : r) {
            if (e->description().environment == "House") {
                attron(COLOR_PAIR(FG_HOUSE));
                putch('^', row, col);
                attroff(COLOR_PAIR(FG_HOUSE));
            }
            else if (e->description().environment == "Superhouse") {
                attron(COLOR_PAIR(FG_SUPERHOUSE));
                putch('^', row, col);
                attroff(COLOR_PAIR(FG_SUPERHOUSE));
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

void Game::draw_enemies() {
    Entity::Position pos = guardian->position();
    auto color = COLOR_PAIR(GUARDIAN_BG);
    if (environment.at(pos.row).at(pos.col)->description().environment == "Water")
        color = COLOR_PAIR(GUARDIAN_WATER);
    else if (environment.at(pos.row).at(pos.col)->description().environment == "Grass")
        color = COLOR_PAIR(GUARDIAN_GRASS);
    
    move(guardian->position().row + 1, guardian->position().col * 2 + 1);

    attron(color);
    addch('T');
    addch('T');
    attroff(color);
}

/**
 * Gets the player position, finds the correct background color and draws the player.
 */
void Game::draw_player() {
    Entity::Position pos = player.position();
    auto color = COLOR_PAIR(PLAYER_BG);
    if (environment.at(pos.row).at(pos.col)->description().environment == "House")
        color = COLOR_PAIR(PLAYER_HOUSE);
    else if (environment.at(pos.row).at(pos.col)->description().environment == "Superhouse")
        color = COLOR_PAIR(PLAYER_SUPERHOUSE);
    else if (environment.at(pos.row).at(pos.col)->description().environment == "Water")
        color = COLOR_PAIR(PLAYER_WATER);
    else if (environment.at(pos.row).at(pos.col)->description().environment == "Grass")
        color = COLOR_PAIR(PLAYER_GRASS);
    
    move(pos.row + 1, pos.col * 2 + 1);
    attron(color);
    addch('(');
    addch(')');
    attroff(color);
}

/**
 * Prints and draws player info, such as name, health, experience, level and balance.
 */
void Game::draw_info() {
    int i;
    
    /* Level */
    move(22, 2);
    printw("Level %d/%d", player.level(), Constants::MAX_LEVEL);
    move(22, 16 - ceil(log10(player.max_exp()+1)));
    printw("%3d/%d", player.exp(), player.max_exp());
    
    /* Experience */
    move(23, 1);
    attron(COLOR_PAIR(FG_CYAN));
    for (i = 0; i < (player.exp() / (double)player.max_exp()) * 20; i++) {
        if (i == 0)
            addch('[');
        else if (i == 19)
            addch(']');
        else
            addch(' ');
    }
    attroff(COLOR_PAIR(FG_CYAN));
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
    
    /* Health */
    putstr("Health", 22, 22);
    move(22, 36 - ceil(log10(player.max_hp()+1)));
    printw("%3d/%d", player.hp(), player.max_hp());
    
    /* Health bar */
    move(23, 21);
    attron(COLOR_PAIR(FG_GREEN));
    for (i = 0; i < (player.hp() / (double)player.max_hp()) * 20; i++) {
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
    
    /* Name */
    move(25, 1);
    attron(COLOR_PAIR(CYAN_BG));
    attron(A_UNDERLINE);
    printw("   %s   ", player.name().c_str());
    attroff(A_UNDERLINE);
    attroff(COLOR_PAIR(CYAN_BG));
    
    /* Damage & block */
    move(26, 1);
    printw("Damage: \t%d (+%d)", player.damage(), player.base_damage());
    move(27, 1);
    printw("Block: \t%d", player.block());
    
    /* Balance */
    move(22, 50);
    printw("Balance: ");
    attron(COLOR_PAIR(YELLOW_BG));
    printw("$%d", player.balance());
    attroff(COLOR_PAIR(YELLOW_BG));
}

/**
 * Prints the contents of the player's inventory.
 */
void Game::draw_inventory() {
    int j = 1;
    int num_potions = 0;
    int i_start = 20 - ((int)player.inventory().empty() ? 1 : (int)player.inventory().size());
    bool found = false;
    for (auto it = player.inventory().begin(); it != player.inventory().end(); ++it) {
        if (dynamic_cast<Potion*>(*it)) {
            found = true;
            num_potions++;
        }
    }
    if (found) i_start += num_potions - 1;
    
    int i = i_start;
    if (show_fight && !player.inventory().empty())
        i--;
    
    move(i++, 50);
    if (!show_buymenu)
        attron(COLOR_PAIR(GREEN_BG));
    attron(A_UNDERLINE);
    printw("      INVENTORY      ");
    attroff(A_UNDERLINE);
    if (!show_buymenu)
        attroff(COLOR_PAIR(GREEN_BG));
    
    if (show_fight) {
        move(i++, 50);
        printw("0. Kick");
    }
    
    /* Go through the inventory and print the item if it's not a potion */
    Weapon* w = nullptr;
    for (auto it = player.inventory().begin(); it != player.inventory().end(); ++it) {
        w = nullptr;
        if (!(dynamic_cast<Potion*>(*it))) {
            move(i++, 50);
            /* Print <#>. <wpn.name>  (<dmg>, <blk>) */
            if ((w = dynamic_cast<Weapon*>(*it)) && show_fight)
                printw("%d. ", j++);
            printw((*it)->name().c_str());
            if (w != nullptr) {
                printw(" \t(");
                attron(COLOR_PAIR(RED_BG));
                printw("%2d", w->damage());
                attroff(COLOR_PAIR(RED_BG));
                printw(", ");
                attron(COLOR_PAIR(CYAN_BG));
                printw("%2d", w->block());
                attroff(COLOR_PAIR(CYAN_BG));
                printw(")");
            }
        }
    }
    
    /* Print potions separately, along with the quantity */ 
    const string name = "Healing potion";
    auto it = find_if(player.inventory().begin(), player.inventory().end(), [&name](const Item* i) {return i->name() == name;});
    if (it != player.inventory().end()) {
        move(i++, 50);
        printw("9. %s x%d (", name.c_str(), num_potions);
        attron(COLOR_PAIR(GREEN_BG));
        printw("%d", ((Potion*) *it)->healing());
        attroff(COLOR_PAIR(GREEN_BG));
        printw(")");
    }

    /* Print "Empty" if inventory is empty */
    move(i, 50);
    if (!show_fight && i == i_start + 1) {
        attron(COLOR_PAIR(YELLOW_BG));
        printw("Empty");
        attroff(COLOR_PAIR(YELLOW_BG));
    }
}

/**
 * Prints status messages.
 */
void Game::draw_status() {
    move(24, 50);
    printw("%s", status_first.c_str());
    move(25, 50);
    printw("%s", status_second.c_str());
}

/**
 * Prints all buyable items in the store.
 */
void Game::draw_buymenu() {
    attron(A_UNDERLINE);
    attron(COLOR_PAIR(GREEN_BG));
    putstr("       BUYMENU       ", 1, 50);
    attroff(COLOR_PAIR(GREEN_BG));
    attroff(A_UNDERLINE);
    
    int choice = 1, i = 2;
    for (auto it = store.begin(); it != store.end(); ++it) {
        move(i++, 50);
        /* Prints <#>. $<cost> <item.name>  (<dmg>, <blk>, <healing>) */
        printw("%d. $%-3d %s", choice++, (*it)->price(), (*it)->name().c_str());
        if (Weapon* w = dynamic_cast<Weapon*>(*it)) {
            printw(" (");
            attron(COLOR_PAIR(RED_BG));
            printw("%d", w->damage());
            attroff(COLOR_PAIR(RED_BG));
            printw(", ");
            attron(COLOR_PAIR(CYAN_BG));
            printw("%d", w->block());
            attroff(COLOR_PAIR(CYAN_BG));
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

/**
 * Draws the fight between the player and an enemy.
 */
void Game::draw_fight() {
    
    if (Enemy* enemy = dynamic_cast<Enemy*>(entities.at(player.position().row).at(player.position().col))) {
    
        move(1, 50);
        attron(A_UNDERLINE);
        attron(COLOR_PAIR(RED_BG));
        printw("        FIGHT        ");
        attroff(A_UNDERLINE);
        attroff(COLOR_PAIR(RED_BG));
        
        /* Enemy name */
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
        
        /* Enemy damage */
        move(3, 50);
        if (enemy->type() == "Guardian")
            printw("Damage: %d", 1000);
        else
            printw("Damage: %d", enemy->damage());
        
        /* Enemy health */
        putstr("Health", 4, 50);
        move(4, 66 - ceil(log10(enemy->max_hp()+1)));
        printw("%3d/%d", enemy->hp(), enemy->max_hp());
        
        /* Enemy health bar */
        int i;
        move(5, 50);
        attron(COLOR_PAIR(FG_GREEN));
        for (i = 0; i < (enemy->hp() / (double)enemy->max_hp()) * 20; i++) {
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

/**
 * Prints a char at given position.
 * @param c   char to print
 * @param row Row
 * @param col Column
 */
void Game::putch(char c, int row, int col) {
    move(row + 1, col * 2 + 1);
    addch(c);
    addch(c);
}

/**
 * Prints a string at given position.  
 * @param s   String to print
 * @param row Row
 * @param col Column
 */
void Game::putstr(string s, int row, int col) {
    move(row, col);
    printw(s.c_str());
}

/**
 * Clears necessary parts of the screen.
 */
void Game::clearscr() {
    // TODO adjust to info pane
    for (int i = 0; i < 22; i++) {
        move(i, 41);
        clrtoeol();
    }
    for (int i = 22; i < 29; i++) {
        move(i, 0);
        clrtoeol();
    }
}