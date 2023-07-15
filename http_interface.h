/*
 * HTTP interface header file for thermostatd
 */
#ifndef __HTTP_INTERFACE_H__
#define __HTTP_INTERFACE_H__

/*
 * Necessary header files
 */
#include <fcntl.h>
#include <pthread.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <json-c/json.h>
#include <netinet/in.h>

#include "config.h"

#ifndef __HTTP_INTERFACE_H__
#define __HTTP_INTERFACE_H__
#endif

#define HTTP_BIND_ADDRESS	"*"
#define HTTP_BIND_PORT		8088
#define HTTP_BUFFER_SIZE	1048576 // 1MB

#define HTTP_REQUEST_REGEX	"([A-Za-z]+) +(/[A-Za-z0-9]+)\???+(.*) +(HTTP/[0-9][.][0-9])"

#define PATH_STATUS             1
#define PATH_HEATER_STATUS      2
#define PATH_CURRENT_TEMP       3
#define PATH_SCHEDULE           4

#define PATH_STRING_STATUS              "/status"
#define PATH_STRING_CURRENT_TEMP        "/currenttemp"
#define PATH_STRING_HEATER_STATUS       "/heaterstatus"
#define PATH_STRING_SCHEDULE            "/schedule"

#define HTTP_USER_AGENT         "thermostatd/0.0.1"

typedef struct kv_char_int_struct_t {
        char *key;
        int   value;
} kv_char_int_struct_t;

typedef struct http_request {
        char *method;
        char *path;
        char *query;
        char *version;
} http_request;

void* _http_handle_client(void *arg);
int  _http_start_interface(thermostatd_options *program_options);

#endif
