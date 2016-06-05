#include "data_win.h"

void exit_data_win(ClickRecognizerRef recognizer, void *context) {
	remove_data_win(true);
	data_win_destroy();
}

void data_click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_BACK, (ClickHandler) exit_data_win);
}

void data_win_create() {
	data_window = window_create();
	
	uint32_t work_time = persist_read_int(WORK_TIME);
	uint32_t play_time = persist_read_int(PLAY_TIME);

	Layer *window_layer = window_get_root_layer(data_window);
	GRect bounds = layer_get_bounds(window_layer);

	bipercent = bipercent_layer_create(bounds);
	bipercent_layer_set_percent(bipercent, work_time * 100 / (work_time + play_time));
	bipercent_layer_set_keys(bipercent, "Work", "Play");
	layer_add_child(window_layer, bipercent);
	window_set_click_config_provider(data_window, data_click_config_provider);
}

void data_win_destroy() {
	bipercent_layer_destroy(bipercent);
	window_destroy(data_window);
}

void push_data_win(bool animated) {
	window_stack_push(data_window, animated);
}

void remove_data_win(bool animated) {
	window_stack_remove(data_window, animated);
}
