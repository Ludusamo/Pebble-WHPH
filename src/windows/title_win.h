#ifndef TITLEWIN_H
#define TITLEWIN_H

#include <pebble.h>

typedef struct {
	Window *window;	
	TextLayer *title;
	TextLayer *company;
} Title_Win;

void title_continue_callback();
void register_click_providers();

Title_Win *title_win_create();
void title_win_destroy(Title_Win *win);

void push_title_win(Title_Win *win, bool animated);
void remove_title_win(Title_Win *win, bool animated);

#endif // TITLEWIN_H
