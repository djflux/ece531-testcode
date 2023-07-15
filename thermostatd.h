/* 
 * Program support functions, and return codes.
 */

#ifndef __THERMOSTATD_H__
#define __THERMOSTATD_H__

#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <libconfig.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>
#include <json-c/json.h>
#include <json-c/json_visit.h>
#include <sys/stat.h>
#include <sys/types.h>


/* 
 * Include supporting header files
 */
#include "api.h"
#include "codes.h"
#include "config.h"
#include "http_interface.h"
#include "tc_main.h"
#include "tc_state.h"
#include "tc_error.h"
#include "util.h"

#define HEATER_STATUS_OFF   0
#define HEATER_STATUS_ON    1

float _get_current_local_temperature(FILE *fd);
int _get_current_heater_status(FILE* fd);
void _open_status_files(thermostatd_options *options);
void _read_config_file(thermostatd_options *options);
json_object *_get_current_setpoint(thermostatd_options *options);
json_object *_get_current_thermostat_status(thermostatd_options *options);
void _set_current_thermostat_options(json_object *current_thermostat_state, char *current_setpoint, float current_temp, int heater_status);
void _run_thermostat(thermostatd_options *options);

#endif
