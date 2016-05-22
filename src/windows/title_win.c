#include "title_win.h"

void title_continue_callback(ClickRecognizerRef recognizer, void *context) {	
	push_select_win(select_win, true);
}

void title_click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_SELECT, title_continue_callback);
}

void register_click_providers(Title_Win *win) {
	window_set_click_config_provider(win->window, title_click_config_provider);
}

Title_Win *title_win_create() {
	Title_Win *win = (Title_Win*) malloc(sizeof(Title_Win));
	if (win) {
		win->window = window_create();

		register_click_providers(win);

		Layer *window_layer = window_get_root_layer(win->window);
		GRect title_bounds = layer_get_bounds(window_layer);
		GRect company_bounds = layer_get_bounds(window_layer);

		// Relative positioning
    		title_bounds.origin.y += title_bounds.size.h / 20;
		win->title = text_layer_create(title_bounds);

		company_bounds.size.h /= 4;
		company_bounds.origin.y += company_bounds.size.h * 3;
		win->company = text_layer_create(company_bounds);

		text_layer_set_text(win->title, "Work Hard\nPlay Hard!");
		text_layer_set_font(win->title, fonts_get_system_font(FONT_KEY_DROID_SERIF_28_BOLD));
		text_layer_set_text_alignment(win->title, GTextAlignmentCenter);

		text_layer_set_text(win->company, "Ludusamo");
		text_layer_set_text_alignment(win->company, GTextAlignmentCenter);

		layer_add_child(window_layer, text_layer_get_layer(win->title));
		layer_add_child(window_layer, text_layer_get_layer(win->company));
    
    		text_layer_enable_screen_text_flow_and_paging(win->title, 2);

		select_win = select_win_create();
		return win;
	}
	return NULL;
}

void title_win_destroy(Title_Win *win) {
	if (win) {
		select_win_destroy(select_win);
		select_win = NULL;
		text_layer_destroy(win->title);
		text_layer_destroy(win->company);
		window_destroy(win->window);
		free(win);
		win = NULL;
	}
}

void push_title_win(Title_Win *win, bool animated) {
	window_stack_push(win->window, animated);
}

void remove_title_win(Title_Win *win, bool animated) {
	window_stack_remove(win->window, animated);
}
