#include <pebble.h>

#include "windows/select_win.h"

static Select_Win *select_win;

void init() {
	select_win = select_win_create();
	push_select_win(select_win, true);
}

void deinit() {
	remove_select_win(select_win, true);
	select_win_destroy(select_win);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
