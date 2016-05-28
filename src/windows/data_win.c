#include "data_win.h"

void exit_data_win(ClickRecognizerRef recognizer, void *context) {
	remove_data_win(true);
	data_win_destroy();
}

void data_click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_BACK, (ClickHandler) exit_data_win);
}

uint16_t get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *context) {
	return 2;
}

void draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *context) {
	if (cell_index->row == 0) {
		int time = work_time;
		int hours = time / 3600;
		time %= 3600;
		int minutes = time / 60;
		time %= 60;
		int seconds = time;

		char buf[20];
		snprintf(buf, 20, "Work %02d:%02d:%02d", hours, minutes, seconds);

		menu_cell_basic_draw(ctx, cell_layer, buf, NULL, NULL);
	} else {
		int time = play_time;
		int hours = time / 3600;
		time %= 3600;
		int minutes = time / 60;
		time %= 60;
		int seconds = time;

		char buf[20];
		snprintf(buf, 20, "Play %02d:%02d:%02d", hours, minutes, seconds);
		menu_cell_basic_draw(ctx, cell_layer, buf, NULL, NULL);
	}
}

int16_t get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
  return PBL_IF_ROUND_ELSE(
    menu_layer_is_index_selected(menu_layer, cell_index) ? 
      MENU_CELL_ROUND_FOCUSED_SHORT_CELL_HEIGHT : MENU_CELL_ROUND_UNFOCUSED_TALL_CELL_HEIGHT,
    44);
}

void select_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {

}

void canvas_update_proc(Layer *layer, GContext *ctx) {
	int32_t total_time = work_time + play_time;
	int32_t percent_work = (work_time * 100) / total_time;
	int work_end_angle = percent_work * 360 / 100;
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Percent Work: %d", (int)percent_work);

	graphics_context_set_stroke_color(ctx, GColorBlack);
	graphics_context_set_fill_color(ctx, GColorBlack);

	GRect rect = layer_get_bounds(layer);
	
	graphics_fill_radial(ctx, rect, GOvalScaleModeFitCircle, RADIAL_R, DEG_TO_TRIGANGLE(0), DEG_TO_TRIGANGLE(work_end_angle));
	graphics_draw_arc(ctx, rect, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(work_end_angle), DEG_TO_TRIGANGLE(360));
	graphics_draw_arc(ctx, calc_rect(layer, 1), GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(work_end_angle), DEG_TO_TRIGANGLE(360));

	graphics_context_set_text_color(ctx, GColorBlack);
	int top_inset = (rect.size.h * 2 / 5);
	int left_inset = INDIC_SIZE;
	graphics_draw_text(ctx, "Work", fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD), grect_inset(rect, GEdgeInsets(top_inset, 0, 0, left_inset)), GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, NULL);
	graphics_draw_text(ctx, "Play", fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD), grect_inset(rect, GEdgeInsets(top_inset + LEGEND_PAD, 0, 0, left_inset)), GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, NULL);

	GRect work_rect = grect_inset(rect, GEdgeInsets(top_inset, 0, 0, rect.size.w / 3));
	work_rect.size.w = INDIC_SIZE;
	work_rect.size.h = INDIC_SIZE;
	graphics_fill_rect(ctx, work_rect, 0, GCornerNone);

	GRect play_rect = grect_inset(rect, GEdgeInsets(top_inset + LEGEND_PAD, 0, 0, rect.size.w / 3));
	play_rect.size.w = INDIC_SIZE;
	play_rect.size.h = INDIC_SIZE;

	graphics_draw_rect(ctx, play_rect);
}

GRect calc_rect(Layer *layer, uint8_t arc_id) {
  return grect_inset(layer_get_bounds(layer), GEdgeInsets(arc_id * RADIAL_R));
}

void req_data() {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Requesting Data");
	begin_app_message();
	register_uint8(TYPE, 2);
	send_message();
}

void receive_data_callback(DictionaryIterator *iter, void *context) {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Received Data");
	Tuple *work_tupe = dict_find(iter, 2);
	if (work_tupe) {
		work_time = work_tupe->value->int32;
	}

	Tuple *play_tupe = dict_find(iter, 3);
	if (play_tupe) {
		play_time = play_tupe->value->int32;
	}
	
	if (play_tupe && work_tupe) {
		Layer *window_layer = window_get_root_layer(data_window);
		GRect bounds = layer_get_bounds(window_layer);

		canvas = layer_create(bounds);
		layer_set_update_proc(canvas, canvas_update_proc);
		layer_add_child(window_layer, canvas);
	}
	window_set_click_config_provider(data_window, data_click_config_provider);
}

void data_win_create() {
	data_window = window_create();
	
	app_message_register_inbox_received(receive_data_callback);
	req_data();	
}

void data_win_destroy() {
	menu_layer_destroy(data_list);
	window_destroy(data_window);
}

void push_data_win(bool animated) {
	window_stack_push(data_window, animated);
}

void remove_data_win(bool animated) {
	window_stack_remove(data_window, animated);
}
