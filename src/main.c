#include <pebble.h>
#include "windows/title_win.h"

#define OUTBOX_SIZE 256
#define INBOX_SIZE 64

void init() {
	title_win_create();
	push_title_win(true);
	
	app_message_open(INBOX_SIZE, OUTBOX_SIZE);
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
