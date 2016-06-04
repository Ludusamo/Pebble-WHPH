#include "workplay_win.h"

void create_time_display(Layer *window_layer, GRect bounds) {
	#if defined(PBL_RECT)
	bounds.origin.x -= ACTION_BAR_WIDTH;
	#endif
	bounds.origin.y += bounds.size.h / 20;
	bounds.size.h /= 3;		

	time_display = text_layer_create(bounds);
	text_layer_set_text(time_display, elapsed_time);
	text_layer_set_font(time_display, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(time_display, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(time_display));
	text_layer_enable_screen_text_flow_and_paging(time_display, 2);
}

void create_stop_display(Layer *window_layer, GRect bounds) {
	#if defined(PBL_RECT)
	bounds.origin.x -= ACTION_BAR_WIDTH;
	#endif
	bounds.origin.y += bounds.size.h * 2 / 3;	
	bounds.size.h /= 3;

	stop_display = text_layer_create(bounds);
	text_layer_set_text(stop_display, "Stop?");
	text_layer_set_font(stop_display, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(stop_display, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(stop_display));
	text_layer_enable_screen_text_flow_and_paging(stop_display, 2);
}

void create_start_display(Layer *window_layer, GRect bounds) {
	#if defined(PBL_RECT)
	bounds.origin.x -= ACTION_BAR_WIDTH;
	#endif
	bounds.origin.y += bounds.size.h * 1 / 3;	
	bounds.size.h /= 3;

	start_display = text_layer_create(bounds);
	text_layer_set_text(start_display, "Start?");
	text_layer_set_font(start_display, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(start_display, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(start_display));	
	text_layer_enable_screen_text_flow_and_paging(start_display, 2);
}

void create_actionbar() {
	actionbar = action_bar_layer_create();
	action_bar_layer_set_click_config_provider(actionbar, action_bar_provider);
	
	tick_bitmap = gbitmap_create_with_resource(RESOURCE_ID_TICK);
	cross_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CROSS);

	action_bar_layer_set_icon(actionbar, BUTTON_ID_UP, tick_bitmap);
	action_bar_layer_set_icon(actionbar, BUTTON_ID_DOWN, cross_bitmap);
	action_bar_layer_add_to_window(actionbar, workplay_window);
}

void set_elapsed_time() {
	int difference = time(NULL) - beginning;
	int hours = difference / 3600;
	difference %= 3600;
	int minutes = difference / 60;
	difference %= 60;
	int seconds = difference;
	snprintf(elapsed_time, 10, "%02d:%02d:%02d", hours, minutes, seconds);
	layer_mark_dirty((Layer*) time_display);
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
	set_elapsed_time();
}

void start_callback(ClickRecognizerRef recognizer, void *context) {
	start_timer(cur_mode, time(NULL));
	remove_workplay_win(true);
}

void exit_callback(ClickRecognizerRef recognizer, void *context) {	
	remove_workplay_win(true);
}

void stop_callback(ClickRecognizerRef recognizer, void *context) {
	stop_timer(cur_mode, beginning, time(NULL), "PLACEHOLDER");
	remove_workplay_win(true);
}

void action_bar_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_UP, (ClickHandler) (in_mode) ? stop_callback : start_callback);
	window_single_click_subscribe(BUTTON_ID_DOWN, (ClickHandler) exit_callback);
	window_single_click_subscribe(BUTTON_ID_BACK, (ClickHandler) exit_callback);
}

void workplay_win_create(MODE mode) {
	if (persist_exists(CUR_MODE)) in_mode = persist_read_int(CUR_MODE) == mode;
	else in_mode = 0;
	cur_mode = mode;
	workplay_window = window_create();
	
	Layer *window_layer = window_get_root_layer(workplay_window);
	GRect bounds = layer_get_bounds(window_layer);

	if (in_mode) {
		beginning = persist_read_int(BEGINNING_TIME);	
		start_display = 0;
		create_time_display(window_layer, bounds);
		create_stop_display(window_layer, bounds);	

		set_elapsed_time();
		
		tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
	} else {
		time_display = 0;
		stop_display = 0;
		create_start_display(window_layer, bounds);
	}
	create_actionbar();
}

void workplay_win_destroy() {
	if (time_display) text_layer_destroy(time_display);
	if (stop_display) text_layer_destroy(stop_display);
	if (start_display) text_layer_destroy(start_display);
	action_bar_layer_destroy(actionbar);
	gbitmap_destroy(tick_bitmap);
	gbitmap_destroy(cross_bitmap);
	tick_timer_service_unsubscribe();

	window_destroy(workplay_window);
}

void push_workplay_win(bool animated) {
	if (workplay_window) window_stack_push(workplay_window, animated);
}

void remove_workplay_win(bool animated) {
	window_stack_remove(workplay_window, animated);
	workplay_win_destroy();
}
