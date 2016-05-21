#include <pebble.h>
#include "windows/title_win.h"
#include "windows/workplay_win.h"

Title_Win *title_win;
WorkPlay_Win *win;

void init() {
	/*title_win = title_win_create();
	push_title_win(title_win, true);*/
	win = workplay_win_create(PLAY);
	push_workplay_win(win, true);
}

void deinit() {
	/*remove_title_win(title_win, true);
	title_win_destroy(title_win);*/
	remove_workplay_win(win, true);
	workplay_win_destroy(win);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
