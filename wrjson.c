#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include "tc_error.h"
#include "tc_state.h"
#include "tc_main.h"
#include "util.h"

tc_error_t get_local_tc_heater_state(char *filename, tc_heater_state_t* heater_state) {
	tc_error_t heater_state_return = tc_read_state(filename, heater_state);
	printf("Heater state: %d\n", *heater_state);
	printf("tc_error_t: %d\n", heater_state_return);
	return heater_state_return;
}

tc_error_t get_local_tc_temperature(char *filename, float *temperature) {
	tc_error_t read_temperature_return = tc_read_temperature(filename, temperature);
	printf("Temperature: %.2f\n", *temperature);
	printf("tc_error_t: %d\n", read_temperature_return);
	return read_temperature_return;
}

int _write_local_json_file(char *filename, char *content) {
	FILE* fp = fopen(filename, "w");

	if (fp == NULL) {
		syslog(LOG_ERR, "Something is really wrong. Couldn't open a new file for writing. Check local system status. Exiting");
		exit(ERR_FILE_OPEN);
	} else {
		fprintf(fp, "%s", content);
		DEBUG("Wrote content to %s", filename);
		fclose(fp);
		return 0;
	}
}

json_object *_build_local_status(void) {
	json_object *root = json_object_new_object();
	if (!root)
		return json_tokener_parse(JSON_ERR_NO_NEW_OBJ);

	float *temperature = malloc(sizeof(float*) * 16);
	tc_heater_state_t* heater_state = malloc(sizeof(tc_heater_state_t*));

        tc_error_t ret_h = get_local_tc_heater_state(STATE_FILENAME, heater_state);
        tc_error_t ret_t = get_local_tc_temperature(TEMPERATURE_FILENAME, temperature);

	if (ret_t != OK) *temperature = (float) DEFAULT_TEMPERATURE;

	json_object *status_array = json_object_new_array();

	json_object_object_add(root, "thermostat_status", status_array);

	json_object *status = json_object_new_object();
	json_object_object_add(status, "_id",                  json_object_new_string("dummy"));
	json_object_object_add(status, JSON_CURRENT_SETPOINT,  json_object_new_string("setPoint1"));
        json_object_object_add(status, JSON_CURRENT_TEMP,      json_object_new_double(*temperature));
	char *new_state = (heater_state == ON) ? "ON" : "OFF";
        json_object_object_add(status, JSON_HEATER_STATUS,     json_object_new_string(new_state));
	json_object_object_add(status, JSON_NEW_SCHEDULE_BOOL, json_object_new_string("false"));
	json_object_array_add(status_array, status);

	printf("new status JSON: \n%s\n\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));

	return status_array;
}


int main(void) {
	float *temperature = malloc(sizeof(float*) * 16);
	tc_heater_state_t* heater_state = malloc(sizeof(tc_heater_state_t*));

	json_object *new_status = _build_local_status();
/*
	printf("temp: %.2f\n", *temperature);
	printf("return: %d\n", ret_t);

	printf("state: %2d\n", *heater_state);
        printf("heater return: %d\n", ret_h);
*/
	return 0;
}
