#ifndef TITLEWIN_H
#define TITLEWIN_H

#include <pebble.h>

#include "select_win.h"

Window *title_window;	
TextLayer *title;
TextLayer *company;

void title_continue_callback(ClickRecognizerRef recognizer, void *context);
void title_click_config_provider(void *context);
void register_click_providers();

void create_title(Layer* window_layer, GRect bounds);
void create_company(Layer* window_layer, GRect bounds);

void title_win_create();
void title_win_destroy();

void push_title_win(bool animated);
void remove_title_win(bool animated);

#endif // TITLEWIN_H
