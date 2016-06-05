#include "timer.h"

int store_local(int mode, int beginning, int end, char *tag) {
	int num_local = persist_read_int(NUM_ENTRIES_MEM_LOC);
	if (num_local + 1 > 8) {
		APP_LOG(APP_LOG_LEVEL_ERROR, "No more local space");
		return 0;
	}
	int start_position = NUM_ENTRIES_MEM_LOC + num_local * 4;
	persist_write_int(start_position, mode);
	persist_write_int(start_position + 1, beginning);
	persist_write_int(start_position + 2, end);
	persist_write_string(start_position + 3, tag);
		
	return 1;
}

void start_timer(int mode, int beginning) {
	if (persist_exists(CUR_MODE_MEM_LOC)) stop_timer(persist_read_int(CUR_MODE_MEM_LOC), persist_read_int(BEGINNING_TIME_MEM_LOC), time(NULL), "PLACEHOLDER");
	persist_write_int(CUR_MODE_MEM_LOC, mode);
	persist_write_int(BEGINNING_TIME_MEM_LOC, beginning);
}

void stop_timer(int mode, int beginning, int end, char *tag) {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Attempting to stop timer.%lu", (uint32_t) time(NULL));
	persist_delete(CUR_MODE_MEM_LOC);
	
	switch (mode) {
	case WORK:
		persist_write_int(WORK_TIME_MEM_LOC, persist_read_int(WORK_TIME_MEM_LOC) + (end - beginning));
		break;
	case PLAY:
		persist_write_int(PLAY_TIME_MEM_LOC, persist_read_int(PLAY_TIME_MEM_LOC) + (end - beginning));
		break;
	}
}
