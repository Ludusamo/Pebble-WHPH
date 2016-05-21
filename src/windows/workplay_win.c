#include "workplay_win.h"

void start_timer() {

}

void stop_timer() {

}

void yes_callback() {

}

void no_callback() {

}

void stop_callback() {

}

void workplay_menu_sections_init(WorkPlay_Win *win) {
	win->menu_sections[0] = (SimpleMenuSection) {
		.num_items = NUM_ITEMS,
		.items = win->menu_items
	};
}

void workplay_menu_items_init(WorkPlay_Win *win) {
	int i = 0;
	win->menu_items[i++] = (SimpleMenuItem) {
		.title = "Yes",
		.callback = yes_callback
	};
	win->menu_items[i++] = (SimpleMenuItem) {
		.title= "No",
		.callback = no_callback
	};
}

WorkPlay_Win *workplay_win_create(MODE mode) {
	WorkPlay_Win *win = (WorkPlay_Win*) malloc(sizeof(WorkPlay_Win));
	if (win) {
		win->window = window_create();
		
		workplay_menu_items_init(win);
		workplay_menu_sections_init(win);

		Layer *window_layer = window_get_root_layer(win->window);
		GRect time_bounds = layer_get_bounds(window_layer);
		GRect stop_bounds = layer_get_bounds(window_layer);
		GRect start_bounds = layer_get_bounds(window_layer);
		GRect menu_bounds = layer_get_bounds(window_layer);

		time_bounds.origin.y += time_bounds.size.h / 20;
		time_bounds.size.h /= 3;		
		win->time_display = text_layer_create(time_bounds);
		text_layer_set_text(win->time_display, "00:00");
		text_layer_set_text_alignment(win->time_display, GTextAlignmentCenter);

		stop_bounds.origin.y += stop_bounds.size.h * 2 / 3;	
		stop_bounds.size.h /= 3;
		win->stop_display = text_layer_create(stop_bounds);
		text_layer_set_text(win->stop_display, "Stop?");
		text_layer_set_text_alignment(win->stop_display, GTextAlignmentCenter);
		
		layer_add_child(window_layer, text_layer_get_layer(win->time_display));
		layer_add_child(window_layer, text_layer_get_layer(win->stop_display));
		
    		text_layer_enable_screen_text_flow_and_paging(win->time_display, 2);
    		text_layer_enable_screen_text_flow_and_paging(win->stop_display, 2);
		return win;
	}
	return NULL;
}

void workplay_win_destroy(WorkPlay_Win *win) {
	if (win) {
		text_layer_destroy(win->time_display);
		text_layer_destroy(win->stop_display);
		text_layer_destroy(win->start_display);
		simple_menu_layer_destroy(win->menu);
		free(win);
		win = NULL;
	}
}

void push_workplay_win(WorkPlay_Win *win, bool animated) {
	window_stack_push(win->window, animated);
}

void remove_workplay_win(WorkPlay_Win *win, bool animated) {
	window_stack_remove(win->window, animated);
}
