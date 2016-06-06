#ifndef TIMER_H
#define TIMER_H

#include <pebble.h>
#include "app_message.h"
#include "shared_val.h"

void start_timer(int mode, int beginning);
void stop_timer(int mode, int beginning, int end, char *tag);

#endif // TIMER_H
