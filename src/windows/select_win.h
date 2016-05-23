#ifndef SELECTWIN_H
#define SELECTWIN_H

#include <pebble.h>

#include "workplay_win.h"

#define NUM_MENU_SECTIONS 1
#define NUM_ITEMS 2

typedef struct {
	Window *window;
	SimpleMenuLayer *menu;
	SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];
	SimpleMenuItem menu_items[NUM_ITEMS];
} Select_Win;

void menu_select_callback();
void menu_sections_init(Select_Win *win);
void menu_items_init(Select_Win *win);

Select_Win *select_win_create();
void select_win_destroy(Select_Win *win);

void push_select_win(Select_Win *win, bool animated);
void remove_select_win(Select_Win *win, bool animated);

#endif // SELECTWIN_H
