#ifndef WORKPLAYWIN_H
#define WORKPLAYWIN_H

#include <pebble.h>
#include "module/app_message.h"
#include "module/timer.h"
#include "module/shared_val.h"

int in_mode;
time_t beginning;
char elapsed_time[10];
int cur_mode;

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

void workplay_win_create(int mode);
void workplay_win_destroy();

void push_workplay_win(bool animated);
void remove_workplay_win(bool animated);

#endif // PLAYWORKWIN_H
