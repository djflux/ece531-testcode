#include <string.h>
#include <stdio.h>

#define BAD_KEY	-1

typedef struct kv_char_int_struct_t {
	char *key;
	int   value;
} kv_char_int_struct_t;

#define PATH_STATUS             1
#define PATH_HEATER_STATUS      2
#define PATH_CURRENT_TEMP       3
#define PATH_SCHEDULE           4

#define PATH_STRING_STATUS		"/status"
#define PATH_STRING_CURRENT_TEMP	"/currenttemp"
#define PATH_STRING_HEATER_STATUS	"/heaterstatus"
#define PATH_STRING_SCHEDULE		"/schedule"

int search_kv(kv_char_int_struct_t *store, char *key) {
	int i = 0;

	while (store[i].key != NULL) {
		if (strcmp(store[i].key, key) == 0) {
			return store[i].value;
		}
		++i;
	}

	return BAD_KEY;
}

int main(void) {

	static kv_char_int_struct_t http_path_lookup[] = {
		{ PATH_STRING_STATUS, PATH_STATUS },
		{ PATH_STRING_HEATER_STATUS, PATH_HEATER_STATUS },
		{ PATH_STRING_CURRENT_TEMP, PATH_CURRENT_TEMP },
		{ PATH_STRING_SCHEDULE, PATH_SCHEDULE }
	};

	int path_string = search_kv(http_path_lookup, PATH_STRING_STATUS);

	printf("path_string: %d\n", path_string);
	
	switch(path_string) {
		case PATH_STATUS:
			printf("path: %s\n", PATH_STRING_STATUS);
			break;
		default:
			printf("HTTP 404\n");
	}

	return 0;
}
