#include <pebble.h>
#include "windows/title_win.h"

Title_Win *title_win;

void init() {
	title_win = title_win_create();
	push_title_win(title_win, true);
}

void deinit() {
	remove_title_win(title_win, true);
	title_win_destroy(title_win);
}

int main() {
	init();
	app_event_loop();
	deinit();
	return 0;
}
