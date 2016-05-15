#include <pebble.h>

#include "windows/select_win.h"
#include "windows/title_win.h"

Select_Win *select_win;
Title_Win *title_win;

void init() {
	/*select_win = select_win_create();
	push_select_win(select_win, true);*/
	title_win = title_win_create();
	push_title_win(title_win, true);
}

void deinit() {
	/*remove_select_win(select_win, true);
	select_win_destroy(select_win);*/
	remove_title_win(title_win, true);
	title_win_destroy(title_win);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
