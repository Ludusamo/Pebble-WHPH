#include "app_message.h"

void register_uint8(AppKey type, uint8_t i) {
	dict_write_uint8(dict, type, i);
}

void register_uint16(AppKey type, uint16_t i) {
	dict_write_uint16(dict, type, i);
}

void register_uint32(AppKey type, uint32_t i) {
	dict_write_uint32(dict, type, i);
}

void register_cstring(AppKey type, char *s) {
	dict_write_cstring(dict, type, s);
}

void init_app_message() {
	app_message_open(INBOX_SIZE, OUTBOX_SIZE);
}

void begin_app_message() {
	AppMessageResult result = app_message_outbox_begin(&dict);
	if (result != APP_MSG_OK) APP_LOG(APP_LOG_LEVEL_ERROR, "Error preparing the outbox: %d", (int) result);
}

int send_message() {
	AppMessageResult result = app_message_outbox_send();
	if (result != APP_MSG_OK) {
		APP_LOG(APP_LOG_LEVEL_ERROR, "Error sending the outbox: %d", (int) result);
		return 0;
	}
	return 1;
}
