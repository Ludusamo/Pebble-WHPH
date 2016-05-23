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

void title_win_create() {
	title_window = window_create();

	register_click_providers();

	Layer *window_layer = window_get_root_layer(title_window);
	GRect title_bounds = layer_get_bounds(window_layer);
	GRect company_bounds = layer_get_bounds(window_layer);

	// Relative positioning
	title_bounds.origin.y += title_bounds.size.h / 20;
	title = text_layer_create(title_bounds);

	company_bounds.size.h /= 4;
	company_bounds.origin.y += company_bounds.size.h * 3;
	company = text_layer_create(company_bounds);

	text_layer_set_text(title, "Work Hard\nPlay Hard!");
	text_layer_set_font(title, fonts_get_system_font(FONT_KEY_DROID_SERIF_28_BOLD));
	text_layer_set_text_alignment(title, GTextAlignmentCenter);

	text_layer_set_text(company, "Ludusamo");
	text_layer_set_text_alignment(company, GTextAlignmentCenter);

	layer_add_child(window_layer, text_layer_get_layer(title));
	layer_add_child(window_layer, text_layer_get_layer(company));

	text_layer_enable_screen_text_flow_and_paging(title, 2);

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
