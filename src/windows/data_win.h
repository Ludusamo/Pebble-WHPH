#ifndef DATAWIN_H
#define DATAWIN_H

#include <pebble.h>

#include "module/app_message.h"
#include "layers/bipercent_layer.h"
#include "module/shared_val.h"

Window *data_window;
BipercentLayer *bipercent;

int32_t work_time;
int32_t play_time;

void exit_data_win(ClickRecognizerRef recognizer, void *context);
void data_click_config_provider(void *context);

void data_win_create();
void data_win_destroy();

void push_data_win(bool animated);
void remove_data_win(bool animated);

#endif // DATAWIN_H
