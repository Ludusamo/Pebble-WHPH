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

int in_mode;
MODE cur_mode;

typedef enum {
	TIMER, STORE
} AppKey;

typedef struct {
	Window *window;

	TextLayer *time_display;
	TextLayer *stop_display;
	TextLayer *start_display;

	GBitmap *tick_bitmap, *cross_bitmap;
	ActionBarLayer *actionbar;
} WorkPlay_Win;

TextLayer *create_time_display(GRect bounds);
TextLayer *create_stop_display(GRect bounds);
TextLayer *create_start_display(GRect bounds);
void create_actionbar(WorkPlay_Win *win);

void start_timer(); 
void stop_timer(); 

void start_callback(ClickRecognizerRef recognizer, void *context);
void exit_callback(ClickRecognizerRef recognizer, void *context);
void stop_callback(ClickRecognizerRef recognizer, void *context);
void action_bar_provider(void *context);

WorkPlay_Win *workplay_win_create(MODE mode);
void workplay_win_destroy(WorkPlay_Win *win);

void push_workplay_win(WorkPlay_Win *win, bool animated);
void remove_workplay_win(WorkPlay_Win *win, bool animated);

#endif // PLAYWORKWIN_H
