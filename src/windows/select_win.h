#ifndef SELECTWIN_H
#define SELECTWIN_H

#include <pebble.h>

#include "workplay_win.h"

#define NUM_MENU_SECTIONS 1
#define NUM_ITEMS 2

Window *select_window;
SimpleMenuLayer *menu;
SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];
SimpleMenuItem menu_items[NUM_ITEMS];

void menu_select_callback();
void menu_sections_init();
void menu_items_init();

void select_win_create();
void select_win_destroy();

void push_select_win(bool animated);
void remove_select_win(bool animated);

#endif // SELECTWIN_H
