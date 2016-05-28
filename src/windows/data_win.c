#include "data_win.h"

void exit_data_win(ClickRecognizerRef recognizer, void *context) {
	remove_data_win(true);
	data_win_destroy();
}

void data_click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_BACK, (ClickHandler) exit_data_win);
}

void req_data() {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Requesting Data");
	begin_app_message();
	register_uint8(TYPE, 2);
	send_message();
}

void receive_data_callback(DictionaryIterator *iter, void *context) {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Received Data");
	Tuple *work_tupe = dict_find(iter, 2);
	if (work_tupe) {
		work_time = work_tupe->value->int32;
	}

	Tuple *play_tupe = dict_find(iter, 3);
	if (play_tupe) {
		play_time = play_tupe->value->int32;
	}
	
	if (play_tupe && work_tupe) {
		Layer *window_layer = window_get_root_layer(data_window);
		GRect bounds = layer_get_bounds(window_layer);

		bipercent = bipercent_layer_create(bounds);
		bipercent_layer_set_percent(bipercent, work_time * 100 / (work_time + play_time));
		bipercent_layer_set_keys(bipercent, "Work", "Play");
		layer_add_child(window_layer, bipercent);
	}
	window_set_click_config_provider(data_window, data_click_config_provider);
}

void data_win_create() {
	data_window = window_create();
	
	app_message_register_inbox_received(receive_data_callback);
	req_data();	
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
