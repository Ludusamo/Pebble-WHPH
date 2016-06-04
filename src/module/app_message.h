#ifndef APPMESSAGE_H
#define APPMESSAGE_H

#include <pebble.h>

#define INBOX_SIZE 64
#define OUTBOX_SIZE 256

typedef enum {
	TYPE,
	TAG,
	TIME_START,
	TIME_STOP
} AppKey;

DictionaryIterator *dict;

void init_app_message();
void begin_app_message();

void register_uint8(AppKey type, uint8_t i);
void register_uint16(AppKey type, uint16_t i);
void register_uint32(AppKey type, uint32_t i);
void register_cstring(AppKey type, char *s);

int send_message();

#endif // APPMESSAGE_H
