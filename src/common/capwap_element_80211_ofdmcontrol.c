#include "capwap.h"
#include "capwap_element.h"

/********************************************************************

 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|    Radio ID   |    Reserved   | Current Chan  |  Band Support |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                         TI Threshold                          |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

Type:   1033 for IEEE 802.11 OFDM Control

Length:   8

********************************************************************/

/* */
static void capwap_80211_ofdmcontrol_element_create(void* data, capwap_message_elements_handle handle, struct capwap_write_message_elements_ops* func) {
	struct capwap_80211_ofdmcontrol_element* element = (struct capwap_80211_ofdmcontrol_element*)data;

	ASSERT(data != NULL);

	/* */
	func->write_u8(handle, element->radioid);
	func->write_u8(handle, 0);
	func->write_u8(handle, element->currentchannel);
	func->write_u8(handle, element->bandsupport);
	func->write_u32(handle, element->tithreshold);
}

/* */
static void* capwap_80211_ofdmcontrol_element_parsing(capwap_message_elements_handle handle, struct capwap_read_message_elements_ops* func) {
	struct capwap_80211_ofdmcontrol_element* data;

	ASSERT(handle != NULL);
	ASSERT(func != NULL);

	if (func->read_ready(handle) != 8) {
		capwap_logging_debug("Invalid IEEE 802.11 OFDM Control element");
		return NULL;
	}

	/* */
	data = (struct capwap_80211_ofdmcontrol_element*)capwap_alloc(sizeof(struct capwap_80211_ofdmcontrol_element));
	memset(data, 0, sizeof(struct capwap_80211_ofdmcontrol_element));

	/* Retrieve data */
	func->read_u8(handle, &data->radioid);
	func->read_u8(handle, NULL);
	func->read_u8(handle, &data->currentchannel);
	func->read_u8(handle, &data->bandsupport);
	func->read_u32(handle, &data->tithreshold);

	return data;
}

/* */
static void* capwap_80211_ofdmcontrol_element_clone(void* data) {
	ASSERT(data != NULL);

	return capwap_clone(data, sizeof(struct capwap_80211_ofdmcontrol_element));
}

/* */
static void capwap_80211_ofdmcontrol_element_free(void* data) {
	ASSERT(data != NULL);
	
	capwap_free(data);
}

/* */
struct capwap_message_elements_ops capwap_element_80211_ofdmcontrol_ops = {
	.create_message_element = capwap_80211_ofdmcontrol_element_create,
	.parsing_message_element = capwap_80211_ofdmcontrol_element_parsing,
	.clone_message_element = capwap_80211_ofdmcontrol_element_clone,
	.free_message_element = capwap_80211_ofdmcontrol_element_free
};
