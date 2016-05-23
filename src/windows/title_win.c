#include "title_win.h"

void title_continue_callback(ClickRecognizerRef recognizer, void *context) {	
	push_select_win(true);
}

void title_click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_SELECT, title_continue_callback);
}

void register_click_providers() {
	window_set_click_config_provider(title_window, title_click_config_provider);
}

void create_title(Layer* window_layer, GRect bounds) {
	bounds.origin.y += bounds.size.h / 20;
	title = text_layer_create(bounds);
	text_layer_set_text(title, TITLE);
	text_layer_set_font(title, fonts_get_system_font(FONT_KEY_DROID_SERIF_28_BOLD));
	text_layer_set_text_alignment(title, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(title));
	text_layer_enable_screen_text_flow_and_paging(title, 2);
}

void create_company(Layer* window_layer, GRect bounds) {
	bounds.size.h /= 4;
	bounds.origin.y += bounds.size.h * 3;
	company = text_layer_create(bounds);
	text_layer_set_text(company, COMPANY);
	text_layer_set_text_alignment(company, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(company));
}

void title_win_create() {
	title_window = window_create();

	register_click_providers();

	Layer *window_layer = window_get_root_layer(title_window);
	GRect bounds = layer_get_bounds(window_layer);

	create_title(window_layer, bounds);
	create_company(window_layer, bounds);

	select_win_create();
}

void title_win_destroy() {
	select_win_destroy();
	text_layer_destroy(title);
	text_layer_destroy(company);
	window_destroy(title_window);
}

void push_title_win(bool animated) {
	window_stack_push(title_window, animated);
}

void remove_title_win(bool animated) {
	window_stack_remove(title_window, animated);
}
