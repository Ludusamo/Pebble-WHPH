#ifndef STORAGE_H
#define STORAGE_H

#include <pebble.h>
#include "shared_val.h"

typedef struct {
	int type;
	const char *tag;
	uint32_t beginning, end;
} Entry;

Entry *create_entry(int type, const char *tag, uint32_t beginning, uint32_t end);
int store_entry(Entry *entry);
Entry *retrieve_top_entry();

#endif // STORAGE_H
