#include "wakeup.h"

void reset_handler(WakeupId id, int32_t cookie) {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Reset Wakeup");
	persist_delete(WAKEUP_KEY);
	persist_write_int(0, (int) time(NULL));
	begin_app_message();
	register_uint8(TYPE, 3);
	send_message();
	persist_delete(30);
	persist_delete(31);
	register_reset_wakeup();
}

void register_reset_wakeup() {
	if (!persist_exists(WAKEUP_KEY)) {
		const time_t midnight = time_start_of_today() + (24 * SECONDS_PER_HOUR);
		char time[20];
		strftime(time, 20, "%D %01H:%01M:%01S", localtime(&midnight));
		APP_LOG(APP_LOG_LEVEL_DEBUG, time);
		
		const int reset_cookie = 0;
		WakeupId id = wakeup_schedule(midnight, reset_cookie, true);
		if (id >= 0) {
			persist_write_int(WAKEUP_KEY, id);
		}
	}
	wakeup_service_subscribe(reset_handler);
}
