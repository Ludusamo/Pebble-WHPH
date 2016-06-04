#ifndef WORKPLAYWIN_H
#define WORKPLAYWIN_H

#include <pebble.h>
#include "module/app_message.h"
#include "module/timer.h"

#define BEGINNING_TIME 0
#define CUR_MODE 1

typedef enum {
	WORK, PLAY
} MODE;

int in_mode;
time_t beginning;
char elapsed_time[10];
MODE cur_mode;

Window *workplay_window;

TextLayer *time_display;
TextLayer *stop_display;
TextLayer *start_display;

GBitmap *tick_bitmap, *cross_bitmap;
ActionBarLayer *actionbar;

void create_time_display(Layer *window_layer, GRect bounds);
void create_stop_display(Layer *window_layer, GRect bounds);
void create_start_display(Layer *window_layer, GRect bounds);

void create_actionbar();

void set_elapsed_time();
void tick_handler(struct tm *tick_time, TimeUnits units_changed);

void start_callback(ClickRecognizerRef recognizer, void *context);
void exit_callback(ClickRecognizerRef recognizer, void *context);
void stop_callback(ClickRecognizerRef recognizer, void *context);
void action_bar_provider(void *context);

void workplay_win_create(MODE mode);
void workplay_win_destroy();

void push_workplay_win(bool animated);
void remove_workplay_win(bool animated);

#endif // PLAYWORKWIN_H
