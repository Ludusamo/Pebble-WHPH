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

void create_actionbar(WorkPlay_Win *win) {
	win->actionbar = action_bar_layer_create();
	action_bar_layer_set_click_config_provider(win->actionbar, action_bar_provider);
	
	win->tick_bitmap = gbitmap_create_with_resource(RESOURCE_ID_TICK);
	win->cross_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CROSS);

	action_bar_layer_set_icon(win->actionbar, BUTTON_ID_UP, win->tick_bitmap);
	action_bar_layer_set_icon(win->actionbar, BUTTON_ID_DOWN, win->cross_bitmap);
	action_bar_layer_add_to_window(win->actionbar, win->window);
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
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
	set_elapsed_time();
}

void start_timer() {
	if (persist_exists(BEGINNING_TIME)) stop_timer();
	persist_write_int(CUR_MODE, (int) cur_mode);
	time_t buffer;
	persist_write_int(BEGINNING_TIME, (int) time(&buffer));

	window_stack_pop(true);
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
	window_stack_pop(true);
}

void stop_callback(ClickRecognizerRef recognizer, void *context) {
	stop_timer();
}

void action_bar_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_UP, (ClickHandler) (in_mode) ? stop_callback : start_callback);
	window_single_click_subscribe(BUTTON_ID_DOWN, (ClickHandler) exit_callback);
}

WorkPlay_Win *workplay_win_create(MODE mode) {
	WorkPlay_Win *win = (WorkPlay_Win*) malloc(sizeof(WorkPlay_Win));
	if (win) {
		if (persist_exists(CUR_MODE)) in_mode = persist_read_int(CUR_MODE) == mode;
		else in_mode = 0;
		cur_mode = mode;
		win->window = window_create();
		
		Layer *window_layer = window_get_root_layer(win->window);
		GRect bounds = layer_get_bounds(window_layer);

		if (in_mode) {
			beginning = persist_read_int(BEGINNING_TIME);	
			set_elapsed_time();
			win->start_display = 0;
			win->time_display = create_time_display(bounds);
			win->stop_display = create_stop_display(bounds);	
			layer_add_child(window_layer, text_layer_get_layer(win->time_display));
			layer_add_child(window_layer, text_layer_get_layer(win->stop_display));
			
			text_layer_enable_screen_text_flow_and_paging(win->time_display, 2);
			text_layer_enable_screen_text_flow_and_paging(win->stop_display, 2);
			
			tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
		} else {
			win->time_display = 0;
			win->stop_display = 0;
			win->start_display = create_start_display(bounds);
			layer_add_child(window_layer, text_layer_get_layer(win->start_display));
			
			text_layer_enable_screen_text_flow_and_paging(win->start_display, 2);
		}

		create_actionbar(win);

		app_message_open(64,64);
		return win;
	}
	return NULL;
}

void workplay_win_destroy(WorkPlay_Win *win) {
	if (win) {	
		if (win->time_display) text_layer_destroy(win->time_display);
		if (win->stop_display) text_layer_destroy(win->stop_display);
		if (win->start_display) text_layer_destroy(win->start_display);
		action_bar_layer_destroy(win->actionbar);
		gbitmap_destroy(win->tick_bitmap);
		gbitmap_destroy(win->cross_bitmap);

		window_destroy(win->window);
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
