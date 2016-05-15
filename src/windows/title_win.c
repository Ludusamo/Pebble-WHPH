#include "title_win.h"

void title_continue_callback() {

}

void register_click_providers() {

}

Title_Win *title_win_create() {
	Title_Win *win = (Title_Win*) malloc(sizeof(Title_Win));
	if (win) {
		win->window = window_create();

		Layer *window_layer = window_get_root_layer(win->window);
		GRect title_bounds = layer_get_bounds(window_layer);
		GRect company_bounds = layer_get_bounds(window_layer);

		// Relative positioning
		title_bounds.origin.y += title_bounds.size.h / 3;
		title_bounds.size.h /= 2;
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
		return win;
	}
	return NULL;
}

void title_win_destroy(Title_Win *win) {
	if (win) {
		text_layer_destroy(win->title);
		text_layer_destroy(win->company);
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
