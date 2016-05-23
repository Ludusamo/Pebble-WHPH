#ifndef SETTINGSWIN_H
#define SETTINGSWIN_H

#include <pebble.h>

#define NUM_SET_MENU_SECTIONS 1
#define NUM_SET_ITEMS 1

Window *settings_window;
MenuLayer *settings_menu;
SimpleMenuSection settings_menu_sections[NUM_SET_MENU_SECTIONS];
SimpleMenuItem settings_menu_items[NUM_SET_ITEMS];


#endif // SETTINGSWIN_H
