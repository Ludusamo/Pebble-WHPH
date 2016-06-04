#include "timer.h"

int store_local(int mode, int beginning, int end, char *tag) {
	int num_local = persist_read_int(NUM_LOCAL);
	if (num_local + 1 > 8) {
		APP_LOG(APP_LOG_LEVEL_ERROR, "No more local space");
		return 0;
	}
	int start_position = NUM_LOCAL + num_local * 4;
	persist_write_int(start_position, mode);
	persist_write_int(start_position + 1, beginning);
	persist_write_int(start_position + 2, end);
	persist_write_string(start_position + 3, tag);
		
	return 1;
}

int store_js(int mode, int beginning, int end, char *tag) {
	begin_app_message();	
	register_uint8(TYPE, mode);
	register_uint32(TIME_START, beginning);
	register_uint32(TIME_STOP, end);
	register_cstring(TAG, tag);
	if (!send_message()) 
		if (!store_local(mode, beginning, end, tag)) return 0;
	return 1;
}

void start_timer(int mode, int beginning) {
	if (persist_exists(CUR_MODE)) stop_timer(mode, beginning, time(NULL), "PLACEHOLDER");
	persist_write_int(CUR_MODE, mode);
	persist_write_int(BEGINNING_TIME, beginning);
}

void stop_timer(int mode, int beginning, int end, char *tag) {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Attempting to stop timer.%lu", (uint32_t) time(NULL));
	store_js(mode, beginning, end, tag);
	persist_delete(CUR_MODE);
	
	switch (mode) {
	case WORK_CASE:
		persist_write_int(WORK_TIME, persist_read_int(WORK_TIME) + (end - beginning));
		break;
	case PLAY_CASE:
		persist_write_int(PLAY_TIME, persist_read_int(PLAY_TIME) + (end - beginning));
		break;
	}
}
