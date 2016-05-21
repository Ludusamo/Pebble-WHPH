#ifndef WORKPLAYWIN_H
#define WORKPLAYWIN_H

#include <pebble.h>

#define BEGINNING_TIME 0
#define CUR_MODE 1

#define NUM_MENU_SECTIONS 1
#define NUM_ITEMS 2

typedef enum {
	WORK, PLAY
} MODE;

typedef struct {
	Window *window;
	MODE mode;

	TextLayer *time_display;
	TextLayer *stop_display;
	TextLayer *start_display;

	SimpleMenuLayer *menu;
	SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];
	SimpleMenuItem menu_items[NUM_ITEMS];
} WorkPlay_Win;

void start_timer(); 
void stop_timer(); 

void yes_callback();
void no_callback();
void stop_callback();
void workplay_menu_sections_init(WorkPlay_Win *win);
void workplay_menu_items_init(WorkPlay_Win *win);

WorkPlay_Win *workplay_win_create(MODE mode);
void workplay_win_destroy(WorkPlay_Win *win);

void push_workplay_win(WorkPlay_Win *win, bool animated);
void remove_workplay_win(WorkPlay_Win *win, bool animated);

#endif // PLAYWORKWIN_H
