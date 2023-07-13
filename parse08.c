// gcc json-parse08.c -ljson-c -o json-parse08

#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

int main(void)
{
	struct json_object_iterator it, it2;
	struct json_object_iterator itEnd, itEnd2;

	char *schedule = "/etc/thermostatd/schedule.json";

	json_object *root = json_object_from_file(schedule);
	// it = json_object_iter_init_default();
	it = json_object_iter_begin(root);
	itEnd = json_object_iter_end(root);

	const char* key;
	json_object* val;

	while (!json_object_iter_equal(&it, &itEnd))
	{
		key = json_object_iter_peek_name(&it);
		val = json_object_iter_peek_value(&it);
		printf("%s  -> %s\n", key, json_object_get_string(val));
		if (strcmp(key, "setpoints") == 0) {
			printf("found setpoints.\n");
			break;
		}
		json_object_iter_next(&it);
	}

/*
	it2 = json_object_iter_begin(val);
	itEnd2 = json_object_iter_end(val);

	printf("second iterators set\n");

	while (!json_object_iter_equal(&it, &itEnd))
	{
		key = json_object_iter_peek_name(&it);
		val = json_object_iter_peek_value(&it);
		printf("%s  -> %s\n", key, json_object_get_string(val));
		json_object_iter_next(&it);
	}


	json_object_put(val); */
	json_object_put(root);
	return 0;
}
