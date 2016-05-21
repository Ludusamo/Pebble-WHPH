#include "workplay_win.h"

TextLayer *create_time_display(GRect bounds) {
	#if defined(PBL_RECT)
	bounds.origin.x -= ACTION_BAR_WIDTH;
	#endif
	bounds.origin.y += bounds.size.h / 20;
	bounds.size.h /= 3;		
	TextLayer *text = text_layer_create(bounds);
	text_layer_set_text(text, "00:00");
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

void start_timer() {

}

void stop_timer() {

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
		win->window = window_create();
		
		Layer *window_layer = window_get_root_layer(win->window);
		GRect bounds = layer_get_bounds(window_layer);

		if (in_mode) {
			win->time_display = create_time_display(bounds);
			win->stop_display = create_stop_display(bounds);	
			layer_add_child(window_layer, text_layer_get_layer(win->time_display));
			layer_add_child(window_layer, text_layer_get_layer(win->stop_display));
			
			text_layer_enable_screen_text_flow_and_paging(win->time_display, 2);
			text_layer_enable_screen_text_flow_and_paging(win->stop_display, 2);
		} else {
			win->start_display = create_start_display(bounds);
			layer_add_child(window_layer, text_layer_get_layer(win->start_display));
			
			text_layer_enable_screen_text_flow_and_paging(win->start_display, 2);
		}

		create_actionbar(win);
		return win;
	}
	return NULL;
}

void workplay_win_destroy(WorkPlay_Win *win) {
	if (win) {
		text_layer_destroy(win->time_display);
		text_layer_destroy(win->stop_display);
		text_layer_destroy(win->start_display);
		action_bar_layer_destroy(win->actionbar);
		gbitmap_destroy(win->tick_bitmap);
		gbitmap_destroy(win->cross_bitmap);
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
