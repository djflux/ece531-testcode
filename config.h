/*
 * config.h
 *
 * Configuration definitions and functions
 */
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdio.h>
#include <json-c/json.h>

/*
 * Default program configurations. These can be overriden in the thermostatd
 * configuration file.
 */
#define CONFIG_FILE		"/etc/thermostatd/thermostatd.json"
#define SCHEDULE_FILE		"/etc/thermostatd/schedule.json"
#define SCHEDULE_FILE_EXAMPLE	"/etc/thermostatd/schedule-example.json"
#define STATUS_FILE             "/var/log/thermostatd/status.json"
#define LOG_FILE		"/var/log/thermostatd/thermostatd.log"
#define API_ENDPOINT_URL        "http://localhost:8989/"

// How long does the daemon wait between temperature check cycles?
//
#define THERMOSTAT_SLEEP_DELAY  10

/* 
 * thermocouple simulation files 
 */
#include "tc_error.h"
#include "tc_main.h"
#include "tc_state.h"

// Used to search for the currently active setpoint
//
#define CURRENT_SETPOINT_TRUE   "true"

// Function macro to to get value from key and turn it into a string.
//
#define JSON_OBJECT_STR(obj, key) json_object_get_string(json_object_object_get(obj, key))


/*
 * JSON node strings for configuration files
 */
#define JSON_NODE_HTTP_BIND_ADDRESS	"httpBindAddress"
#define JSON_NODE_HTTP_BIND_PORT	"httpBindPort"
#define JSON_NODE_SCHEDULE_CONFIG	"scheduleConfigiFile"
#define JSON_NODE_THERMOSTATD_LOG_FILE	"logFile"
#define JSON_NODE_TEMPERATURE_FILE	"temperatureFile"
#define JSON_NODE_HEATER_STATUS_FILE	"heaterStatusFile"
#define JSON_NODE_API_ENDPOINT_URL      "apiEndpointURL"
#define JSON_NODE_LOCAL_STATUS_FILE	"localStatusFile"

/*
 * JSON formatted error messages
 */
#define JSON_ERR_F_NOOPEN       "{\"err\": \"Could not open specified file.\"}"
#define JSON_ERR_NO_NEW_OBJ     "{\"err\": \"Could not create new JSON object.\"}"

/*
 * Curl errors
 */
#define ERR_CURL_COULDNT_CONNECT	"ERR_CURL_COULDNT_CONNECT"
#define ERR_CURL_WTF			"ERR_CURL_WTF"


/*
 * Define structure to hold all the program default options and set based on
 * command line arguments.
 */
typedef struct thermostatd_options {
        char *config_file;
        char *http_bind_address;
        int http_bind_port;
        char *schedule_config_file;
        char *log_file;
        char *temperature_file;
        char *heater_status_file;
	char *local_status_file;
        char *api_endpoint_url;
        FILE *file_descriptor_current_temperature;
        FILE *file_descriptor_heater_status;
	json_object *json_current_schedule;
	json_object *json_current_status;
	char *current_setpoint;
        float current_setpoint_temperature;
} thermostatd_options;

#endif
