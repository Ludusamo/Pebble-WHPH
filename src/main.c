#include <pebble.h>
#include "windows/title_win.h"
#include "module/app_message.h"
#include "module/wakeup.h"

void init() {
	title_win_create();
	push_title_win(true);
	
	init_app_message();
	if (launch_reason() == APP_LAUNCH_WAKEUP) reset_handler(0, 0);
	else register_reset_wakeup();
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
