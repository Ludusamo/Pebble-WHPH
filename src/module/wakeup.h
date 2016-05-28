#ifndef WAKEUP_H
#define WAKEUP_H

#include <pebble.h>
#include "app_message.h"

#define WAKEUP_KEY 20

void reset_handler(WakeupId id, int32_t cookie);

void register_reset_wakeup();

#endif // WAKEUP_H
