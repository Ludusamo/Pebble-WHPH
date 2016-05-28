#include "bipercent_layer.h"

BipercentLayer *bipercent_layer_create(GRect frame) {
	BipercentLayer *layer = layer_create_with_data(frame, sizeof(BipercentLayerData));
	layer_set_update_proc(layer, bipercent_update_proc);
	layer_mark_dirty(layer);

	BipercentLayerData *data = (BipercentLayerData*) layer_get_data(layer);
	data->percent = 0;
	return layer;
}

void bipercent_layer_destroy(BipercentLayer *layer) {
	if (layer) {
		layer_destroy(layer);
	}
}

void bipercent_layer_set_percent(BipercentLayer *layer, int percent) {
	BipercentLayerData *data = (BipercentLayerData*) layer_get_data(layer);
	data->percent = percent;
}

void bipercent_layer_set_keys(BipercentLayer *layer, const char *key1, const char *key2) {
	BipercentLayerData *data = (BipercentLayerData*) layer_get_data(layer);	
	data->key1 = key1;
	data->key2 = key2;
}

void bipercent_draw_circle(Layer *layer, GContext *ctx) {
	BipercentLayerData *data = (BipercentLayerData*) layer_get_data(layer);
	int end_angle = data->percent * 360 / 100;

	GRect rect = layer_get_bounds(layer);
	
	graphics_fill_radial(ctx, rect, GOvalScaleModeFitCircle, RADIAL_R, DEG_TO_TRIGANGLE(0), DEG_TO_TRIGANGLE(end_angle));
	graphics_draw_arc(ctx, rect, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(end_angle), DEG_TO_TRIGANGLE(360));
	graphics_draw_arc(ctx, grect_inset(layer_get_bounds(layer), GEdgeInsets(RADIAL_R))
, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(end_angle), DEG_TO_TRIGANGLE(360));
}

void bipercent_draw_legend(Layer *layer, GContext *ctx) {
	BipercentLayerData *data = (BipercentLayerData*) layer_get_data(layer);
	GRect rect = layer_get_bounds(layer);
	
	graphics_context_set_text_color(ctx, GColorBlack);
	int top_inset = (rect.size.h * 2 / 5);
	int left_inset = INDIC_SIZE;
	graphics_draw_text(ctx, data->key1, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD), grect_inset(rect, GEdgeInsets(top_inset, 0, 0, left_inset)), GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, NULL);
	graphics_draw_text(ctx, data->key2, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD), grect_inset(rect, GEdgeInsets(top_inset + LEGEND_PAD, 0, 0, left_inset)), GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, NULL);

	GRect rect1 = grect_inset(rect, GEdgeInsets(top_inset, 0, 0, rect.size.w / 3));
	rect1.size.w = INDIC_SIZE;
	rect1.size.h = INDIC_SIZE;
	graphics_fill_rect(ctx, rect1, 0, GCornerNone);

	GRect rect2 = grect_inset(rect, GEdgeInsets(top_inset + LEGEND_PAD, 0, 0, rect.size.w / 3));
	rect2.size.w = INDIC_SIZE;
	rect2.size.h = INDIC_SIZE;

	graphics_draw_rect(ctx, rect2);
}

void bipercent_update_proc(Layer *layer, GContext *ctx) {
	bipercent_draw_circle(layer, ctx);
	bipercent_draw_legend(layer, ctx);
}
