#ifndef TIMER_H
#define TIMER_H

#include <pebble.h>
#include "app_message.h"

#define BEGINNING_TIME 0
#define CUR_MODE 1

#define NUM_LOCAL 100
#define MAX_LOCAL 8

int store_local(int mode, int beginning, int end, char *tag);
int store_js(int mode, int beginning, int end, char *tag);

void start_timer(int mode, int beginning);
void stop_timer(int mode, int beginning, int end, char *tag);

#endif // TIMER_H
