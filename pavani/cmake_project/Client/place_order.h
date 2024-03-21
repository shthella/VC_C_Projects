#ifndef PLACE_ORDER_H
#define PLACE_ORDER_H

// Include necessary libraries and headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>   // for send and recv
#include <unistd.h>
#include "debug_log.h"

// Function prototypes for utility functions
bool isValidYNInput(char input);
char getYNInput(char prompt[]);

// Function prototype for place_order function
void place_order(int client_socket);

#endif /* PLACE_ORDER_H */

