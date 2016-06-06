#include <pebble.h>
#include "windows/title_win.h"
#include "module/app_message.h"
#include "module/daily_reset.h"

void init() {
	title_win_create();
	push_title_win(true);
	
	init_app_message();
	if (!is_same_day()) {
		daily_reset();
	}
}

void deinit() {
	remove_title_win(true);
	title_win_destroy();
}

int main() {
	init();
	app_event_loop();
	deinit();
	return 0;
}
