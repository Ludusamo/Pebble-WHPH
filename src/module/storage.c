#include "storage.h"

Entry *create_entry(int type, const char *tag, uint32_t beginning, uint32_t end) {
	Entry *entry = malloc(sizeof(Entry));
	entry->type = type;
	entry->tag = tag;
	entry->beginning = beginning;
	entry->end = end;
	return entry;
}

int store_entry(Entry *entry) {
	int num_entries = persist_read_int(NUM_ENTRIES_MEM_LOC);
	if (num_entries == MAX_ENTRIES) return 0;
	int mem_loc = NUM_ENTRIES_MEM_LOC + (++num_entries);
	persist_write_data(mem_loc, entry, sizeof(Entry));
	persist_write_int(NUM_ENTRIES_MEM_LOC, num_entries);
	return 1;
}

Entry *retrieve_top_entry() {
	int num_entries = persist_read_int(NUM_ENTRIES_MEM_LOC);
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Attempting to retrieve top entry: %d", num_entries);
	if (num_entries == 0) return NULL;
	Entry *entry = malloc(sizeof(Entry));
	int mem_loc = NUM_ENTRIES_MEM_LOC + num_entries;
	persist_read_data(mem_loc, entry, sizeof(Entry));
	persist_delete(mem_loc);
	persist_write_int(NUM_ENTRIES_MEM_LOC, num_entries - 1);
	return entry;
}
