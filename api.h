/*
 * cloud_api.h defines the cloud endpoints, methods and other supporting
 * prototypes for thermostatd to interact with the cloud-based API.
 */
#ifndef __API_H__
#define __API_H__

#include <json-c/json.h>

#include "config.h"
#include "util.h"

// Cloud API URL paths. These could be discovered but it's a quick thing
// for this project so defining macros.
//
#define API_ROOT                    "/"
#define API_SCHEDULE                "/schedule"
#define API_SCHEDULE_CLEAN          "/schedule_clean"
#define API_RESET_SCHEDULE          "/reset_schedule"
#define API_UPLOAD_SCHEDULE         "/upload_schedule"
#define API_THERMOSTAT_STATUS       "/thermostat_status"
#define API_RESET_THERMOSTAT_STATUS "/reset_thermostat_status"

#define API_EMPTY_SCHEDULE_FILE		"/etc/thermostatd/schedule-empty.json"

/*
 * JSON element names for status
 */
#define JSON_CURRENT_SETPOINT		"current_setpoint"
#define JSON_CURRENT_TEMP			"current_temp"
#define JSON_HEATER_STATUS			"heater_status"
#define JSON_NEW_SCHEDULE_BOOL		"new_schedule_available"

// Used for curl resonse bodies
//
struct memory {
	char *response;
	size_t size;
};

// Get the fulle schedule with API _id's so that we can update an 
// individual set point when needed (e.g. it becomes the current
// set point).
json_object *_api_get_schedule();

// Get a clean schedule to save to a local file
char *_api_get_schedule_clean(char *url);

// Get the thermostat status from the API endpoint.
//
char *_api_get_thermostat_status(char *url);

// Reset the schedule on the API endpoint. This may not be needed but
// prototyping in case.
json_object *_api_reset_schedule();

// Reset the thermostat status entry in the API endpoint.
// 
json_object *_api_reset_thermostat_status();

// Create a full thermostat status entry. This method will
// replace any status that currently exists.
json_object *_api_post_thermostat_status();

// Upload a full schedule to the API endpoint
char *api_upload_schedule(char *url, const char *postdata);

// Update the termostatus status
//
char *_api_put_status(char *url, const char *postdata);

#endif