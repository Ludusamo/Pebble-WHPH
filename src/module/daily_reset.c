#include "daily_reset.h"

uint32_t get_start_of_today() {
	time_t start_of_today = time_start_of_today();
	struct tm *local_start = localtime(&start_of_today);
	time_t time_local_start = mktime(local_start);
	return (uint32_t) time_local_start;
}

void store_day() {
	persist_write_int(CUR_DAY_MEM_LOC, get_start_of_today());
}

int is_same_day() {
	uint32_t cur_day = persist_read_int(CUR_DAY_MEM_LOC);
	return cur_day == get_start_of_today();
}

void daily_reset() {
	persist_delete(WORK_TIME_MEM_LOC);
	persist_delete(PLAY_TIME_MEM_LOC);
	store_day();
}
