#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern int debug;
extern char ip_addr[20]; // Change const char* to char

void setDebugLevel(int argc, char *argv[]);
void debug_log(int level, const char *message);

#endif /* DEBUG_LOG_H */

