#ifndef DATAWIN_H
#define DATAWIN_H

#include <pebble.h>

Window *data_window;
MenuLayer *data_list;

int32_t work_time;
int32_t play_time;

void exit_data_win(ClickRecognizerRef recognizer, void *context);
void data_click_config_provider(void *context);

uint16_t get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *context);
void draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *context);
int16_t get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context);
void select_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context);

void req_data();
void receive_data_callback(DictionaryIterator *iter, void *context);

void data_win_create();
void data_win_destroy();

void push_data_win(bool animated);
void remove_data_win(bool animated);

#endif // DATAWIN_H