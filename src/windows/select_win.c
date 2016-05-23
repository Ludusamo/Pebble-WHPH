#include "select_win.h"

void menu_select_callback(int index, void *context) {
	workplay_win_create(index);
	push_workplay_win(true);
}

void menu_sections_init(Select_Win *win) {	
	win->menu_sections[0] = (SimpleMenuSection) {
		.num_items = NUM_ITEMS,
		.items = win->menu_items
	};
}

void menu_items_init(Select_Win *win) {
	int i = 0;
	win->menu_items[i++] = (SimpleMenuItem) {
		.title = "Work",
		.callback = menu_select_callback
	};
	win->menu_items[i++] = (SimpleMenuItem) {
		.title = "Play",
		.callback = menu_select_callback
	};
}

Select_Win *select_win_create() {
	Select_Win *select_window = (Select_Win*) malloc(sizeof(Select_Win));
	if (select_window) {
		select_window->window = window_create();
		
		menu_items_init(select_window);
		menu_sections_init(select_window);		

		Layer *window_layer = window_get_root_layer(select_window->window);
		GRect bounds = layer_get_bounds(window_layer);
	
		select_window->menu = simple_menu_layer_create(bounds, select_window->window, select_window->menu_sections, NUM_MENU_SECTIONS, NULL);
		layer_add_child(window_layer, simple_menu_layer_get_layer(select_window->menu));
		return select_window;
	}
	return NULL;
}

void select_win_destroy(Select_Win *win) {
	if (win) {
		simple_menu_layer_destroy(win->menu);
		window_destroy(win->window);
		free(win);
		win = NULL;
	}
}

void push_select_win(Select_Win *win, bool animated) {
	window_stack_push(win->window, animated);
}

void remove_select_win(Select_Win *win, bool animated) {
	window_stack_remove(win->window, animated);
}
