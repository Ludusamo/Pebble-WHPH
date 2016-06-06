#ifndef DAILYRESET_H
#define DAILYRESET_H

#include <pebble.h>
#include "shared_val.h"
#include "storage.h"

uint32_t get_start_of_today();
void store_day();
int is_same_day();
void daily_reset();

#endif // DAILYRESET_H
