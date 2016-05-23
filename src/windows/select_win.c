#include "select_win.h"

void menu_select_callback(int index, void *context) {
	if (index < 2) {
		workplay_win_create(index);
		push_workplay_win(true);
	}
}

void menu_sections_init() {	
	menu_sections[0] = (SimpleMenuSection) {
		.num_items = NUM_ITEMS,
		.items = menu_items
	};
}

void menu_items_init() {
	int i = 0;
	menu_items[i++] = (SimpleMenuItem) {
		.title = "Work",
		.callback = menu_select_callback
	};
	menu_items[i++] = (SimpleMenuItem) {
		.title = "Play",
		.callback = menu_select_callback
	};
	menu_items[i++] = (SimpleMenuItem) {
		.title = "Settings",
		.callback = menu_select_callback
	};
}

void select_win_create() {
	select_window = window_create();
	
	menu_items_init();
	menu_sections_init();		

	Layer *window_layer = window_get_root_layer(select_window);
	GRect bounds = layer_get_bounds(window_layer);

	menu = simple_menu_layer_create(bounds, select_window, menu_sections, NUM_MENU_SECTIONS, NULL);
	layer_add_child(window_layer, simple_menu_layer_get_layer(menu));
}

void select_win_destroy() {
	simple_menu_layer_destroy(menu);
	window_destroy(select_window);
}

void push_select_win(bool animated) {
	window_stack_push(select_window, animated);
}

void remove_select_win(bool animated) {
	window_stack_remove(select_window, animated);
}
