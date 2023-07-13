#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
#include <json-c/json_visit.h>

#define CURRENT "true"
#define JSON_OBJECT_STR(obj, key) json_object_get_string(json_object_object_get(obj, key))

static int doit(json_object *obj, int flags, json_object *parent, const char *key,
		size_t *index, void *data)
{
	if (!parent || flags==JSON_C_VISIT_SECOND || 
			json_object_get_type(obj) == json_type_object || 
			json_object_get_type(obj) == json_type_array)
		return JSON_C_VISIT_RETURN_CONTINUE;

	if (strcmp(json_object_get_string(obj), CURRENT) == 0)
	{
		printf("Found: %s temp: %s %s\n", JSON_OBJECT_STR(parent, "name"), JSON_OBJECT_STR(parent, "temperature"), json_object_to_json_string(obj));
		return JSON_C_VISIT_RETURN_STOP;
	}
	return JSON_C_VISIT_RETURN_CONTINUE;
}

	int 
main(void)
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

	//json_object *root = json_object_from_file("/etc/thermostatd/schedule.json");
	printf("Search for %s\n\n", CURRENT);
	json_c_visit(val, 0, doit, NULL);

	json_object_put(root);
	return 0;
}
