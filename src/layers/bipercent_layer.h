#ifndef BIPERCENTLAYER_H
#define BIPERCENTLAYER_H

#include <pebble.h>

#define RADIAL_R 20
#define INDIC_SIZE 14
#define LEGEND_PAD 20

typedef struct {
	int percent;
	const char *key1, *key2;
} BipercentLayerData;

typedef Layer BipercentLayer;

BipercentLayer *bipercent_layer_create(GRect frame);
void bipercent_layer_destroy(BipercentLayer *layer);

void bipercent_layer_set_percent(BipercentLayer *layer, int percent);
void bipercent_layer_set_keys(BipercentLayer *layer, const char *key1, const char *key2);

void bipercent_draw_circle(Layer *layer, GContext *ctx);
void bipercent_draw_legend(Layer *layer, GContext *ctx);
void bipercent_update_proc(Layer *layer, GContext *ctx);
GRect calc_rect(Layer *layer, uint8_t arc_id);

#endif // BIPERCENTLAYER_H
