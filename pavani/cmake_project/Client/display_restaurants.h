#ifndef DISPLAY_RESTAURANTS_H
#define DISPLAY_RESTAURANTS_H

// Include necessary libraries and headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>   // for send and recv
#include "debug_log.h"

// Function prototype for displaying restaurants
void display_restaurants(int client_socket);

#endif /* DISPLAY_RESTAURANTS_H */

