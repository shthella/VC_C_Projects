#ifndef DISPLAY_RESTAURANTS_H
#define DISPLAY_RESTAURANTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sqlite3.h> // Include SQLite3 header for database handling
#include "debug_log.h" // Include the header file for debug logging
#include "database.h"

void display_restaurants(int client_socket); // Declaration of display_restaurants function

#endif /* DISPLAY_RESTAURANTS_H */

