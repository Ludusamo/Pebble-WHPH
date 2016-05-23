#include "workplay_win.h"

TextLayer *create_time_display(GRect bounds) {
	#if defined(PBL_RECT)
	bounds.origin.x -= ACTION_BAR_WIDTH;
	#endif
	bounds.origin.y += bounds.size.h / 20;
	bounds.size.h /= 3;		
	TextLayer *text = text_layer_create(bounds);
	text_layer_set_text(text, elapsed_time);
	text_layer_set_font(text, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text, GTextAlignmentCenter);
	return text;
}

TextLayer *create_stop_display(GRect bounds) {
	#if defined(PBL_RECT)
	bounds.origin.x -= ACTION_BAR_WIDTH;
	#endif
	bounds.origin.y += bounds.size.h * 2 / 3;	
	bounds.size.h /= 3;
	TextLayer *text = text_layer_create(bounds);
	text_layer_set_text(text, "Stop?");
	text_layer_set_font(text, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text, GTextAlignmentCenter);
	return text;
}

TextLayer *create_start_display(GRect bounds) {
	#if defined(PBL_RECT)
	bounds.origin.x -= ACTION_BAR_WIDTH;
	#endif
	bounds.origin.y += bounds.size.h * 1 / 3;	
	bounds.size.h /= 3;
	TextLayer *text = text_layer_create(bounds);
	text_layer_set_text(text, "Start?");
	text_layer_set_font(text, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text, GTextAlignmentCenter);
	return text;
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
	time_t cur_t = time(NULL);
	
	int difference = cur_t - beginning;
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

void start_timer() {
	if (persist_exists(BEGINNING_TIME)) stop_timer();
	persist_write_int(CUR_MODE, (int) cur_mode);
	time_t buffer;
	persist_write_int(BEGINNING_TIME, (int) time(&buffer));

	remove_workplay_win(true);
}

void stop_timer() {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Attempting to stop timer.");
	DictionaryIterator *out;
	AppMessageResult result = app_message_outbox_begin(&out);
	if (result == APP_MSG_OK) {
		int value = 1;
		dict_write_int(out, TIMER, &value, sizeof(int), true);
	
		result = app_message_outbox_send();
		if (result != APP_MSG_OK) {
			APP_LOG(APP_LOG_LEVEL_ERROR, "Error sending the outbox: %d", (int) result);
		}
	} else {
		APP_LOG(APP_LOG_LEVEL_ERROR, "Error preparing the outbox: %d", (int) result);
	}

}

void start_callback(ClickRecognizerRef recognizer, void *context) {
	start_timer();
}

void exit_callback(ClickRecognizerRef recognizer, void *context) {	
	remove_workplay_win(true);
}

void stop_callback(ClickRecognizerRef recognizer, void *context) {
	stop_timer();
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
		set_elapsed_time();
		start_display = 0;
		time_display = create_time_display(bounds);
		stop_display = create_stop_display(bounds);	
		layer_add_child(window_layer, text_layer_get_layer(time_display));
		layer_add_child(window_layer, text_layer_get_layer(stop_display));
		
		text_layer_enable_screen_text_flow_and_paging(time_display, 2);
		text_layer_enable_screen_text_flow_and_paging(stop_display, 2);
		
		tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
	} else {
		time_display = 0;
		stop_display = 0;
		start_display = create_start_display(bounds);
		layer_add_child(window_layer, text_layer_get_layer(start_display));
		
		text_layer_enable_screen_text_flow_and_paging(start_display, 2);
	}

	create_actionbar();

	app_message_open(64,64);
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
