/*
 * Utility functions header file
 */
#ifndef __UTIL_H__
#define __UTIL_H__

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <time.h>
#include <curl/curl.h>

#include "thermostatd.h"

// Return code bad key in key value store
//
#define BAD_KEY	-1

/*
 * Program debugging macros
 */
#ifndef DEBUG_OUT
#define DEBUG_OUT       1
#endif

// Setup a DEBUG function to print out various items during program
// execution.
//
#if defined(DEBUG_OUT) && DEBUG_OUT > 0
#define DEBUG(fmt, args...) syslog(LOG_DEBUG, "DEBUG: %s:%d:%s(): " fmt "\n", \
                __FILE__, __LINE__, __func__, ##args)
#else
#define DEBUG(fmt, args...) /* Don't do anything in release builds */
#endif

// Error string
//
#define ERROR_FORMAT    "An error occurred. The error is: %s"


/*
 * Build key-value store
 */
typedef struct kv_char_int_struct_t kv_store; 

int search_kv(kv_store *store, char* key);

const char *_get_local_time(void);
int time_since_midnight(void);
void _debug_prog_options(thermostatd_options *options);

// Utility to remove non-alphanumeric characters from a string
//
char *make_string_alphanum(char *str);

#endif
