/*
 * codes.h - contains return codes for program exit.
 */
#ifndef __CODES_H__
#define __CODES_H__

/*
 * Program return codes. Could be typedef enum - decided to explicitly
 * set numbers to know which type of exit happened.
 */
#define ERR_INIT        2
#define ERR_FORK        3
#define ERR_SETSID      4
#define ERR_CHDIR       5
#define ERR_FILE_OPEN   6

/*
 * Networking return codes
 */
#define ERR_NET_SOCKET	10
#define ERR_NET_BIND	11
#define ERR_NET_LISTEN	12
#define ERR_NET_ACCEPT	13

/*
 * Signal handling errors.
 */
#define ERR_SEGV        20

/*
 * Schedule errors
 */
#define ERR_SCHEDULE_NO_CURRENT 30

/* 
 * Some undefined error
 */
#define ERR_WTF         187

#endif
