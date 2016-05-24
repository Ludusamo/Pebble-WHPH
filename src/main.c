#include <pebble.h>
#include "windows/title_win.h"

void init() {
	title_win_create();
	push_title_win(true);
	
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
